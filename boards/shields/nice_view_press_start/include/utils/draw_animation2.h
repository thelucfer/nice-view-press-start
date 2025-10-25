#pragma once

/*
 * Framebuffer-native draw header for animation2.
 *
 * - LVGL is optional: if LVGL is available the real headers will be included.
 *   Otherwise we provide a minimal `lv_obj_t` typedef so code compiled without
 *   LVGL doesn't break.
 *
 * - The primary API is framebuffer-based: `draw_animation2(unsigned index)`
 *   copies a packed 1bpp fullscreen frame into the global `screen_buffer`
 *   and flushes the OLED. This avoids any dependency on LVGL canvas objects.
 *
 * - For source-compatibility with existing LVGL code a thin LVGL wrapper
 *   declaration is provided when LVGL headers are present.
 */

#ifdef __has_include
#  if __has_include(<lvgl.h>)
#    include <lvgl.h>
#  else
/* Minimal fallback so translation units that reference `lv_obj_t` compile
 * when LVGL is not available during static analysis or framebuffer-only
 * builds.
 */
typedef void lv_obj_t;
#  endif
#else
typedef void lv_obj_t;
#endif

/* Pull in framebuffer layout / helper declarations */
#include "../main.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Draw the animation frame with the given index into the global framebuffer
 * and flush the display. Index is modulo the available frame count.
 *
 * This is the preferred, LVGL-free API for the Corne SSD1306 framebuffer port.
 */
void draw_animation2(unsigned index);

/* Optional LVGL-compatible wrapper declaration:
 *
 * When LVGL is available a wrapper `draw_animation2_lv` may be provided by
 * the implementation to preserve compatibility with callers that still pass
 * an LVGL canvas object. The wrapper is only declared when LVGL headers are
 * present.
 */
#ifdef __has_include
#  if __has_include(<lvgl.h>)
void draw_animation2_lv(lv_obj_t *canvas, unsigned index);
#  endif
#endif

#ifdef __cplusplus
}
#endif