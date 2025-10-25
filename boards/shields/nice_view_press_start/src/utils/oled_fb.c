/*
 * Simple framebuffer-based OLED helper for the Corne SSD1306 port.
 *
 * Provides:
 *  - oled_init_fb(const char *display_label)
 *  - oled_flush_fb(void)
 *  - oled_draw_fullscreen_frame(const uint8_t *frame)
 *
 * The implementation attempts to bind the Zephyr display device using the
 * supplied `display_label`. If `display_label` is NULL it tries a set of
 * reasonable DT fallbacks so the code isn't hard-coded to a single label.
 *
 * The code writes the entire packed 1bpp framebuffer `screen_buffer` to the
 * display using the Zephyr display API (`display_write` with a
 * `display_buffer_descriptor`) when available. The expected framebuffer layout
 * is:
 *  - Row-major
 *  - MSB-first within each byte (bit7 = leftmost pixel of the byte)
 *  - Rows padded to whole bytes (bytes_per_row = ceil(width/8))
 *
 * This file intentionally keeps the logic minimal and defensive: if no display
 * device can be bound, flush calls will no-op and emit a diagnostic message.
 */

#include "../../include/main.h"

#ifdef __has_include
#  if __has_include(<zephyr/device.h>)
#    include <zephyr/device.h>
#  else
#    include "../../../../../zephyr/device.h"
#  endif
#else
#  include "../../../../../zephyr/device.h"
#endif

#ifdef __has_include
#  if __has_include(<zephyr/drivers/display.h>)
#    include <zephyr/drivers/display.h>
#  else
#    include "../../../../../zephyr/drivers/display.h"
#  endif
#else
#  include "../../../../../zephyr/drivers/display.h"
#endif

#ifdef __has_include
#  if __has_include(<zephyr/devicetree.h>)
#    include <zephyr/devicetree.h>
#  else
#    include "../../../../../zephyr/devicetree.h"
#  endif
#else
#  include "../../../../../zephyr/devicetree.h"
#endif

/* Prefer the dedicated sys/printk when available; otherwise fall back to the
 * shield-local stub. If neither header is detected, declare a minimal prototype
 * for static analysis so translation units can use `printk` without including
 * the Zephyr kernel stub (which previously triggered unused-include warnings).
 */
#ifdef __has_include
#  if __has_include(<zephyr/sys/printk.h>)
#    include <zephyr/sys/printk.h>
#  elif __has_include("boards/shields/nice_view_press_start/include/zephyr/sys/printk.h")
#    include "boards/shields/nice_view_press_start/include/zephyr/sys/printk.h"
#  else
/* Minimal prototype for static-analysis fallback (no kernel.h include). */
int printk(const char *fmt, ...);
#  endif
#else
int printk(const char *fmt, ...);
#endif

/* printk prototype is provided above when the real header is not available,
 * so no additional prototype is needed here.
 */

#include <string.h>

#ifndef SCREEN_FB_BYTES
/* Fallback in case main.h uses a different name */
#define SCREEN_FB_BYTES FB_BYTES_TOTAL
#endif

/* Static binding to the display device discovered during init */
static const struct device *oled_dev = NULL;

/* Helper: try device_get_binding by label and log a short message */
static const struct device *try_bind_label(const char *label) {
    if (!label) {
        return NULL;
    }
    const struct device *dev = device_get_binding(label);
    if (dev) {
        printk("oled_fb: bound to display '%s'\n", label);
    } else {
        printk("oled_fb: device_get_binding('%s') failed\n", label);
    }
    return dev;
}

/* Try a sequence of DT-based fallbacks (compile-time) if the user did not pass
 * an explicit label. Each branch is guarded by the appropriate devicetree macro.
 *
 * The goal is to be tolerant across boards and overlays where the SSD1306
 * node might be named differently.
 */
static const struct device *try_dt_fallbacks(void) {
    const struct device *dev = NULL;

    /* 1) DT_CHOSEN display (common in some ZMK setups) */
#ifdef DT_CHOSEN_zmk_display
#if DT_NODE_EXISTS(DT_CHOSEN(zmk_display))
    dev = device_get_binding(DT_LABEL(DT_CHOSEN(zmk_display)));
    if (dev) {
        printk("oled_fb: bound to chosen zmk_display (%s)\n", DT_LABEL(DT_CHOSEN(zmk_display)));
        return dev;
    }
#endif
#endif

    /* 2) Common node label used by some SSD1306 overlays */
#if DT_NODE_EXISTS(DT_NODELABEL(ssd1306))
    dev = device_get_binding(DT_LABEL(DT_NODELABEL(ssd1306)));
    if (dev) {
        printk("oled_fb: bound to nodelabel ssd1306 (%s)\n", DT_LABEL(DT_NODELABEL(ssd1306)));
        return dev;
    }
#endif

    /* 3) If the driver is registered as an instance of solomon, try instance 0 */
#ifdef DT_DRV_COMPAT_solomon_ssd1306fb
#if DT_HAS_COMPAT_STATUS_OKAY(solomon_ssd1306fb)
    /* DT_INST macros are the recommended way to access instances */
#if DT_NODE_EXISTS(DT_INST(0, solomon_ssd1306fb))
    dev = device_get_binding(DT_LABEL(DT_INST(0, solomon_ssd1306fb)));
    if (dev) {
        printk("oled_fb: bound to solomon_ssd1306fb instance 0 (%s)\n", DT_LABEL(DT_INST(0, solomon_ssd1306fb)));
        return dev;
    }
#endif
#endif
#endif

    /* 4) Try a named alias (some overlays create an alias like 'ssd1306') */
#ifdef DT_ALIAS_ssd1306
#if DT_NODE_EXISTS(DT_ALIAS_ssd1306)
    dev = device_get_binding(DT_LABEL(DT_ALIAS_ssd1306));
    if (dev) {
        printk("oled_fb: bound to alias ssd1306 (%s)\n", DT_LABEL(DT_ALIAS_ssd1306));
        return dev;
    }
#endif
#endif

    /* Nothing found */
    return NULL;
}

/* Initialize the oled framebuffer binding.
 *
 * If `display_label` is provided it will be used directly. Otherwise the
 * function tries a set of DT fallbacks compiled into the firmware.
 *
 * This function is safe to call multiple times; subsequent calls will not
 * re-bind if a device is already bound.
 */
void oled_init_fb(const char *display_label) {
    if (oled_dev) {
        /* already initialized */
        return;
    }

    if (display_label) {
        oled_dev = try_bind_label(display_label);
    }

    if (!oled_dev) {
        oled_dev = try_dt_fallbacks();
    }

    if (!oled_dev) {
        printk("oled_fb: WARNING: failed to bind any display device. oled_flush_fb will no-op.\n");
    } else {
        /* Optionally log capabilities if the display driver exposes them */
        struct display_capabilities caps;
        if (display_get_capabilities(oled_dev, &caps) == 0) {
            printk("oled_fb: display capabilities: xres=%u yres=%u framebuffer=%s\n",
                   caps.x_resolution, caps.y_resolution,
                   (caps.screen_info & SCREEN_INFO_MONO_VTILED) ? "vtiled/mono" : "unknown");
        }
    }
}

/* Flush the global screen_buffer to the display device.
 *
 * This uses the Zephyr display API with a `display_buffer_descriptor` describing
 * a full-screen write. If the display device is not bound this function will
 * simply return.
 */
void oled_flush_fb(void) {
    if (!oled_dev) {
        printk("oled_fb: flush requested but display device not bound\n");
        return;
    }

    /* Prepare descriptor for the full framebuffer. The descriptor fields used
     * here match the Zephyr display API expectations for a raw buffer write.
     */
    struct display_buffer_descriptor desc = {
        .buf_size = SCREEN_FB_BYTES,
        .width = SCREEN_WIDTH,
        .height = SCREEN_HEIGHT,
        .pitch = SCREEN_WIDTH, /* pitch in pixels */
    };

    int rc = display_write(oled_dev, 0, 0, &desc, screen_buffer);
    if (rc) {
        printk("oled_fb: display_write failed: %d\n", rc);
    }
}

/* Copy a packed fullscreen frame into the global framebuffer and flush. If the
 * provided `frame` pointer is NULL the function will clear the framebuffer
 * instead and flush that (useful for test patterns).
 */
void oled_draw_fullscreen_frame(const uint8_t *frame) {
    if (frame) {
        memcpy(screen_buffer, frame, SCREEN_FB_BYTES);
    } else {
        /* Clear */
        memset(screen_buffer, 0x00, SCREEN_FB_BYTES);
    }
    oled_flush_fb();
}

/* Compatibility shim expected by a few callers in the shield code.
 *
 * Historically the code called `oled_update_framebuffer()` which returned an
 * int status. Provide a thin wrapper that invokes the framebuffer flush and
 * returns 0 to indicate success.
 */
int oled_update_framebuffer(void) {
    oled_flush_fb();
    return 0;
}