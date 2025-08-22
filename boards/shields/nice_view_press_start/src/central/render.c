#include "../../include/central/render.h"

#include <ctype.h>
#include <lvgl.h>
#include <stdlib.h>
#include <string.h>
#include <zephyr/sys/util.h>
#include <zephyr/kernel.h>
#include <zephyr/random/random.h>
#include "../../include/colors.h"
#include "../../include/central/initialize_listeners.h"
#include "../../include/fonts/pixel_custom.h"
#include "../../include/main.h"
#include "../../include/utils/draw_battery.h"
#include "../../include/utils/draw_animation2.h"
#include "../../include/utils/draw_bluetooth_searching.h"
#include "../../include/utils/draw_bluetooth_logo_outlined.h"
#include "../../include/utils/draw_bluetooth_logo.h"
#include "../../include/utils/draw_usb_logo.h"
#include "../../include/utils/rotate_connectivity_canvas.h"
#include "../../include/utils/rotate_main2_canvas.h"



void render_battery() {
    lv_canvas_fill_bg(battery_canvas, BACKGROUND_COLOR, LV_OPA_COVER);

    draw_battery(battery_canvas,  5, 5, states.battery);
}

static void render_bluetooth_logo() {
    if (states.connectivity.active_profile_bonded) {
        if (states.connectivity.active_profile_connected) {
            draw_bluetooth_logo(connectivity_canvas, 18, 15);
        } else {
            draw_bluetooth_logo_outlined(connectivity_canvas, 18,  15);
        }
    } else {
        draw_bluetooth_searching(connectivity_canvas, 18, 15);
    }
}

static void render_bluetooth_profile_index() {
	
	
	int unsigned random = sys_rand32_get() & 1;
	
    lv_draw_label_dsc_t label_dsc;
    lv_draw_label_dsc_init(&label_dsc);
    label_dsc.color = FOREGROUND_COLOR;
    label_dsc.font = &pixel_custom;
    label_dsc.align = LV_TEXT_ALIGN_RIGHT;

    static const unsigned custom_font_22_height = 19;
    static const unsigned width = CONNECTIVITY_CANVAS_WIDTH - 18;
    static const char bluetooth_profile_label[5][2] = {"1", "2", "3", "4", "5"};
    const char* label = bluetooth_profile_label[states.connectivity.active_profile_index];
   
    lv_canvas_draw_text(connectivity_canvas, 2, 16, width, &label_dsc, random);
}

static void render_bluetooth_connectivity() {
    render_bluetooth_logo();
    render_bluetooth_profile_index();
}

static void render_usb_connectivity() {
    draw_usb_logo(connectivity_canvas, 11, 19);
}

void render_connectivity() {
    lv_canvas_fill_bg(connectivity_canvas, BACKGROUND_COLOR, LV_OPA_COVER);

    switch (states.connectivity.selected_endpoint.transport) {
        case ZMK_TRANSPORT_BLE: {
            render_bluetooth_connectivity();
            break;
        }
        case ZMK_TRANSPORT_USB: {
            render_usb_connectivity();
            break;
        }
    }

    rotate_connectivity_canvas();
}




void render_main() {	

#if IS_ENABLED(CONFIG_NICE_VIEW_PRESS_START_BACKGROUND)

		draw_animation1(main_canvas, states.background_index);

#endif
}


#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)

void render_main2() {	

    lv_canvas_fill_bg(main2_canvas, BACKGROUND_COLOR, LV_OPA_COVER);

	    // Capitalize the layer name if given or use the layer number otherwise.
    char* text = NULL;
    if (states.layer.name == NULL) {
        text = malloc(10 * sizeof(char));
        sprintf(text, "LAYER %i", states.layer.index);
    }
    else {
        text = malloc((strlen(states.layer.name) + 1) * sizeof(char));
        for (unsigned i = 0; states.layer.name[i] != '\0'; i++) {
            text[i] = toupper(states.layer.name[i]);
        }
        text[strlen(states.layer.name)] = '\0';
    }

    lv_draw_label_dsc_t layer_name_dsc;
    lv_draw_label_dsc_init(&layer_name_dsc);
    layer_name_dsc.color = FOREGROUND_COLOR;
    layer_name_dsc.font = &pixel_custom;
    layer_name_dsc.align = LV_TEXT_ALIGN_CENTER;

    lv_canvas_draw_text(
        main2_canvas,
        0,
        53,
        MAIN2_CANVAS_WIDTH,
        &layer_name_dsc,
        text
    );

    free(text);
    text = NULL;
	
	rotate_main2_canvas();
 
}
#endif