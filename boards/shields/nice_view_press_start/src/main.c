/*
 * boards/shields/nice_view_press_start/src/main.c
 *
 * Framebuffer-based display initialization for the Corne SSD1306 128x64 port.
 *
 * This file replaces the previous LVGL-based `zmk_display_status_screen`
 * provider with a minimal framebuffer initializer that:
 *  - binds the SSD1306 display device,
 *  - clears & draws a small test pattern to verify the wiring,
 *  - calls the shield's listeners initialization so the rest of the UI logic
 *    can start updating the `screen_buffer`.
 *
 * The original API in ZMK expects a function named `zmk_display_status_screen`.
 * In the LVGL port this returned an `lv_obj_t *`. Since this shield build does
 * not use LVGL we simply return NULL while still providing the initialization
 * side-effects. The returned pointer is not used by the framebuffer-based
 * implementation.
 */

#include "../include/main.h"
#ifdef __has_include
#  if __has_include(<zephyr/kernel.h>)
#    include <zephyr/kernel.h>
#  endif
#endif
#include <string.h>

/* initialize_listeners provides the battery/ble listeners and hooks used by
 * the renderers. The header lives in the shield include tree.
 */
#include "../include/central/initialize_listeners.h"

/* Provide a simple no-op typedef so any external references to `lv_obj_t*`
 * signatures (from core ZMK headers or elsewhere) are compatible at the
 * symbol level. This keeps link-time compatibility while avoiding LVGL.
 *
 * Note: this typedef is intentionally local to this translation unit.
 */
typedef void lv_obj_t;

/* zmk_display_status_screen
 *
 * Called by ZMK to obtain the display root in the LVGL port. For the
 * framebuffer port we use this call as an opportunity to:
 *  - bind the OLED device (via oled_init_fb)
 *  - draw a quick test pattern and flush it to the OLED
 *  - initialize the shield listeners so rendering updates begin
 *
 * Returns: NULL (no LVGL screen object).
 */
lv_obj_t *zmk_display_status_screen(void) {
    /* Bind the OLED device (use DT fallbacks inside the helper). */
    oled_init_fb(NULL);

    /* Clear the software framebuffer first. */
    screen_fb_clear();

    /* Draw a simple test pattern so users can verify wiring at boot:
     * - a 2-pixel border
     * - a small diagonal line
     * - a central 8x8 checker to show inversion/packing clearly
     */
    const int W = SCREEN_WIDTH;
    const int H = SCREEN_HEIGHT;

    /* Border */
    for (int x = 0; x < W; ++x) {
        screen_fb_set_pixel(x, 0, true);
        screen_fb_set_pixel(x, H - 1, true);
    }
    for (int y = 0; y < H; ++y) {
        screen_fb_set_pixel(0, y, true);
        screen_fb_set_pixel(W - 1, y, true);
    }

    /* Diagonal */
    const int diag_len = (W < H) ? W : H;
    for (int i = 2; i < diag_len - 2; i += 2) {
        screen_fb_set_pixel(i, i, true);
    }

    /* Center checker (8x8) */
    const int cx = W / 2 - 4;
    const int cy = H / 2 - 4;
    for (int yy = 0; yy < 8; ++yy) {
        for (int xx = 0; xx < 8; ++xx) {
            bool on = ((xx + yy) & 1) == 0;
            screen_fb_set_pixel(cx + xx, cy + yy, on);
        }
    }

    /* Flush the framebuffer to the OLED (no-op if device not bound). */
    oled_flush_fb();

    /* Initialize shield listeners (battery, BLE profile listeners, etc.). */
    initialize_listeners();

    /* The LVGL port returned an lv_obj_t* screen; in framebuffer mode we
     * do not use LVGL, so return NULL. The important work is the init side
     * effects performed above.
     */
    return NULL;
}