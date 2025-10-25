#include "../../include/utils/rotate_connectivity_canvas.h"
#include "../../include/main.h"

void rotate_connectivity_canvas(void) {
    /* No-op for the monochrome framebuffer (SSD1306) port.
       Rotation was previously implemented using LVGL canvases and transforms.
       For the packed 1bpp framebuffer path we compose the final buffer
       directly; this helper is preserved to maintain the original API but
       intentionally does nothing to avoid LVGL dependencies. */
    (void)CONNECTIVITY_CANVAS_WIDTH;
    (void)CONNECTIVITY_CANVAS_HEIGHT;
}
