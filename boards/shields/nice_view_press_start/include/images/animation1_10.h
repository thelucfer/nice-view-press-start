#pragma once

#include <stdint.h>
#include <stddef.h>

/* Make LVGL optional for builds that don't include it. If LVGL is available,
 * include it and use the real `lv_img_dsc_t`. Otherwise provide a minimal
 * fallback typedef so code including this header can compile in framebuffer-
 * only builds.
 */
#ifdef __has_include
#  if __has_include(<lvgl.h>)
#    include <lvgl.h>
#  else
typedef struct {
    struct {
        int cf;
        int always_zero;
        int reserved;
        int w;
        int h;
    } header;
    size_t data_size;
    const uint8_t *data;
} lv_img_dsc_t;
#  endif
#else
typedef struct {
    struct {
        int cf;
        int always_zero;
        int reserved;
        int w;
        int h;
    } header;
    size_t data_size;
    const uint8_t *data;
} lv_img_dsc_t;
#endif

extern const lv_img_dsc_t animation1_10;