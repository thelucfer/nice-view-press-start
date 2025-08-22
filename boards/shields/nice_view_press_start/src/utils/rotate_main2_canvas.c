#include "../../include/utils/rotate_main2_canvas.h"

#include <lvgl.h>
#include "../../include/main.h"
#include "../../include/colors.h"

void rotate_main2_canvas() {
    static lv_color_t cbuf_tmp[LV_CANVAS_BUF_SIZE_TRUE_COLOR(MAIN2_CANVAS_WIDTH, MAIN2_CANVAS_HEIGHT)];
    memcpy(cbuf_tmp, main2_canvas_buffer, sizeof(cbuf_tmp));

    lv_img_dsc_t img;
    img.data = (void*)cbuf_tmp;
    img.header.cf = LV_IMG_CF_TRUE_COLOR;
    img.header.w = MAIN2_CANVAS_WIDTH;
    img.header.h = MAIN2_CANVAS_HEIGHT;

    lv_canvas_fill_bg(main2_canvas, BACKGROUND_COLOR, LV_OPA_COVER);
    lv_canvas_transform(
        main2_canvas,
        &img,
        900, LV_IMG_ZOOM_NONE,
        -1, 0,
        MAIN2_CANVAS_WIDTH / 2, MAIN2_CANVAS_HEIGHT / 2,
        false
    );
}
