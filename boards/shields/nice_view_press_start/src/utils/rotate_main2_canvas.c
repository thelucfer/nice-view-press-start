#include "../../include/utils/rotate_main2_canvas.h"

#include "../../include/main.h"

void rotate_main2_canvas(void) {
    /* No-op for the monochrome framebuffer port.
       Rotation/orientation was previously handled using LVGL canvases.
       For the SSD1306/128x64 port we render 'main2' content directly into
       the packed 1bpp framebuffer. This function is retained to preserve
       the original API but intentionally does nothing to avoid LVGL
       dependencies in the monochrome path. */
    (void)MAIN2_CANVAS_WIDTH;
    (void)MAIN2_CANVAS_HEIGHT;
}
