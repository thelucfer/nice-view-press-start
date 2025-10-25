#include "../../include/utils/draw_animation2.h"
#include "../../include/main.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/*
 * Framebuffer-based animation renderer for animation2.
 *
 * This implementation expects a generated header that provides:
 *   - static const uint8_t animation2_frames[][BYTES_PER_FRAME] = { ... };
 *   - static const unsigned animation2_frame_count = N;
 *
 * The conversion tooling used earlier in this project produces:
 *   boards/shields/nice_view_press_start/include/images/animation2_frames_mono.h
 *
 * Each frame must be a packed 1bpp framebuffer matching SCREEN_FB_BYTES
 * (row-major, MSB-first). This function copies the requested frame into the
 * global `screen_buffer` and flushes the OLED with `oled_update_framebuffer()`.
 */

/* Include the generated frames header. If the header is missing at build time
 * the build will fail, which is desirable because the animation data is
 * required for this renderer.
 */
#include "../../include/images/animation2_frames_mono.h"

/* Backwards compatibility: some code/processes expect FB_BYTES named symbol. */
#ifndef FB_BYTES
#define FB_BYTES SCREEN_FB_BYTES
#endif

/* Ensure a visible prototype for the OLED update shim */
int oled_update_framebuffer(void);

/* Primary framebuffer-based renderer:
 *
 * - index: arbitrary unsigned index; frames are selected modulo the available
 *          frame count so callers can increment indefinitely.
 *
 * Behavior:
 * - If no frames are available, the function is a no-op.
 * - If the generated frames are smaller than the framebuffer, the remainder of
 *   the buffer is cleared (defensive).
 * - If the generated frames are larger than the framebuffer, only the first
 *   FB_BYTES are copied (defensive).
 */
void draw_animation2(unsigned index) {
    /* Guard: no frames available */
    if (animation2_frame_count == 0) {
        return;
    }

    /* Wrap index */
    unsigned frame = (unsigned)(index % animation2_frame_count);

    /* Compute sizes */
    size_t src_frame_size = sizeof(animation2_frames[0]);
    size_t dst_frame_size = (size_t)FB_BYTES;

    /* Defensive copy length */
    size_t copy_bytes = src_frame_size < dst_frame_size ? src_frame_size : dst_frame_size;

    /* Copy frame into the global framebuffer (packed 1bpp) */
    memcpy(screen_buffer, animation2_frames[frame], copy_bytes);

    /* If the source frame is smaller, clear the rest */
    if (copy_bytes < dst_frame_size) {
        memset(screen_buffer + copy_bytes, 0x00, dst_frame_size - copy_bytes);
    }

    /* Flush to the display. The implementation of oled_update_framebuffer()
     * is responsible for writing `screen_buffer` to the SSD1306 device.
     */
    (void)oled_update_framebuffer();
}

/* Optional LVGL-compatible wrapper:
 *
 * Some parts of the original shield expected a signature taking an LVGL canvas
 * pointer. Provide an on-demand wrapper when LVGL is available so existing
 * LVGL-based call sites can still compile and function (the canvas parameter
 * is ignored in the framebuffer port).
 */
#ifdef __has_include
#  if __has_include(<lvgl.h>)
void draw_animation2_lv(lv_obj_t* canvas, unsigned index) {
    (void)canvas; /* not used in framebuffer mode */
    draw_animation2(index);
}
#  endif
#endif