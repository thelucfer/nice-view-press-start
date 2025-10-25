#pragma once

/* This header is used by both the LVGL-based path and the framebuffer (mono)
 * path. Some build environments (framebuffer-only) do not provide LVGL, so
 * provide a lightweight conditional fallback that keeps the external symbol
 * available without forcing an LVGL dependency.
 *
 * - If LVGL is available, include it and use the real `lv_img_dsc_t`.
 * - Otherwise, declare a minimal placeholder `lv_img_dsc_t` so code that
 *   references `bluetooth_logo` can still compile in framebuffer mode.
 */

#ifdef __has_include
#  if __has_include(<lvgl.h>)
#    include <lvgl.h>
#  else
/* Minimal fallback definition of the LVGL image descriptor type so the
 * shield can be built without pulling in LVGL. This placeholder is intentionally
 * opaque and only exists to allow translation units that include this header
 * to compile in the framebuffer-only build.
 */
typedef struct { const void *data; } lv_img_dsc_t;
#  endif
#else
/* Compiler doesn't support __has_include — assume LVGL not present and
 * provide the fallback descriptor type.
 */
typedef struct { const void *data; } lv_img_dsc_t;
#endif

extern const lv_img_dsc_t bluetooth_logo;
