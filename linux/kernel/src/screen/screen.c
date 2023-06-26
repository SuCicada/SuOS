//
// Created by Pengyifu on 2023/06/05.
//

#include "screen.h"
#include "color.h"
#include "log.h"

void boxfill8(unsigned char *vram, int xsize,
              unsigned char color,
              int x0, int y0, int x1, int y1) {
    int x, y;
    for (y = y0; y <= y1; y++) {
        for (x = x0; x <= x1; x++) {
            vram[y * xsize + x] = color;
        }
    }
}


void make_window8(unsigned char *buf, int xsize, int ysize, char *title) {
    static char closebtn[14][16] = {
            "OOOOOOOOOOOOOOO@",
            "OQQQQQQQQQQQQQ$@",
            "OQQQQQQQQQQQQQ$@",
            "OQQQ@@QQQQ@@QQ$@",
            "OQQQQ@@QQ@@QQQ$@",
            "OQQQQQ@@@@QQQQ$@",
            "OQQQQQQ@@QQQQQ$@",
            "OQQQQQ@@@@QQQQ$@",
            "OQQQQ@@QQ@@QQQ$@",
            "OQQQ@@QQQQ@@QQ$@",
            "OQQQQQQQQQQQQQ$@",
            "OQQQQQQQQQQQQQ$@",
            "O$$$$$$$$$$$$$$@",
            "@@@@@@@@@@@@@@@@"
    };

    int x, y;
    char c;
    boxfill8(buf, xsize, 8, 0, 0, xsize - 1, 0);
    boxfill8(buf, xsize, 7, 1, 1, xsize - 2, 1);
    boxfill8(buf, xsize, 8, 0, 0, 0, ysize - 1);
    boxfill8(buf, xsize, 7, 1, 1, 1, ysize - 2);
    boxfill8(buf, xsize, 15, xsize - 2, 1, xsize - 2, ysize - 2);
    boxfill8(buf, xsize, 0, xsize - 1, 0, xsize - 1, ysize - 1);
    boxfill8(buf, xsize, 8, 2, 2, xsize - 3, ysize - 3);
    boxfill8(buf, xsize, 12, 3, 3, xsize - 4, 20);
    boxfill8(buf, xsize, 15, 1, ysize - 2, xsize - 2, ysize - 2);
    boxfill8(buf, xsize, 0, 0, ysize - 1, xsize - 1, ysize - 1);


    puts8(buf, xsize, 24, 4, 7, title);
    //write the x button to the buf
    for (y = 0; y < 14; y++) {
        for (x = 0; x < 16; x++) {
            c = closebtn[y][x];
            if (c == '@')
                c = 0;
            else if (c == '$')
                c = 15;
            else if (c == 'Q')
                c = 8;
            else c = 7;
        }
        buf[(5 + y) * xsize + (xsize - 21 + x)] = c;


    }
    return;
}


SHTCTL *shtctl_init(unsigned char *vram, int xsize, int ysize) {
    SHTCTL *ctl;
    int i;
    ctl = (SHTCTL *) mem_alloc(sizeof(SHTCTL));
    log_println("sizeof(SHTCTL): %d", sizeof(SHTCTL));

    if (ctl == 0)
        return 0;

    ctl->map = (unsigned char *) mem_alloc(xsize * ysize);

    if (ctl->map == 0) {
        mem_free(ctl);
        return 0;
    }
    ctl->vram = vram;
    ctl->xsize = xsize;
    ctl->ysize = ysize;
    ctl->top = -1;  //no sheet

    for (i = 0; i < MAX_SHEETS; i++) {
        SHEET *sheet_ptr = &ctl->sheet[i];
        sheet_ptr->id = i;
        sheet_ptr->flags = 0;
        sheet_ptr->ctl = ctl;
    }
    return ctl;
}

SHEET *sheet_alloc(SHTCTL *ctl) {
    SHEET *sht;
    int i;
    for (i = 0; i < MAX_SHEETS; i++) {
        if (ctl->sheet[i].flags == 0) {
            sht = &ctl->sheet[i];
            sht->flags = 1;
            sht->height = -1;
            return sht;
        }
    }
    return 0;
}

void sheet_setbuf(SHEET *sht, unsigned char *buf, int xsize, int ysize, int col_inv) {
    sht->buf = buf;
    sht->bxsize = xsize;
    sht->bysize = ysize;
    sht->col_inv = col_inv;
    return;
}

/*
refresh absolute position, between:
 (vx0, vy0, layer) -> (vx1, vy1, layerend)


*/

unsigned char *vram_tmp;

void sheet_refreshsub0(SHTCTL *ctl,
                       int vx0, int vy0,
                       int vx1, int vy1,
                       int layer, int layerend) {
    int h, bx, by, vx, vy, bx0, bx1, by0, by1;
    unsigned char *buf, *vram = ctl->vram;
    unsigned char sid;
    unsigned char c;
    unsigned char *map = ctl->map;

    SHEET *sht;
    if (vx0 < 0) vx = 0;
    if (vy0 < 0) vy = 0;
    if (vx1 > ctl->xsize) vx1 = ctl->xsize;
    if (vy1 > ctl->ysize) vy1 = ctl->ysize;
    for (h = layer; h <= layerend; h++) {
        sht = ctl->sheets[h]; // current sheet
        sid = sht - ctl->sheet;
        buf = sht->buf;

        bx0 = vx0 - sht->vx0;
        by0 = vy0 - sht->vy0;

        bx1 = vx1 - sht->vx0;
        by1 = vy1 - sht->vy0;

        if (bx0 < 0)bx0 = 0;
        if (by0 < 0)by0 = 0;
        if (bx1 > sht->bxsize)bx1 = sht->bxsize;
        if (by1 > sht->bysize)by1 = sht->bysize;
        for (by = by0; by < by1; by++) {
            vy = sht->vy0 + by;
            for (bx = bx0; bx < bx1; bx++) {
                vx = sht->vx0 + bx;

                c = map[vy * ctl->xsize + vx];
                if (c == sid) {
                    vram[vy * ctl->xsize + vx] = buf[by * sht->bxsize + bx];;
                }
            }
        }
        // if(h==1)  while(1);
    }
}

void sheet_refreshsub(SHTCTL *ctl,
                      int vx0, int vy0,
                      int vx1, int vy1,
                      int layer, int layerend) {
    unsigned char *map = ctl->map;
    unsigned char *vram = ctl->vram;

    if (vx0 < 0) vx0 = 0;
    if (vy0 < 0) vy0 = 0;
    if (vx1 > ctl->xsize) vx1 = ctl->xsize;
    if (vy1 > ctl->ysize) vy1 = ctl->ysize;
    for (int h = layer; h <= layerend; h++) {
        debug("h:%d\n", h);
        SHEET *sht = ctl->sheets[h]; // sheet on current layer
        int sid = h + 1;

        unsigned char *buf = sht->buf;

        int sht_x0 = sht->vx0;
        int bx0 = (sht_x0 < vx0) * vx0 +
                  (sht_x0 >= vx0 && sht_x0 <= vx1) * sht_x0;

        int sht_x1 = sht->vx0 + sht->bxsize;
        int bx1 = (sht_x1 < vx0) * vx0 +
                  (vx0 <= sht_x1 && sht_x1 <= vx1) * sht_x1;

        int sht_y0 = sht->vy0;
        int by0 = (sht_y0 < vy0) * vy0 +
                  (vy0 <= sht_y0 && sht_y0 <= vy1) * sht_y0;

        int sht_y1 = sht->vy0 + sht->bysize;
        int by1 = (sht_y1 < vy0) * vy0 +
                  (vy0 <= sht_y1 && sht_y1 <= vy1) * sht_y1;

        for (int by = by0; by < by1; by++) {
            for (int bx = bx0; bx < bx1; bx++) {
                int from = (by - sht->vy0) * sht->bxsize + (bx - sht->vx0);
                int c = buf[from];
//                if (c != sht->col_inv) {
                int to = by * ctl->xsize + bx;
//                    map[to] = sid; // refresh
//                }
                if (map[to] == sid) {
                    vram[to] = c;
                }
            }
        }
    }
}

// 更新的层级：layer -> top
// relative position
//
void sheet_refreshmap(SHTCTL *ctl, int vx0, int vy0, int vx1, int vy1, int layer) {
//    int bx, by, vx, vy, bx0, by0, bx1, by1;
//    unsigned char *buf, *vram = ctl->vram;
    unsigned char *map = ctl->map;
//    unsigned char sid;
    unsigned char c;

    if (vx0 < 0) vx0 = 0;
    if (vy0 < 0) vy0 = 0;
    if (vx1 > ctl->xsize) vx1 = ctl->xsize;
    if (vy1 > ctl->ysize) vy1 = ctl->ysize;
    for (int h = layer; h <= ctl->top; h++) {
        debug("h:%d\n", h);
        SHEET *sht = ctl->sheets[h]; // sheet on current layer
        int sid = h + 1;
//        sid = sht - ctl->sheet;
        //printdebug((unsigned)sid,0);
        unsigned char *buf = sht->buf;

        int bx0, by0; // left right
        int bx1, by1;
        /*

         x0       x1
         |         |
         |         |
         xxxxxxxxxxx ------ y0
         |xxxxxxxxx|
         |xxxxxxxxx|
         |xxxxxxxxx|
         xxxxxxxxxxx ------- y1

         */
        // vx0, vy0, vx1, vy1 : refresh area
        // sht                : sht area
        // 1. sht x0 cmp  ref x0, x1
        int sht_x0 = sht->vx0;
        if (sht_x0 < vx0) { // left
            bx0 = vx0;
        } else if (sht_x0 >= vx0 && sht_x0 <= vx1) { // middle
            bx0 = sht_x0;
        } else if (sht_x0 > vx1) { // right
            // not overlap
        }

        // 等价的
        /*
        bx0 = (sht_x0 < vx0) * vx0 +
              (sht_x0 >= vx0 && sht_x0<= vx1) * sht_x0;
         */

        int sht_x1 = sht->vx0 + sht->bxsize;
        bx1 = (sht_x1 < vx0) * vx0 +
              (vx0 <= sht_x1 && sht_x1 <= vx1) * sht_x1;

        int sht_y0 = sht->vy0;
        by0 = (sht_y0 < vy0) * vy0 +
              (vy0 <= sht_y0 && sht_y0 <= vy1) * sht_y0;

        int sht_y1 = sht->vy0 + sht->bysize;
        by1 = (sht_y1 < vy0) * vy0 +
              (vy0 <= sht_y1 && sht_y1 <= vy1) * sht_y1;


//        // 这里是为了能圈出一个矩形，绘制区域和 sheet 相交的部分
//        bx0 = vx0 - sht->vx0; // 目标位置, 现在位置
//        by0 = vy0 - sht->vy0;
//
//        bx1 = vx1 - sht->vx0;
//        by1 = vy1 - sht->vy0;
//
//        if (bx0 < 0)bx0 = 0;
//        if (by0 < 0)by0 = 0;
//        if (bx1 > sht->bxsize)bx1 = sht->bxsize;
//        if (by1 > sht->bysize)by1 = sht->bysize;
        for (int by = by0; by < by1; by++) {
//            int vy = sht->vy0 + by;
//            debug("bx:%d,by:%d\n",bx,by);
            for (int bx = bx0; bx < bx1; bx++) {
//                int vx = sht->vx0 + bx;
                int from = (by - sht->vy0) * sht->bxsize + (bx - sht->vx0);
//                c = buf[by * sht->bxsize + bx];
                c = buf[from];
                if (c != sht->col_inv) {
//                    map[vy * ctl->xsize + vx] = sid;
                    int to = by * ctl->xsize + bx;
                    map[to] = sid; // refresh
                }
            }
        }
    }
}

void sheet_updown(SHEET *sht, int height) {
    int h, old = sht->height;
    SHTCTL *ctl = sht->ctl;
    if (height > ctl->top + 1) {
        height = ctl->top + 1;
    }

    if (height < -1) {
        height = -1;
    }
    sht->height = height;

    if (old > height) {
        // 降低
        if (height >= 0) {
            // 插入排序
            for (h = old; h > height; h--) {
                ctl->sheets[h] = ctl->sheets[h - 1];
                ctl->sheets[h]->height = h;
            }
            ctl->sheets[height] = sht;

            // 覆盖我
            sheet_refreshmap(ctl, sht->vx0, sht->vy0, sht->vx0 + sht->bxsize, sht->vy0 + sht->bysize, sht->height + 1);
            sheet_refreshsub(ctl, sht->vx0, sht->vy0, sht->vx0 + sht->bxsize, sht->vy0 + sht->bysize, sht->height + 1,
                             old);

        } else {
            if (ctl->top > old) {
                for (h = old; h < ctl->top; h++) {
                    ctl->sheets[h] = ctl->sheets[h + 1];
                    ctl->sheets[h]->height = h;
                }

            }
            ctl->top--;
            sheet_refreshmap(ctl, sht->vx0, sht->vy0, sht->vx0 + sht->bxsize, sht->vy0 + sht->bysize, 0);
            sheet_refreshsub(ctl, sht->vx0, sht->vy0, sht->vx0 + sht->bxsize, sht->vy0 + sht->bysize, 0, old - 1);

        }
    } else if (old < height) {

        if (old > 0) {

            for (h = old; h < height; h++) {
                ctl->sheets[h] = ctl->sheets[h + 1];
                ctl->sheets[h]->height = h;
            }
            ctl->sheets[height] = sht;
        } else {

            for (h = ctl->top; h >= height; h--) {
                ctl->sheets[h + 1] = ctl->sheets[h];
                ctl->sheets[h + 1]->height = h + 1;
            }
            ctl->sheets[height] = sht;
            ctl->top++;

        }
        sheet_refreshmap(ctl, sht->vx0, sht->vy0, sht->vx0 + sht->bxsize, sht->vy0 + sht->bysize, height);
        sheet_refreshsub(ctl, sht->vx0, sht->vy0, sht->vx0 + sht->bxsize, sht->vy0 + sht->bysize, height, height);
    }

}

// 相对位置
void sheet_refresh(SHEET *sht, int bx0, int by0, int bx1, int by1) {
    SHTCTL *ctl = sht->ctl;
    if (sht->height >= 0) {
        sheet_refreshsub(ctl, sht->vx0 + bx0, sht->vy0 + by0,
                         sht->vx0 + bx1, sht->vy0 + by1,
                         sht->height, sht->height);
    }
}

void sheet_move(SHEET *sht, int vx0, int vy0) {
    SHTCTL *ctl = sht->ctl;
    int old_vx0 = sht->vx0;
    int old_vy0 = sht->vy0;

    sht->vx0 = vx0;
    sht->vy0 = vy0;
    if (sht->height >= 0) {
        //移动之后map要重新生成
        sheet_refreshmap(ctl, old_vx0, old_vy0, old_vx0 + sht->bxsize, old_vy0 + sht->bysize, 0);
        sheet_refreshmap(ctl, vx0, vy0, vx0 + sht->bxsize, vy0 + sht->bysize, sht->height);
        //sheet_refresh(ctl);
        sheet_refreshsub(ctl, old_vx0, old_vy0, old_vx0 + sht->bxsize, old_vy0 + sht->bysize, 0, sht->height - 1);
        sheet_refreshsub(ctl, vx0, vy0, vx0 + sht->bxsize, vy0 + sht->bysize, sht->height, sht->height);
    }
    return;
}

void sheet_free(SHEET *sht) {
    if (sht->height >= 0)
        sheet_updown(sht, -1);

    sht->flags = 0;
    return;
}
