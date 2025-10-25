#pragma once

/*
 * Framebuffer-based main definitions for the SSD1306 128x64 port.
 *
 * This header replaces the previous LVGL-based layout with a simple packed
 * 1-bit framebuffer layout used by the Corne/SSD1306 OLED driver:
 *
 * - Row-major ordering
 * - MSB-first within each byte (bit 7 = leftmost pixel of the byte)
 * - Each row is padded to a full byte boundary (bytes_per_row = ceil(width/8))
 *
 * Other modules in this shield include this header to access the global
 * `screen_buffer` and layout constants.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* Target display dimensions for the Corne SSD1306 128x64 module */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

/* Width reserved for the top (battery) column used by the UI */
#define TOP_WIDTH 25

/* Canvas / region definitions reworked for framebuffer approach */
#define BATTERY_CANVAS_WIDTH (TOP_WIDTH)
#define BATTERY_CANVAS_HEIGHT (SCREEN_HEIGHT / 2)

#define CONNECTIVITY_CANVAS_WIDTH (SCREEN_HEIGHT / 2)
#define CONNECTIVITY_CANVAS_HEIGHT (CONNECTIVITY_CANVAS_WIDTH)
#define CONNECTIVITY_CANVAS_AVAILABLE_HEIGHT (TOP_WIDTH)

#define MAIN_CANVAS_WIDTH (SCREEN_WIDTH)
#define MAIN_CANVAS_HEIGHT (SCREEN_HEIGHT)

#define MAIN2_CANVAS_WIDTH (SCREEN_HEIGHT)
#define MAIN2_CANVAS_HEIGHT (SCREEN_HEIGHT)

/* Packed framebuffer sizing helpers */
#define SCREEN_BYTES_PER_ROW (((SCREEN_WIDTH) + 7) / 8)
#define SCREEN_FB_BYTES ((SCREEN_BYTES_PER_ROW) * (SCREEN_HEIGHT))

/*
 * Global framebuffer.
 *
 * - Packed 1bpp, row-major, MSB-first per byte.
 * - Size: SCREEN_FB_BYTES bytes.
 *
 * Note: defined in a single C translation unit (implementation) to avoid
 * multiple-definition errors. Other files should include this header and use
 * the extern declaration below.
 */
extern uint8_t screen_buffer[SCREEN_FB_BYTES];

/* Simple OLED helper prototypes (implemented in the shield code).
 *
 * These helpers are intentionally minimal and are designed for the framebuffer
 * approach:
 *
 * - `oled_init_fb` should bind the Zephyr display device and perform any
 *   initialization required for the SSD1306 driver.
 * - `oled_flush_fb` should write the entire `screen_buffer` to the display
 *   using the appropriate display API (e.g., display_write / display_write_async).
 * - `oled_draw_fullscreen_frame` copies a single packed 1bpp frame (SCREEN_FB_BYTES
 *   bytes) into `screen_buffer` and flushes the display.
 *
 * Implementations may optionally accept a DT label or use DT macros
 * internally to obtain the correct device binding.
 */
void oled_init_fb(const char *display_label);
void oled_flush_fb(void);
void oled_draw_fullscreen_frame(const uint8_t *frame);

/* Convenience: clear the framebuffer (set all pixels to 0/black) */
static inline void screen_fb_clear(void) {
    for (size_t i = 0; i < SCREEN_FB_BYTES; ++i) {
        screen_buffer[i] = 0x00;
    }
}

/* Pixel helper (row-major, MSB-first). Useful for small primitives that write
 * directly into the framebuffer.
 *
 * x: 0..SCREEN_WIDTH-1
 * y: 0..SCREEN_HEIGHT-1
 * v: true=set (white), false=clear (black)
 */
static inline void screen_fb_set_pixel(int x, int y, bool v) {
    if ((unsigned)x >= (unsigned)SCREEN_WIDTH || (unsigned)y >= (unsigned)SCREEN_HEIGHT) {
        return;
    }
    const size_t row_off = (size_t)y * SCREEN_BYTES_PER_ROW;
    const size_t byte_idx = row_off + (x / 8);
    const uint8_t bit = (uint8_t)(1u << (7 - (x & 7)));
    if (v) {
        screen_buffer[byte_idx] |= bit;
    } else {
        screen_buffer[byte_idx] &= (uint8_t)~bit;
    }
}