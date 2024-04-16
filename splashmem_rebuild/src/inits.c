#include "inits.h"

uint32_t *init_colors(uint32_t num) {
    static uint32_t color_set[4];
    switch (num) {
        case 1:
            color_set[0] = 255;
            color_set[1] = 0;
            color_set[2] = 0;
            color_set[3] = 255;
            break;
        case 2:
            color_set[0] = 0;
            color_set[1] = 255;
            color_set[2] = 0;
            color_set[3] = 255;
            break;
        case 3:
            color_set[0] = 0;
            color_set[1] = 0;
            color_set[2] = 255;
            color_set[3] = 255;
            break;
        case 4:
            color_set[0] = 255;
            color_set[1] = 127;
            color_set[2] = 0;
            color_set[3] = 255;
            break;
        case 5:
            color_set[0] = 127;
            color_set[1] = 255;
            color_set[2] = 0;
            color_set[3] = 255;
            break;
        case 6:
            color_set[0] = 0;
            color_set[1] = 255;
            color_set[2] = 255;
            color_set[3] = 255;
            break;
        case 7:
            color_set[0] = 255;
            color_set[1] = 0;
            color_set[2] = 180;
            color_set[3] = 255;
            break;
        case 8:
            color_set[0] = 255;
            color_set[1] = 255;
            color_set[2] = 0;
            color_set[3] = 255;
            break;
        default:
            color_set[0] = 0;
            color_set[1] = 0;
            color_set[2] = 0;
            color_set[3] = 255;
    }
    return color_set;
}
