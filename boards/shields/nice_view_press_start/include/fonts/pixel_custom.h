#pragma once

/* Make LVGL optional for builds that don't include it. If LVGL is available,
 * include it and use the real `lv_font_t`. Otherwise provide a minimal fallback
 * typedef so code including this header can compile in framebuffer-only builds.
 */
#ifdef __has_include
#  if __has_include(<lvgl.h>)
#    include <lvgl.h>
#  else
typedef struct { const void *data; } lv_font_t;
#  endif
#else
typedef struct { const void *data; } lv_font_t;
#endif

extern const lv_font_t pixel_custom;
