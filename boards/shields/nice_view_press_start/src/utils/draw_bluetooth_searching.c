#include "../../include/utils/draw_bluetooth_searching.h"
#include "../../include/main.h"
#include "../../include/images/bluetooth_searching_mono.h"

#include <stdint.h>
#include <stdbool.h>

/*
 * Blit the pre-generated mono bitmap for the 'bluetooth searching' icon into
 * the global packed 1bpp framebuffer `screen_buffer`.
 *
 * The generated header `bluetooth_searching_mono.h` contains:
 *   static const uint8_t bluetooth_searching_frames[][ BYTES_PER_FRAME ]
 *   static const unsigned bluetooth_searching_frame_count
 *
 * The image was generated with dimensions 12x17 (W x H) and is packed
 * row-major, MSB-first within each byte (bit7 = leftmost pixel).
 *
 * This function preserves the original public API (coordinates in pixels).
 */

/* Known icon dimensions (matched when the header was generated) */
#define BT_SEARCH_W 12
#define BT_SEARCH_H 17

void draw_bluetooth_searching(uint16_t x, uint16_t y) {
    /* Quick bounds check: skip if icon is fully off-screen */
    if ((int)x + BT_SEARCH_W <= 0 || (int)x >= SCREEN_WIDTH ||
        (int)y + BT_SEARCH_H <= 0 || (int)y >= SCREEN_HEIGHT) {
        return;
    }

    /* Use first (and only) frame from the generated header */
    if (bluetooth_searching_frame_count == 0) {
        return;
    }
    const uint8_t *src = bluetooth_searching_frames[0];

    const int src_bpr = (BT_SEARCH_W + 7) / 8; /* bytes per row in source */

    for (int row = 0; row < BT_SEARCH_H; ++row) {
        const uint8_t *row_src = src + row * src_bpr;
        for (int bx = 0; bx < src_bpr; ++bx) {
            uint8_t byte = row_src[bx];
            /* Iterate bits MSB-first: bit 7 = leftmost pixel in this source byte */
            for (int bit = 0; bit < 8; ++bit) {
                int sx = bx * 8 + bit;
                if (sx >= BT_SEARCH_W) {
                    break;
                }
                bool pixel_on = (byte & (1u << (7 - bit))) != 0;
                screen_fb_set_pixel((int)x + sx, (int)y + row, pixel_on);
            }
        }
    }
}