/*
 * boards/shields/nice_view_press_start/src/central/render.c
 *
 * Framebuffer-based central-side renderers.
 *
 * This file replaces the LVGL canvas drawing with direct writes into the
 * packed 1bpp framebuffer `screen_buffer`. Text rendering is omitted for now;
 * where the original used text/canvas APIs we either no-op or draw simple
 * placeholders (e.g. layer indicator).
 *
 * The functions below are intentionally small and call into the small set of
 * drawing helpers available in the shield:
 *  - draw_battery(x, y, state)
 *  - draw_bluetooth_logo(x, y)
 *  - draw_bluetooth_logo_outlined(x, y)
 *  - draw_bluetooth_searching(x, y)
 *  - draw_usb_logo(x, y)
 *  - draw_animation1(index)         (full-screen animation)
 *
 * After drawing UI elements we flush the framebuffer using the `oled_*`
 * helpers (provided in the shield implementation) so changes are visible on
 * the physical OLED.
 */

#include "../../include/central/render.h"
#include "../../include/main.h"
#include "../../include/colors.h"

#include "../../include/utils/draw_battery.h"
#include "../../include/utils/draw_bluetooth_logo.h"
#include "../../include/utils/draw_bluetooth_logo_outlined.h"
#include "../../include/utils/draw_bluetooth_searching.h"
#include "../../include/utils/draw_usb_logo.h"
#include "../../include/utils/draw_animation1.h"
#include "../../include/utils/rotate_connectivity_canvas.h"
#include "../../include/utils/rotate_main2_canvas.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* Small helper: fill a rectangle into the framebuffer using the pixel helper
 * exposed by main.h (screen_fb_set_pixel).
 */
static void fill_rect_fb(int x, int y, int w, int h, int on) {
    if (w <= 0 || h <= 0) return;
    for (int yy = 0; yy < h; ++yy) {
        int py = y + yy;
        if ((unsigned)py >= (unsigned)SCREEN_HEIGHT) continue;
        for (int xx = 0; xx < w; ++xx) {
            int px = x + xx;
            if ((unsigned)px >= (unsigned)SCREEN_WIDTH) continue;
            screen_fb_set_pixel(px, py, on ? true : false);
        }
    }
}

/* Render the battery widget.
 *
 * We draw the battery at a fixed location and flush the display. The battery
 * drawer takes care of drawing the interior according to `states.battery`.
 */
void render_battery() {
    /* Clear the top-left/top area where the battery will be drawn to avoid
     * leftover pixels from previous frames. Use a small safe box.
     */
    const int bx = SCREEN_WIDTH - 12; /* place near the right edge */
    const int by = 2;
    const int bw = 12;
    const int bh = 26;

    /* Clear region */
    fill_rect_fb(bx, by, bw, bh, BACKGROUND_COLOR);

    /* Draw battery using the shared drawer */
    draw_battery((uint16_t)bx, (uint16_t)by, states.battery);

    /* Flush to physical display (best-effort) */
    (void)oled_update_framebuffer();
}

/* Render the connectivity widget (bluetooth / usb).
 *
 * Layout chosen to roughly match the original: a small connectivity icon
 * somewhere in the top-left-ish area. We reuse the framebuffer icon drawers.
 */
void render_connectivity() {
    /* Clear a small area first */
    const int cx = 18;
    const int cy = 15;
    fill_rect_fb(cx - 4, cy - 4, 40, 40, BACKGROUND_COLOR);

    /* Choose what to draw depending on selected endpoint transport */
    switch (states.connectivity.selected_endpoint.transport) {
        case ZMK_TRANSPORT_BLE:
            if (states.connectivity.active_profile_bonded) {
                if (states.connectivity.active_profile_connected) {
                    /* Solid Bluetooth glyph */
                    draw_bluetooth_logo((uint16_t)cx, (uint16_t)cy);
                } else {
                    /* Bonded but not connected: outlined glyph */
                    draw_bluetooth_logo_outlined((int)cx, (int)cy);
                }
            } else {
                /* No bonded profile: show searching indicator */
                draw_bluetooth_searching((uint16_t)cx, (uint16_t)cy);
            }
            break;

        case ZMK_TRANSPORT_USB:
        default:
            /* USB transport or unknown: draw USB glyph */
            draw_usb_logo((uint16_t)11, (uint16_t)19);
            break;
    }

    /* Rotation helper preserved for API compatibility (no-op on framebuffer) */
    rotate_connectivity_canvas();

    /* Flush framebuffer so the connectivity status is visible immediately */
    (void)oled_update_framebuffer();
}

/* Render main area.
 *
 * If the optional animation feature is enabled, draw the fullscreen animation
 * using the animation helper that copies a full packed 1bpp frame into the
 * global `screen_buffer` and flushes itself.
 *
 * If animations are not enabled, this function currently leaves the main
 * framebuffer content alone.
 */
void render_main() {
#if IS_ENABLED(CONFIG_NICE_VIEW_PRESS_START_BACKGROUND)
    /* draw_animation1 will copy and flush */
    draw_animation1(states.background_index);
#else
    /* No background animation: nothing to do for now. */
    (void)states.background_index;
#endif
}

/* Render the secondary main area (main2).
 *
 * The original LVGL implementation drew the active layer name. Text drawing is
 * omitted for now; instead we render a small visual indicator representing the
 * active layer index (a few filled blocks). This is intentionally simple and
 * keeps the UI informative without pulling in a text renderer.
 */
void render_main2() {
#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
    /* Clear a small area in the lower-right where layer info previously lived */
    const int area_w = 40;
    const int area_h = 16;
    const int area_x = (SCREEN_WIDTH > area_w) ? (SCREEN_WIDTH - area_w - 2) : 0;
    const int area_y = (SCREEN_HEIGHT > area_h) ? (SCREEN_HEIGHT - area_h - 2) : 0;
    fill_rect_fb(area_x, area_y, area_w, area_h, BACKGROUND_COLOR);

    /* Draw up to 5 small blocks indicating the active layer index (0..4) */
    int idx = (int)states.layer.index;
    if (idx < 0) idx = 0;
    /* normalize to 0..4 range for display */
    int display_idx = idx % 5;

    const int block_w = 6;
    const int block_h = 8;
    const int gap = 4;
    int start_x = area_x + 4;
    int start_y = area_y + 4;

    for (int i = 0; i < 5; ++i) {
        int on = (i == display_idx) ? FOREGROUND_COLOR : BACKGROUND_COLOR;
        fill_rect_fb(start_x + i * (block_w + gap), start_y, block_w, block_h, on);
    }

    /* Rotation helper preserved for API compatibility (no-op for framebuffer) */
    rotate_main2_canvas();

    /* Flush so layer indicator is visible */
    (void)oled_update_framebuffer();
#else
    (void)states.layer;
#endif
}