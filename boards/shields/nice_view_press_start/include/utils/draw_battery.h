#pragma once

#include <stdint.h>
#include <stdbool.h>

/* Battery state reported by ZMK listeners */
struct battery_state {
    uint8_t level;
    bool is_charging;
};

/* Framebuffer-based drawer for the battery icon.
 *
 * On the monochrome SSD1306 port we draw directly into the packed 1bpp
 * `screen_buffer`, so this function accepts pixel coordinates rather than
 * LVGL canvas objects.
 */
void draw_battery(uint16_t x, uint16_t y, struct battery_state state);
