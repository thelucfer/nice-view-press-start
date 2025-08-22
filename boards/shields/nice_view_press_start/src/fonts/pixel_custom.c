/*******************************************************************************
 * Size: 15 px
 * Bpp: 1
 * Opts: --bpp 1 --size 15 --no-compress --stride 1 --align 1 --font PIxel custom.ttf --range 32-127 --format lvgl -o pixel_custom.c
 ******************************************************************************/

#include "../../include/fonts/pixel_custom.h"

#include <lvgl.h>

#ifndef PIXEL_CUSTOM
#define PIXEL_CUSTOM 1
#endif

#if PIXEL_CUSTOM

/*-----------------
 *    BITMAPS
 *----------------*/

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xf0, 0xf0,

    /* U+0022 "\"" */
    0xcf, 0x3c, 0xf3,

    /* U+0023 "#" */
    0x33, 0xc, 0xcf, 0xff, 0xff, 0x33, 0xc, 0xcf,
    0xff, 0xff, 0x33, 0xc, 0xc0,

    /* U+0024 "$" */
    0xc, 0xc, 0xc, 0x3f, 0x3f, 0xc0, 0xc0, 0x3c,
    0x3c, 0x3, 0x3, 0xfc, 0xfc, 0xc, 0xc,

    /* U+0025 "%" */
    0xf0, 0xfc, 0x3f, 0x33, 0xcc, 0xc, 0x3, 0x3,
    0x3c, 0xcf, 0xc3, 0xf0, 0xf0,

    /* U+0026 "&" */
    0x30, 0x30, 0xcc, 0xcc, 0x30, 0x30, 0xcc, 0xcc,
    0x33, 0x33,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x33, 0xcc, 0xcc, 0xcc, 0x33,

    /* U+0029 ")" */
    0xcc, 0x33, 0x33, 0x33, 0xcc,

    /* U+002A "*" */
    0x30, 0xcf, 0xff, 0x30, 0xcc, 0xf3,

    /* U+002B "+" */
    0x30, 0xcf, 0xff, 0x30, 0xc0,

    /* U+002C "," */
    0x33, 0xcc,

    /* U+002D "-" */
    0xff, 0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0xc, 0x30, 0xc3, 0x30, 0xcc, 0x30, 0xc3, 0x0,

    /* U+0030 "0" */
    0x3c, 0x3c, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x3c, 0x3c,

    /* U+0031 "1" */
    0x33, 0xcf, 0xc, 0x30, 0xc3, 0xc, 0xff, 0xf0,

    /* U+0032 "2" */
    0x3c, 0x3c, 0xc3, 0xc3, 0xc, 0xc, 0x30, 0x30,
    0xff, 0xff,

    /* U+0033 "3" */
    0x3c, 0x3c, 0xc3, 0xc3, 0xc, 0xc, 0xc3, 0xc3,
    0x3c, 0x3c,

    /* U+0034 "4" */
    0xc, 0xc, 0x3c, 0x3c, 0xcc, 0xcc, 0xff, 0xff,
    0xc, 0xc,

    /* U+0035 "5" */
    0xff, 0xff, 0xc0, 0xc0, 0x3c, 0x3c, 0x3, 0x3,
    0xfc, 0xfc,

    /* U+0036 "6" */
    0x3f, 0x3f, 0xc0, 0xc0, 0xfc, 0xfc, 0xc3, 0xc3,
    0x3c, 0x3c,

    /* U+0037 "7" */
    0xff, 0xff, 0x3, 0x3, 0xc, 0xc, 0x30, 0x30,
    0xc0, 0xc0,

    /* U+0038 "8" */
    0x3c, 0x3c, 0xc3, 0xc3, 0x3c, 0x3c, 0xc3, 0xc3,
    0x3c, 0x3c,

    /* U+0039 "9" */
    0x3c, 0x3c, 0xc3, 0xc3, 0x3f, 0x3f, 0x3, 0x3,
    0xfc, 0xfc,

    /* U+003A ":" */
    0xf0, 0xf0,

    /* U+003B ";" */
    0x33, 0x0, 0x33, 0xcc,

    /* U+003C "<" */
    0xc, 0x33, 0xc, 0xc3, 0x3, 0xc, 0xc, 0x30,

    /* U+003D "=" */
    0xff, 0xf0, 0x0, 0xff, 0xf0,

    /* U+003E ">" */
    0xc3, 0x3, 0xc, 0xc, 0x33, 0xc, 0xc3, 0x0,

    /* U+003F "?" */
    0x3f, 0x3f, 0xc3, 0xc3, 0xc, 0xc, 0x30, 0x30,
    0x0, 0x0, 0x30, 0x30,

    /* U+0040 "@" */
    0x3f, 0xf, 0xcc, 0xf, 0x3, 0xcf, 0xf3, 0xfc,
    0xcf, 0x33, 0xf, 0xc3, 0xf0,

    /* U+0041 "A" */
    0x30, 0xcc, 0xf3, 0xff, 0x3c, 0xf3, 0xcf, 0x30,

    /* U+0042 "B" */
    0xf3, 0xcc, 0xf3, 0xf3, 0xcc, 0xf3, 0xf3, 0xc0,

    /* U+0043 "C" */
    0x3c, 0xfc, 0x30, 0xc3, 0xc, 0x30, 0x3c, 0xf0,

    /* U+0044 "D" */
    0xf3, 0xcc, 0xf3, 0xcf, 0x3c, 0xf3, 0xf3, 0xc0,

    /* U+0045 "E" */
    0xff, 0xfc, 0x30, 0xf3, 0xcc, 0x30, 0xff, 0xf0,

    /* U+0046 "F" */
    0xff, 0xfc, 0x30, 0xf3, 0xcc, 0x30, 0xc3, 0x0,

    /* U+0047 "G" */
    0x3c, 0xfc, 0x30, 0xc3, 0xc, 0xf3, 0x3c, 0xf0,

    /* U+0048 "H" */
    0xcf, 0x3c, 0xf3, 0xff, 0xfc, 0xf3, 0xcf, 0x30,

    /* U+0049 "I" */
    0xff, 0xff, 0xf0,

    /* U+004A "J" */
    0xff, 0xf0, 0xc3, 0xc, 0x3c, 0xf3, 0xf3, 0xc0,

    /* U+004B "K" */
    0xcf, 0x3c, 0xf3, 0xf3, 0xcc, 0xf3, 0xcf, 0x30,

    /* U+004C "L" */
    0xcc, 0xcc, 0xcc, 0xcc, 0xff,

    /* U+004D "M" */
    0xc0, 0xf0, 0x3f, 0x3f, 0xcf, 0xcc, 0xf3, 0x3c,
    0xf, 0x3, 0xc0, 0xf0, 0x30,

    /* U+004E "N" */
    0xc3, 0xc3, 0xf3, 0xf3, 0xcf, 0xcf, 0xc3, 0xc3,
    0xc3, 0xc3,

    /* U+004F "O" */
    0x3c, 0x3c, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x3c, 0x3c,

    /* U+0050 "P" */
    0xf3, 0xcc, 0xf3, 0xf3, 0xcc, 0x30, 0xc3, 0x0,

    /* U+0051 "Q" */
    0x3f, 0xf, 0xcc, 0xf, 0x3, 0xcc, 0xf3, 0x3c,
    0x33, 0xc, 0x3c, 0xcf, 0x30,

    /* U+0052 "R" */
    0xf3, 0xcc, 0xf3, 0xf3, 0xcc, 0xf3, 0xcf, 0x30,

    /* U+0053 "S" */
    0x3f, 0x3f, 0xc0, 0xc0, 0x3c, 0x3c, 0x3, 0x3,
    0xfc, 0xfc,

    /* U+0054 "T" */
    0xff, 0xf3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc0,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x3c, 0x3c,

    /* U+0056 "V" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0x30, 0xc0,

    /* U+0057 "W" */
    0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xcc, 0xf3, 0x3f,
    0x3f, 0xcf, 0xc0, 0xf0, 0x30,

    /* U+0058 "X" */
    0xcf, 0x3c, 0xf3, 0x30, 0xcc, 0xf3, 0xcf, 0x30,

    /* U+0059 "Y" */
    0xcf, 0x3c, 0xf3, 0x30, 0xc3, 0xc, 0x30, 0xc0,

    /* U+005A "Z" */
    0xff, 0xf0, 0xc3, 0x30, 0xcc, 0x30, 0xff, 0xf0,

    /* U+005B "[" */
    0xff, 0xcc, 0xcc, 0xcc, 0xff,

    /* U+005C "\\" */
    0xc3, 0xc, 0x30, 0x30, 0xc0, 0xc3, 0xc, 0x30,

    /* U+005D "]" */
    0xff, 0x33, 0x33, 0x33, 0xff,

    /* U+005E "^" */
    0x30, 0xcc, 0xf3,

    /* U+005F "_" */
    0xff, 0xf0,

    /* U+0060 "`" */
    0xcc, 0x33,

    /* U+007B "{" */
    0x3c, 0xf3, 0xc, 0xc3, 0x3, 0xc, 0x3c, 0xf0,

    /* U+007C "|" */
    0xff, 0xff, 0xf0,

    /* U+007D "}" */
    0xf3, 0xc3, 0xc, 0xc, 0x33, 0xc, 0xf3, 0xc0,

    /* U+007E "~" */
    0x30, 0xcc, 0x3c, 0xcf, 0x33, 0xc3, 0x30, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 22, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 65, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 131, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 7, .adv_w = 196, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 164, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 35, .adv_w = 196, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 65, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 59, .adv_w = 98, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 98, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 131, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 75, .adv_w = 131, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 80, .adv_w = 65, .box_w = 4, .box_h = 4, .ofs_x = -2, .ofs_y = -2},
    {.bitmap_index = 82, .adv_w = 131, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 84, .adv_w = 65, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 85, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 65, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 65, .box_w = 4, .box_h = 8, .ofs_x = -2, .ofs_y = -2},
    {.bitmap_index = 197, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 131, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 210, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 164, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 196, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 65, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 98, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 196, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 372, .adv_w = 196, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 429, .adv_w = 196, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 98, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 471, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 479, .adv_w = 98, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 131, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 487, .adv_w = 131, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 489, .adv_w = 98, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 491, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 65, .box_w = 2, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 196, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/


/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};


/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t pixel_custom = {
#else
lv_font_t pixel_custom = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};

#endif /*#if PIXEL_CUSTOM*/
