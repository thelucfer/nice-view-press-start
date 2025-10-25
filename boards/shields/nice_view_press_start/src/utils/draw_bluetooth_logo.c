#include "../../include/main.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * Framebuffer-based Bluetooth icon drawer for the SSD1306 monochrome port.
 *
 * This function draws a compact Bluetooth glyph directly into the packed
 * 1bpp framebuffer `screen_buffer`. The packing assumed is row-major,
 * MSB-first per byte (byte_per_row = SCREEN_WIDTH / 8).
 *
 * Coordinates (x,y) specify the top-left corner where the icon will be drawn.
 * The icon is a small 9x17 pixel glyph designed to be readable at small sizes.
 *
 * This implementation is self-contained and does not depend on LVGL or any
 * externally generated image headers. It is intentionally simple and robust.
 */

/* Helper: set or clear a pixel in the packed 1bpp screen buffer.
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

/* Draw a simple line from (x0,y0) to (x1,y1) using Bresenham's algorithm.
 * Draws pixels into the framebuffer as 'set'.
 */
static void draw_line_fb(int x0, int y0, int x1, int y1) {
    int dx =  abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy; /* error value e_xy */
    while (1) {
        set_pixel_fb(x0, y0, true);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
}

/* Draw a filled triangle by drawing horizontal scanlines between edges.
 * v: true to set pixels (fill), false to clear.
 */
static void fill_triangle_fb(int x0, int y0, int x1, int y1, int x2, int y2, bool v) {
    /* Sort points by y ascending (y0 <= y1 <= y2) */
    if (y0 > y1) { int tx = x0; x0 = x1; x1 = tx; int ty = y0; y0 = y1; y1 = ty; }
    if (y1 > y2) { int tx = x1; x1 = x2; x2 = tx; int ty = y1; y1 = y2; y2 = ty; }
    if (y0 > y1) { int tx = x0; x0 = x1; x1 = tx; int ty = y0; y0 = y1; y1 = ty; }

    static int edge_interp(int xa, int ya, int xb, int yb, int y) {
        if (ya == yb) return xa;
        /* Use long long for the intermediate multiply to avoid overflow on large diffs */
        return xa + (int)(((long long)(xb - xa) * (y - ya)) / (yb - ya));
    }

    for (int y = y0; y <= y2; y++) {
        if (y < y1) {
            int xa = edge_interp(x0, y0, x1, y1, y);
            int xb = edge_interp(x0, y0, x2, y2, y);
            if (xa > xb) { int t = xa; xa = xb; xb = t; }
            for (int x = xa; x <= xb; x++) set_pixel_fb(x, y, v);
        } else {
            int xa = edge_interp(x1, y1, x2, y2, y);
            int xb = edge_interp(x0, y0, x2, y2, y);
            if (xa > xb) { int t = xa; xa = xb; xb = t; }
            for (int x = xa; x <= xb; x++) set_pixel_fb(x, y, v);
        }
    }
}

/* Public API: draw a small Bluetooth glyph at (x,y).
 *
 * The glyph is 9 pixels wide and 17 pixels tall, centered for clarity.
 * The design approximates the standard Bluetooth rune with two diagonal
 * strokes and a central vertical connector.
 */
void draw_bluetooth_logo(uint16_t x, uint16_t y) {
    /* Icon dimensions */
    const int W = 9;
    const int H = 17;

    /* Quick bounds check: if entirely off-screen, skip */
    if ((int)x + W <= 0 || (int)x >= SCREEN_WIDTH || (int)y + H <= 0 || (int)y >= SCREEN_HEIGHT) {
        return;
    }

    /* Coordinates relative to icon origin */
    /* Draw outer strokes (two crossing diagonals forming the rune) */
    draw_line_fb(x + 1, y + 1, x + 7, y + 8);   /* descending diagonal */
    draw_line_fb(x + 1, y + 15, x + 7, y + 8);  /* ascending diagonal */

    /* Draw inner vertical connector */
    draw_line_fb(x + 4, y + 2, x + 4, y + 14);

    /* Accent pixels to strengthen glyph at small size */
    set_pixel_fb(x + 3, y + 3, true);
    set_pixel_fb(x + 5, y + 3, true);
    set_pixel_fb(x + 3, y + 13, true);
    set_pixel_fb(x + 5, y + 13, true);

    /* Fill small kite shapes near center to approximate original art */
    fill_triangle_fb(x + 3, y + 2, x + 4, y + 6, x + 5, y + 2, true);
    fill_triangle_fb(x + 3, y + 14, x + 4, y + 10, x + 5, y + 14, true);
}