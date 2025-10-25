#include "../../include/utils/draw_battery.h"
#include "../../include/main.h"
#include "../../include/colors.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/*
 * Framebuffer-based battery drawer for the SSD1306 monochrome port.
 *
 * This implementation draws directly into the packed 1bpp global framebuffer
 * `screen_buffer` defined in `main.h`. The packing assumed is row-major,
 * MSB-first per byte (byte_per_row = SCREEN_WIDTH/8).
 *
 * The battery art is a small icon (originally 25x24-ish in the LVGL layout).
 * We implement a compact outline and a filled bar proportional to the
 * reported battery percentage. Coordinates are relative to the top-left
 * of the screen (x,y).
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
    uint8_t bit = 1u << (7 - (x % 8)); /* MSB-first */
    if (v) {
        screen_buffer[byte_index] |= bit;
    } else {
        screen_buffer[byte_index] &= ~bit;
    }
}

/* Draw a rectangle outline into the framebuffer */
static void draw_rect_outline_fb(int x, int y, int w, int h, bool set) {
    for (int i = 0; i < w; i++) {
        set_pixel_fb(x + i, y, set);
        set_pixel_fb(x + i, y + h - 1, set);
    }
    for (int j = 0; j < h; j++) {
        set_pixel_fb(x, y + j, set);
        set_pixel_fb(x + w - 1, y + j, set);
    }
}

/* Fill a rectangle area into the framebuffer */
static void fill_rect_fb(int x, int y, int w, int h, bool set) {
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            set_pixel_fb(x + i, y + j, set);
        }
    }
}

/* Small lightning-bolt marker for charging state. Approximates the previous
 * LVGL pattern (drawn inside the battery). Coordinates are relative to battery
 * origin.
 */
static void draw_lightning_fb(int ox, int oy) {
    /* Pattern taken to fit inside the battery box used below */
    const int px[] = {8, 8, 7, 7, 6, 6, 6, 5, 5, 5, 4, 4, 4, 3, 3, 2, 2};
    const int py[] = {11, 12, 10, 11, 9, 10, 11, 9, 10, 11, 10, 11, 12, 10, 11, 9, 10};
    const int n = sizeof(px) / sizeof(px[0]);
    for (int i = 0; i < n; i++) {
        set_pixel_fb(ox + px[i], oy + py[i], true);
    }
}

/* Public API:
 * Draw the battery icon with its fill level. Coordinates are the top-left
 * where the battery artwork should be drawn.
 *
 * This is intentionally a simple, robust implementation that doesn't rely on
 * LVGL. It writes directly into the packed 1bpp framebuffer and returns.
 */
void draw_battery(uint16_t x, uint16_t y, struct battery_state state) {
    /* Battery art dimensions based on the original layout */
    const int BAT_W = 10;   /* overall width including terminals */
    const int BAT_H = 24;   /* overall height */
    const int INNER_X = x + 2;
    const int INNER_Y = y + 2;
    const int INNER_W = 7;
    const int INNER_H = 19; /* fillable height */

    /* Defensive bounds: if the icon would be off-screen, skip */
    if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT) {
        return;
    }

    /* Draw outline (foreground) */
    draw_rect_outline_fb(x + 10, y + 2, 1, 19, true); /* Top small terminal */
    draw_rect_outline_fb(x + 2, y + 22, 7, 1, true);  /* Right terminal line */
    draw_rect_outline_fb(x, y + 2, 1, 19, true);      /* Bottom */
    draw_rect_outline_fb(x + 2, y, 7, 1, true);       /* Left */

    /* Draw rounded-ish corners by clearing pixels at the interior corners */
    set_pixel_fb(x + 9, y + 1, true);
    set_pixel_fb(x + 9, y + 21, true);
    set_pixel_fb(x + 1, y + 21, true);
    set_pixel_fb(x + 1, y + 1, true);

    /* Draw small right-side terminal */
    fill_rect_fb(x + 4, y + 23, 3, 1, true);

    /* Compute filled height from state.level (0..100) — fill from bottom */
    int fill_h = (state.level * INNER_H) / 100;
    if (fill_h < 0) {
        fill_h = 0;
    } else if (fill_h > INNER_H) {
        fill_h = INNER_H;
    }

    /* Clear interior area first (background) */
    fill_rect_fb(INNER_X, INNER_Y, INNER_W, INNER_H, false);

    /* Fill the battery according to charge level (foreground) */
    if (fill_h > 0) {
        int fy = INNER_Y + (INNER_H - fill_h); /* start y for fill */
        fill_rect_fb(INNER_X, fy, INNER_W, fill_h, true);
    }

    /* Round the interior corners by clearing specific pixels (match LVGL look) */
    set_pixel_fb(INNER_X + 6, INNER_Y + 0, false);  /* Top left */
    set_pixel_fb(INNER_X + 6, INNER_Y + INNER_H - 1, false); /* Top right/ bottom */

    /* If charging, draw lightning bolt pattern inside */
    if (state.is_charging) {
        draw_lightning_fb(x, y);
    }
}

