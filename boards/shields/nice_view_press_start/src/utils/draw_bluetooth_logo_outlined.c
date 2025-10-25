#include "../../include/utils/draw_bluetooth_logo_outlined.h"
#include "../../include/main.h"
#include "../../include/images/bluetooth_disconnected_mono.h"
#include <stdint.h>
#include <stdbool.h>

/*
 * Framebuffer-based replacement for the LVGL canvas image draw.
 *
 * The original implementation used LVGL to draw an indexed 1-bit image onto
 * an LVGL canvas. For the SSD1306/Corne framebuffer port we instead copy the
 * pre-generated packed 1bpp bitmap into the global `screen_buffer`.
 *
 * Signature intentionally kept the same so existing callers (passing an
 * LVGL canvas pointer) keep building — the `canvas` parameter is ignored.
 *
 * The mono image header `bluetooth_disconnected_mono.h` was generated with
 * the conversion tool at size 12x17 (packed row-major, MSB-first).
 */

void draw_bluetooth_logo_outlined(int x, int y) {
    const int W = 12;
    const int H = 17;

    /* Quick bounds check */
    if (x + W <= 0 || x >= SCREEN_WIDTH || y + H <= 0 || y >= SCREEN_HEIGHT) {
        return;
    }

    const uint8_t *src = bluetooth_disconnected_frames[0];
    const int src_bpr = (W + 7) / 8; /* bytes per row in source (should be 2) */

    /* Copy source rows into the global framebuffer, setting pixels individually
     * to avoid byte-alignment issues when `x` is not byte-aligned.
     */
    for (int row = 0; row < H; ++row) {
        const uint8_t *row_src = src + row * src_bpr;
        for (int bx = 0; bx < src_bpr; ++bx) {
            uint8_t byte = row_src[bx];
            for (int bit = 0; bit < 8; ++bit) {
                int sx = bx * 8 + bit;
                if (sx >= W) break;
                bool pixel_on = (byte & (1u << (7 - bit))) != 0;
                screen_fb_set_pixel(x + sx, y + row, pixel_on);
            }
        }
    }
}
