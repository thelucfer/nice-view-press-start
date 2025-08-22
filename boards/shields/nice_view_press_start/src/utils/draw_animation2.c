#include "../../include/utils/draw_animation2.h"

#include <lvgl.h>
#include "../../include/images/animation2_background.h"
#include "../../include/images/animation2_flash.h"
#include "../../include/images/animation2_Aaim.h"
#include "../../include/images/animation2_Adraw.h"
#include "../../include/images/animation2_Aflash.h"
#include "../../include/images/animation2_Aflash2.h"
#include "../../include/images/animation2_Aflash3.h"
#include "../../include/images/animation2_Aholster.h"
#include "../../include/images/animation2_Alaugh.h"
#include "../../include/images/animation2_Astanding.h"
#include "../../include/images/animation2_Ao1.h"
#include "../../include/images/animation2_Ao2.h"
#include "../../include/images/animation2_Ao3.h"
#include "../../include/images/animation2_Ao4.h"
#include "../../include/images/animation2_Ao5.h"
#include "../../include/images/animation2_Ao6.h"
#include "../../include/images/animation2_Ao7.h"
#include "../../include/images/animation2_Ao8.h"
#include "../../include/images/animation2_Ao9.h"
#include "../../include/images/animation2_Aw1.h"
#include "../../include/images/animation2_Aw2.h"
#include "../../include/images/animation2_Aw3.h"
#include "../../include/images/animation2_Aw4.h"
#include "../../include/images/animation2_Aw5.h"
#include "../../include/images/animation2_Aw6.h"
#include "../../include/images/animation2_Aw7.h"
#include "../../include/images/animation2_Aw8.h"
#include "../../include/images/animation2_Aw9.h"
	
#include "../../include/images/animation2_Bw1.h"
#include "../../include/images/animation2_Bw2.h"
#include "../../include/images/animation2_Bw3.h"
#include "../../include/images/animation2_Bw4.h"
#include "../../include/images/animation2_Bw5.h"
#include "../../include/images/animation2_Bw6.h"
#include "../../include/images/animation2_Bw7.h"
#include "../../include/images/animation2_Bw8.h"
#include "../../include/images/animation2_Bw9.h"
#include "../../include/images/animation2_Baim.h"
#include "../../include/images/animation2_Bdraw.h"
#include "../../include/images/animation2_Bstanding.h"
#include "../../include/images/animation2_Bhit.h"
	
#include "../../include/images/animation2_Cw1.h"
#include "../../include/images/animation2_Cw2.h"
#include "../../include/images/animation2_Cw3.h"
#include "../../include/images/animation2_Cw4.h"
#include "../../include/images/animation2_Cw5.h"
#include "../../include/images/animation2_Cw6.h"
#include "../../include/images/animation2_Cw7.h"
#include "../../include/images/animation2_Cw8.h"
#include "../../include/images/animation2_Cw9.h"
#include "../../include/images/animation2_Caim.h"
#include "../../include/images/animation2_Cdraw.h"
#include "../../include/images/animation2_Cstanding.h"
#include "../../include/images/animation2_Chit1.h"
#include "../../include/images/animation2_Chit2.h"
#include "../../include/images/animation2_Chit3.h"
#include "../../include/images/animation2_Chit4.h"
#include "../../include/images/animation2_Chit5.h"
#include "../../include/images/animation2_Chit6.h"
#include "../../include/images/animation2_Chit7.h"
#include "../../include/images/animation2_Chit8.h"
#include "../../include/images/animation2_Chit9.h"
#include "../../include/images/animation2_Chit10.h"
#include "../../include/images/animation2_Chit11.h"
#include "../../include/images/animation2_Chit12.h"


void draw_animation2(lv_obj_t* canvas, unsigned index) {
    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);

    switch (index % 140) {
        case 1: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }

        case 2: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aw1, &img_dsc);
            break;
        }
 
        case 3: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aw2, &img_dsc);
            break;
        }

        case 4: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aw3, &img_dsc);
            break;
        }

        case 5: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aw4, &img_dsc);
            break;
        }

        case 6: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aw5, &img_dsc);
            break;
        }

        case 7: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aw6, &img_dsc);
            break;
        }

        case 8: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aw7, &img_dsc);
            break;
        }

        case 9: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aw8, &img_dsc);
            break;
        }

        case 10: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aw9, &img_dsc);
            break;
        }

        case 11: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Astanding, &img_dsc);
            break;
        }

        case 12: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Astanding, &img_dsc);
            break;
        }

        case 13: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Astanding, &img_dsc);
            break;
        }

        case 14: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Astanding, &img_dsc);
            break;
        }

        case 15: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Astanding, &img_dsc);
            break;
        }

        case 16: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Astanding, &img_dsc);
            break;
        }

        case 17: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Astanding, &img_dsc);
            break;
        }

        case 18: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Astanding, &img_dsc);
            break;
        }

        case 19: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Astanding, &img_dsc);
            break;
        }

        case 20: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Astanding, &img_dsc);
            break;
        }

        case 21: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Astanding, &img_dsc);
            break;
        }

        case 22: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Astanding, &img_dsc);
            break;
        }		

        case 23: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Adraw, &img_dsc);
            break;
        }

        case 24: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aaim, &img_dsc);
            break;
        }

        case 25: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aaim, &img_dsc);
            break;
        }

        case 26: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aflash, &img_dsc);
            break;
        }

        case 27: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aflash2, &img_dsc);
            break;
        }

        case 28: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aflash3, &img_dsc);
            break;
        }

        case 29: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Alaugh, &img_dsc);
            break;
        }

        case 30: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aaim, &img_dsc);
            break;
        }

        case 31: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Alaugh, &img_dsc);
            break;
        }

        case 32: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aaim, &img_dsc);
            break;
        }

        case 33: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Alaugh, &img_dsc);
            break;
        }

        case 34: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aaim, &img_dsc);
            break;
        }

        case 35: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Aholster, &img_dsc);
            break;
        }

        case 36: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Astanding, &img_dsc);
            break;
        }

        case 37: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Ao1, &img_dsc);
            break;
        }

        case 38: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Ao2, &img_dsc);
            break;
        }

        case 39: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Ao3, &img_dsc);
            break;
        }

        case 40: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Ao4, &img_dsc);
            break;
        }

        case 41: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Ao5, &img_dsc);
            break;
        }

        case 42: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Ao6, &img_dsc);
            break;
        }

        case 43: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Ao7, &img_dsc);
            break;
        }

        case 44: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Ao8, &img_dsc);
            break;
        }

        case 45: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Ao9, &img_dsc);
            break;
        }

        case 46: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }
        case 47: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }
        case 48: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }
        case 49: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }
        case 50: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }



        case 51: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bw1, &img_dsc);
            break;
        }

        case 52: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bw2, &img_dsc);
            break;
        }

        case 53: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bw2, &img_dsc);
            break;
        }

        case 54: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bw3, &img_dsc);
            break;
        }

        case 55: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bw4, &img_dsc);
            break;
        }

        case 56: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bw5, &img_dsc);
            break;
        }

        case 57: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bw6, &img_dsc);
            break;
        }

        case 58: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bw7, &img_dsc);
            break;
        }

        case 59: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bw8, &img_dsc);
            break;
        }

        case 60: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bw9, &img_dsc);
            break;
        }

        case 61: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bstanding, &img_dsc);
            break;
        }
        case 62: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bstanding, &img_dsc);
            break;
        }
        case 63: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bstanding, &img_dsc);
            break;
        }
        case 64: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bstanding, &img_dsc);
            break;
        }
        case 65: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bstanding, &img_dsc);
            break;
        }
        case 66: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bstanding, &img_dsc);
            break;
        }
        case 67: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bstanding, &img_dsc);
            break;
        }

        case 68: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bdraw, &img_dsc);
            break;
        }

        case 69: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Baim, &img_dsc);
            break;
        }

        case 70: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_flash, &img_dsc);
            break;
        }
        case 71: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bstanding, &img_dsc);
            break;
        }
        case 72: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bstanding, &img_dsc);
            break;
        }

        case 73: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bhit, &img_dsc);
            break;
        }
        case 74: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bhit, &img_dsc);
            break;
        }
        case 75: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bhit, &img_dsc);
            break;
        }
        case 76: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bhit, &img_dsc);
            break;
        }
        case 77: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }
        case 78: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bhit, &img_dsc);
            break;
        }
        case 79: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }

        case 80: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Bhit, &img_dsc);
            break;
        }
        case 81: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }
        case 82: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }
        case 83: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }
        case 84: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }
        case 85: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }

        case 86: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cw1, &img_dsc);
            break;
        }

        case 87: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cw2, &img_dsc);
            break;
        }

        case 88: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cw3, &img_dsc);
            break;
        }

        case 89: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cw4, &img_dsc);
            break;
        }

        case 90: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cw5, &img_dsc);
            break;
        }

        case 91: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cw6, &img_dsc);
            break;
        }

        case 92: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cw7, &img_dsc);
            break;
        }

        case 93: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cw8, &img_dsc);
            break;
        }

        case 94: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cw9, &img_dsc);
            break;
        }

        case 95: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cstanding, &img_dsc);
            break;
        }
        case 96: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cstanding, &img_dsc);
            break;
        }
        case 97: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cstanding, &img_dsc);
            break;
        }
        case 98: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cstanding, &img_dsc);
            break;
        }
        case 99: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cstanding, &img_dsc);
            break;
        }
        case 100: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cstanding, &img_dsc);
            break;
        }
        case 101: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cstanding, &img_dsc);
            break;
        }
        case 102: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cstanding, &img_dsc);
            break;
        }
        case 103: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cstanding, &img_dsc);
            break;
        }
        case 104: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cstanding, &img_dsc);
            break;
        }
        case 105: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cstanding, &img_dsc);
            break;
        }
        case 106: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cstanding, &img_dsc);
            break;
        }
        case 107: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cstanding, &img_dsc);
            break;
        }
        case 108: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cstanding, &img_dsc);
            break;
        }
        case 109: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cstanding, &img_dsc);
            break;
        }

        case 110: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Cdraw, &img_dsc);
            break;
        }

        case 111: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Caim, &img_dsc);
            break;
        }

        case 112: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Caim, &img_dsc);
            break;
        }

        case 113: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_flash, &img_dsc);
            break;
        }

        case 114: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit1, &img_dsc);
            break;
        }

        case 115: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit2, &img_dsc);
            break;
        }

        case 116: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit3, &img_dsc);
            break;
        }

        case 117: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit4, &img_dsc);
            break;
        }

        case 118: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit5, &img_dsc);
            break;
        }

        case 119: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit6, &img_dsc);
            break;
        }

        case 120: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit7, &img_dsc);
            break;
        }

        case 121: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit8, &img_dsc);
            break;
        }

        case 122: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit9, &img_dsc);
            break;
        }

        case 123: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit10, &img_dsc);
            break;
        }

        case 124: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit11, &img_dsc);
            break;
        }

        case 125: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit12, &img_dsc);
            break;
        }
        case 126: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit12, &img_dsc);
            break;
        }
        case 127: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit12, &img_dsc);
            break;
        }
        case 128: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit12, &img_dsc);
            break;
        }
        case 129: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit12, &img_dsc);
            break;
        }
        case 130: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit12, &img_dsc);
            break;
        }
        case 131: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }
        case 132: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit12, &img_dsc);
            break;
        }
        case 133: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }

        case 134: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_Chit12, &img_dsc);
            break;
        }
        case 135: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }
        case 136: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }
        case 137: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }
        case 138: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }
        case 139: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }
        case 140: {
            lv_canvas_draw_img(canvas, 0, 0, &animation2_background, &img_dsc);
            break;
        }


    }
}
