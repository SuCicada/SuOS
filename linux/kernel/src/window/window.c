//
// Created by SuCicada on 2023/06/19.
//
#include "screen.h"
#include "color.h"

void init_screen(unsigned char *buf, int xsize, int ysize) {
//    int xsize = DISPLAY_X_SIZE, ysize = DISPLAY_Y_SIZE;
    boxfill8(buf, xsize, BACK_COLOR, 0,0, xsize - 1, ysize - 29);
    boxfill8(buf, xsize, COL8_C6C6C6, 0, ysize - 28, xsize - 1, ysize - 28);
    boxfill8(buf, xsize, COL8_FFFFFF, 0, ysize - 27, xsize - 1, ysize - 27);
    boxfill8(buf, xsize, COL8_C6C6C6, 0, ysize - 26, xsize - 1, ysize - 1);

    boxfill8(buf, xsize, COL8_FFFFFF, 3, ysize - 24, 59, ysize - 24);
    boxfill8(buf, xsize, COL8_FFFFFF, 2, ysize - 24, 2, ysize - 4);
    boxfill8(buf, xsize, COL8_848484, 3, ysize - 4, 59, ysize - 4);
    boxfill8(buf, xsize, COL8_848484, 59, ysize - 23, 59, ysize - 5);
    boxfill8(buf, xsize, COL8_000000, 2, ysize - 3, 59, ysize - 3);
    boxfill8(buf, xsize, COL8_000000, 60, ysize - 24, 60, ysize - 3);

    boxfill8(buf, xsize, COL8_848484, xsize - 47, ysize - 24, xsize - 4, ysize - 24);
    boxfill8(buf, xsize, COL8_848484, xsize - 47, ysize - 23, xsize - 47, ysize - 4);
    boxfill8(buf, xsize, COL8_FFFFFF, xsize - 47, ysize - 3, xsize - 4, ysize - 3);
    boxfill8(buf, xsize, COL8_FFFFFF, xsize - 3, ysize - 24, xsize - 3, ysize - 3);
}
