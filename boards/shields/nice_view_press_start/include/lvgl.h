#ifndef NICE_VIEW_PRESS_START_LVGL_STUB_H
#define NICE_VIEW_PRESS_START_LVGL_STUB_H

/*
 * Minimal lvgl.h stub for the framebuffer-only Corne SSD1306 port.
 *
 * This header provides lightweight typedefs, macros and no-op helpers so
 * translation units that include <lvgl.h> in the original project can
 * compile for a build that does not actually link LVGL.
 *
 * The implementations are intentionally minimal and safe: they do nothing,
 * only provide the symbols expected by the shield code.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* Basic LVGL types used across the shield */
typedef int16_t lv_coord_t;

/* Simple opaque object type */
typedef struct lv_obj {
    int _lv_stub;
} lv_obj_t;

/* Simple color type (monochrome builds will interpret values as needed) */
typedef uint32_t lv_color_t;

/* Color helpers (monochrome builds may ignore the numeric values) */
static inline lv_color_t lv_color_white(void) { return (lv_color_t)0xFFFFFFFFu; }
static inline lv_color_t lv_color_black(void) { return (lv_color_t)0x00000000u; }

/* Opacity constants */
#define LV_OPA_COVER 255

/* Image color formats (only a few are referenced by the repo) */
#define LV_IMG_CF_INDEXED_1BIT  0x01
#define LV_IMG_CF_TRUE_COLOR    0x02

/* Image descriptor type (minimal subset used by generated LVGL assets) */
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

/* Draw descriptors (minimal placeholders) */
typedef struct {
    int color;
    const void *font;
    int align;
} lv_draw_label_dsc_t;

static inline void lv_draw_label_dsc_init(lv_draw_label_dsc_t *d) {
    if (d) { d->color = 0; d->font = NULL; d->align = 0; }
}

typedef struct {
    int dummy;
} lv_draw_img_dsc_t;

static inline void lv_draw_img_dsc_init(lv_draw_img_dsc_t *d) {
    (void)d;
}

/* Font type placeholder (some generated font C files include lvgl.h) */
typedef struct { const void *d; } lv_font_t;

/* LVGL attribute macros used by generated sources - define empty */
#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif
#ifndef LV_ATTRIBUTE_LARGE_CONST
#define LV_ATTRIBUTE_LARGE_CONST
#endif
#ifndef LV_ATTRIBUTE_IMG
#define LV_ATTRIBUTE_IMG(name)
#endif

/* Canvas buffer size macro used by existing code.
 * Original LVGL calculates bytes for the chosen color format; the stub
 * provides a simple conservative size (number of pixels).
 */
#ifndef LV_CANVAS_BUF_SIZE_TRUE_COLOR
#define LV_CANVAS_BUF_SIZE_TRUE_COLOR(w, h) ((size_t)((w) * (h)))
#endif

/* Text alignment constants (minimal) */
#define LV_TEXT_ALIGN_LEFT   0
#define LV_TEXT_ALIGN_CENTER 1
#define LV_TEXT_ALIGN_RIGHT  2

/* Minimal no-op implementations of LVGL functions used by the shield.
 * Functions are inline to avoid link-time issues and are intentionally
 * empty.
 */

static inline lv_obj_t *lv_obj_create(lv_obj_t *parent) {
    (void)parent;
    return NULL;
}
static inline void lv_obj_set_size(lv_obj_t *obj, lv_coord_t w, lv_coord_t h) {
    (void)obj; (void)w; (void)h;
}
static inline lv_obj_t *lv_canvas_create(lv_obj_t *parent) {
    (void)parent;
    return NULL;
}
static inline void lv_canvas_set_buffer(lv_obj_t *canvas, void *buf, lv_coord_t w, lv_coord_t h, int cf) {
    (void)canvas; (void)buf; (void)w; (void)h; (void)cf;
}
static inline void lv_obj_align(lv_obj_t *obj, int align, lv_coord_t x, lv_coord_t y) {
    (void)obj; (void)align; (void)x; (void)y;
}
static inline void lv_canvas_fill_bg(lv_obj_t *canvas, lv_color_t color, int opa) {
    (void)canvas; (void)color; (void)opa;
}
static inline void lv_canvas_draw_text(lv_obj_t *canvas, lv_coord_t x, lv_coord_t y, lv_coord_t width, const lv_draw_label_dsc_t *dsc, const char *txt) {
    (void)canvas; (void)x; (void)y; (void)width; (void)dsc; (void)txt;
}
static inline void lv_canvas_draw_img(lv_obj_t *canvas, lv_coord_t x, lv_coord_t y, const lv_img_dsc_t *img, const lv_draw_img_dsc_t *img_dsc) {
    (void)canvas; (void)x; (void)y; (void)img; (void)img_dsc;
}

/* Timer and helper types used in some files: provide safe stubs */
typedef void lv_timer_t;
static inline lv_timer_t *lv_timer_create(void (*cb)(lv_timer_t*), uint32_t period_ms, void *user_data) {
    (void)cb; (void)period_ms; (void)user_data;
    return NULL;
}
static inline void lv_timer_pause(lv_timer_t *t) { (void)t; }
static inline void lv_timer_resume(lv_timer_t *t) { (void)t; }

/* Minimal assert-like macro to silence unused warnings in generated code */
#ifndef LV_UNUSED
#define LV_UNUSED(x) (void)(x)
#endif

#endif /* NICE_VIEW_PRESS_START_LVGL_STUB_H */