#include "../../include/utils/draw_animation1.h"
#include "../../include/main.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>

/* Provide FB_BYTES compatibility alias for the framebuffer size used by the
 * rest of the shield. Some translation units reference FB_BYTES; ensure it
 * maps to SCREEN_FB_BYTES from main.h when not already defined.
 */
#ifndef FB_BYTES
#define FB_BYTES SCREEN_FB_BYTES
#endif

/* Declare OLED framebuffer update helper prototype so this TU has a visible
 * prototype and does not rely on implicit function declarations.
 */
int oled_update_framebuffer(void);

/*
 * Framebuffer-based animation renderer for animation1.
 *
 * This implementation expects a generated header that provides:
 *   - static const uint8_t animation1_frames[][BYTES_PER_FRAME] = { ... };
 *   - static const unsigned animation1_frame_count = N;
 *
 * The conversion tool generates:
 *   boards/shields/nice_view_press_start/include/images/animation1_frames_mono.h
 *
 * Each frame is assumed to be a packed 1bpp framebuffer matching FB_BYTES
 * (row-major, MSB-first). This function copies the requested frame into the
 * global `screen_buffer` and flushes the OLED with `oled_update_framebuffer()`.
 */

/* Generated frames header (created by tools/convert_gif_to_mono.py) */
#include "../../include/images/animation1_frames_mono.h"

void draw_animation1(unsigned index) {
    /* Guard: no frames available */
    if (animation1_frame_count == 0) {
        return;
    }

    /* Ensure we use a valid index */
    unsigned frame = (unsigned)(index % animation1_frame_count);

    /* Determine size of a source frame (in case the generated header differs) */
    size_t src_frame_size = sizeof(animation1_frames[0]);
    size_t dst_frame_size = (size_t)FB_BYTES;

    /* Copy as many bytes as fit into the destination framebuffer.
       In the expected case src_frame_size == dst_frame_size == FB_BYTES. */
    size_t copy_bytes = src_frame_size < dst_frame_size ? src_frame_size : dst_frame_size;

    memcpy(screen_buffer, animation1_frames[frame], copy_bytes);

    /* If the source frame was smaller than the full framebuffer, clear the
       remainder to avoid leaving old pixels. This is defensive and unlikely
       to be needed if the generator produced full-screen frames. */
    if (copy_bytes < dst_frame_size) {
        memset(screen_buffer + copy_bytes, 0x00, dst_frame_size - copy_bytes);
    }

    /* Flush to physical display. Ignore return code here — caller/listeners
       may handle retries/logging separately. */
    (void)oled_update_framebuffer();
}