#include "../../include/peripheral/render.h"

#include <stdint.h>
#include <stddef.h>

#include "../../include/main.h"
#include "../../include/peripheral/initialize_listeners.h"

#include "../../include/utils/draw_battery.h"
#include "../../include/utils/draw_animation2.h"
#include "../../include/utils/draw_bluetooth_logo_outlined.h"
#include "../../include/utils/draw_bluetooth_logo.h"
#include "../../include/utils/draw_bluetooth_searching.h"
#include "../../include/utils/draw_usb_logo.h"
#include "../../include/utils/rotate_connectivity_canvas.h"

/* Prototype for framebuffer flush helper (implemented in oled_fb.c) */
extern int oled_update_framebuffer(void);

/*
 * Peripheral-side framebuffer-based renderers
 *
 * These functions replace the LVGL canvas-based drawing with direct writes
 * into the packed 1bpp global framebuffer `screen_buffer`. Many drawing
 * helpers (draw_battery, draw_bluetooth_logo, draw_usb_logo, etc.) write
 * into that buffer. Full-screen animations (draw_animation2) will copy
 * entire frames into `screen_buffer` and flush the display themselves.
 *
 * These functions are intentionally small and act as the glue between
 * the ZMK listeners/timers and the framebuffer drawing helpers.
 */

void render_battery(void) {
    /* Historically the battery was drawn around the top-right region of the
     * screen. For the peripheral (small layout) we draw it at a fixed offset
     * similar to the original layout used by the LVGL implementation.
     *
     * The `draw_battery` helper writes into `screen_buffer` but does not
     * necessarily flush the display, so call the flush helper afterwards to
     * ensure immediate update of the physical OLED.
     */
    draw_battery(5, 5, states.battery);

    /* Best-effort flush; ignore error return here. */
    (void)oled_update_framebuffer();
}

void render_connectivity(void) {
    /*
     * Compose the connectivity icon area. The original implementation used a
     * small LVGL canvas. Here we choose coordinates that match the original
     * visual placement (approximate) and call the framebuffer-based drawers.
     *
     * Flow:
     *  - If BLE endpoint selected: show bluetooth (connected/bonded) or searching
     *  - If USB endpoint selected: show USB icon
     *
     * After drawing the icon(s) we flush the framebuffer so the device updates.
     */

    if (states.connectivity.selected_endpoint.transport == ZMK_TRANSPORT_BLE) {
        if (states.connectivity.active_profile_bonded) {
            if (states.connectivity.active_profile_connected) {
                /* Connected + bonded: solid bluetooth glyph */
                draw_bluetooth_logo(18, 15);
            } else {
                /* Bonded but not connected: outlined glyph (or same glyph) */
                draw_bluetooth_logo_outlined(18, 15);
            }
        } else {
            /* No bonded profile: show searching indicator */
            draw_bluetooth_searching(18, 15);
        }
    } else {
        /* USB transport */
        draw_usb_logo(11, 19);
    }

    /* Call rotation/orientation helper (no-op for monochrome path but kept
     * to preserve API compatibility). */
    rotate_connectivity_canvas();

    /* Flush framebuffer to the OLED */
    (void)oled_update_framebuffer();
}

void render_main(void) {
#if IS_ENABLED(CONFIG_NICE_VIEW_PRESS_START_BACKGROUND)
    /*
     * draw_animation2 is responsible for copying the appropriate full-screen
     * monochrome frame into `screen_buffer` and flushing the OLED. We simply
     * forward the background index here.
     */
    draw_animation2(states.background_index);
#endif
}