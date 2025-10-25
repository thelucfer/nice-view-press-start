#pragma once

#include <stdint.h>

/* Framebuffer-based signature: draw the outlined bluetooth glyph directly into
 * the packed 1bpp screen framebuffer at pixel coordinates (x, y).
 *
 * The previous LVGL canvas-based signature used LVGL types; for the SSD1306
 * framebuffer port we expose a simple integer coordinate API.
 */
void draw_bluetooth_logo_outlined(int x, int y);
