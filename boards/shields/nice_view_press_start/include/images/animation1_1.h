#pragma once

#include <stdint.h>
#include <stddef.h>

/* Make LVGL optional: if available include it, otherwise provide a tiny
 * fallback typedef for the lv_img_dsc_t used by generated image headers.
 */

#ifdef __has_include
#  if __has_include(<lvgl.h>)
#    include <lvgl.h>
#  else
/* Minimal fallback definition of LVGL image descriptor used by the
 * generated headers. This allows the image headers to be included in builds
 * that do not provide LVGL while keeping the original symbol names.
 */
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

extern const lv_img_dsc_t animation1_1;
