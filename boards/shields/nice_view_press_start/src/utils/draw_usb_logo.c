#include "../../include/main.h"
#include <stdint.h>
#include <stdbool.h>

/*
 * Framebuffer-based USB icon drawer for the SSD1306 monochrome port.
 *
 * Draws a compact USB glyph directly into the packed 1bpp framebuffer
 * `screen_buffer` (row-major, MSB-first). Coordinates (x,y) specify the
 * top-left corner where the icon will be drawn.
 *
 * This is a small, robust placeholder implementation that avoids LVGL and
 * uses simple primitives to render a recognizable USB symbol.
 */

/* Helper: set or clear a pixel in the packed 1bpp framebuffer.
 * x: 0..SCREEN_WIDTH-1, y: 0..SCREEN_HEIGHT-1
 * v: true = set (white/foreground), false = clear (black/background)
 */
static inline void set_pixel_fb(int x, int y, bool v) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return;
    }
    const int bytes_per_row = SCREEN_WIDTH / 8;
    size_t byte_index = (size_t)y * bytes_per_row + (x / 8);
    uint8_t bit = 1u << (7 - (x & 7)); /* MSB-first */
    if (v) {
        screen_buffer[byte_index] |= bit;
    } else {
        screen_buffer[byte_index] &= (uint8_t)~bit;
    }
}

/* Draw a horizontal line in the framebuffer */
static void hline_fb(int x, int y, int w, bool v) {
    for (int i = 0; i < w; i++) {
        set_pixel_fb(x + i, y, v);
    }
}

/* Draw a vertical line in the framebuffer */
static void vline_fb(int x, int y, int h, bool v) {
    for (int j = 0; j < h; j++) {
        set_pixel_fb(x, y + j, v);
    }
}

/* Fill a rectangle area in the framebuffer */
static void fill_rect_fb(int x, int y, int w, int h, bool v) {
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            set_pixel_fb(x + i, y + j, v);
        }
    }
}

/* Draw a small circle (approximated) into the framebuffer */
static void draw_circle_fb(int cx, int cy, int r, bool v) {
    if (r <= 0) {
        set_pixel_fb(cx, cy, v);
        return;
    }
    /* Midpoint circle algorithm (simple integer version) */
    int x = r;
    int y = 0;
    int err = 0;

    while (x >= y) {
        set_pixel_fb(cx + x, cy + y, v);
        set_pixel_fb(cx + y, cy + x, v);
        set_pixel_fb(cx - y, cy + x, v);
        set_pixel_fb(cx - x, cy + y, v);
        set_pixel_fb(cx - x, cy - y, v);
        set_pixel_fb(cx - y, cy - x, v);
        set_pixel_fb(cx + y, cy - x, v);
        set_pixel_fb(cx + x, cy - y, v);

        y += 1;
        if (err <= 0) {
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

/* Public API: draw a compact USB glyph at (x,y).
 *
 * The glyph is approximately 11x13 pixels. It draws:
 *  - a circle 'handle' at the top
 *  - a vertical stem downwards
 *  - three prongs (left, right, bottom) forming the USB symbol
 */
void draw_usb_logo(uint16_t x, uint16_t y) {
    /* Icon dimensions and quick bounds check */
    const int W = 11;
    const int H = 13;
    if ((int)x + W <= 0 || (int)x >= SCREEN_WIDTH || (int)y + H <= 0 || (int)y >= SCREEN_HEIGHT) {
        return;
    }

    /* Coordinates relative to icon origin */
    int ox = (int)x;
    int oy = (int)y;

    /* Draw top circle/handle (centered horizontally) */
    int circle_cx = ox + 5; /* center x */
    int circle_cy = oy + 2; /* center y */
    draw_circle_fb(circle_cx, circle_cy, 2, true);

    /* Draw vertical stem from below the circle */
    int stem_x = circle_cx;
    int stem_y = circle_cy + 3;
    vline_fb(stem_x, stem_y, 6, true);

    /* Draw bottom prong (small triangle/line) */
    hline_fb(ox + 4, oy + 10, 3, true);  /* short horizontal at bottom */

    /* Draw left prong: small line and dot */
    hline_fb(ox + 1, oy + 7, 3, true);
    set_pixel_fb(ox + 0, oy + 7, true);

    /* Draw right prong: small line and dot */
    hline_fb(ox + 7, oy + 7, 3, true);
    set_pixel_fb(ox + 10, oy + 7, true);

    /* Strengthen glyph by filling a small vertical segment in the stem */
    fill_rect_fb(stem_x - 1, stem_y + 1, 3, 3, true);

    /* Optionally, clear a pixel to give a slightly stylized look (interior) */
    set_pixel_fb(circle_cx, circle_cy, false); /* hollow the ring center */
}