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
}

/*
refresh absolute position, between:
 (vx0, vy0, layer) -> (vx1, vy1, layerend)

 @args: c:  pixel color flag
        to: absolute position
*/
void sheet_refreshsub_0(SHTCTL *ctl,
                        SHEET *sht,
                        unsigned char c, int to) {
    int sid = sht->id;
    unsigned char *map = ctl->map;
    unsigned char *vram = ctl->vram;
//    log_println("sheet_refreshsub_0: sid: %d, c: %d, to: %d", sid, c, to);
    if (map[to] == sid) {
        vram[to] = c;
    }
}
/*
c: color of this site
 */
void sheet_refreshmap_0(SHTCTL *ctl,
                        SHEET *sht,
                        unsigned char c, int to) {
    int sid = sht->id;
    unsigned char *map = ctl->map;
    if (c != sht->col_inv) {
        map[to] = sid; // refresh
    }
}

void sheet_refresh_base(SHTCTL *ctl,
                        int vx0, int vy0,
                        int vx1, int vy1,
                        int layer, int layerend,
                        void (*refresh)(SHTCTL *ctl, SHEET *sht, unsigned char c, int to)) {
//    unsigned char *map = ctl->map;
//    unsigned char sid;

    if (vx0 < 0) vx0 = 0;
    if (vy0 < 0) vy0 = 0;
    if (vx1 > ctl->xsize) vx1 = ctl->xsize;
    if (vy1 > ctl->ysize) vy1 = ctl->ysize;
    int sum = 0;
    for (int h = layer; h <= layerend; h++) {
        debug("h:%d\n", h);
        SHEET *sht = ctl->sheets[h]; // sheet on current layer
//        int sid = h + 1;
//        int sid = sht->id;

//        sid = sht - ctl->sheet;
        //printdebug((unsigned)sid,0);
        unsigned char *buf = sht->buf;

        int bx0 = -1, by0 = -1; // left right
        int bx1 = -1, by1 = -1;
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
        } else if (vx0 <= sht_x0 && sht_x0 <= vx1) { // middle
            bx0 = sht_x0;
        } else if (sht_x0 > vx1) { // right
            // not overlap`
        }
        if (bx0 == -1) continue;

        // 等价的
        /*
        bx0 = (sht_x0 < vx0) * vx0 +
              (sht_x0 >= vx0 && sht_x0<= vx1) * sht_x0;
         */

        int sht_x1 = sht->vx0 + sht->bxsize;
        bx1 = (sht_x1 < vx0) * -1 +
              (vx0 <= sht_x1 && sht_x1 <= vx1) * sht_x1 +
              (vx1 < sht_x1) * vx1;
        if (bx1 == -1) continue;

        int sht_y0 = sht->vy0;
        by0 = (sht_y0 < vy0) * vy0 +
              (vy0 <= sht_y0 && sht_y0 <= vy1) * sht_y0 +
              (sht_y0 > vy1) * -1;
        if (by0 == -1) continue;

        int sht_y1 = sht->vy0 + sht->bysize;
        by1 = (sht_y1 < vy0) * -1 +
              (vy0 <= sht_y1 && sht_y1 <= vy1) * sht_y1 +
              (vy1 < sht_y1) * vy1;
        if (by1 == -1) continue;

        log_println("bx0:%d, by0:%d, bx1:%d, by1:%d", bx0, by0, bx1, by1);
        for (int by = by0; by < by1; by++) {
            for (int bx = bx0; bx < bx1; bx++) {
                int from = (by - sht->vy0) * sht->bxsize + (bx - sht->vx0);
                unsigned char c = buf[from];
//                if (c != sht->col_inv) {
                int to = by * ctl->xsize + bx;
//                    map[to] = sid; // refresh
//                }

                refresh(ctl, sht, c, to);
//                sum++;
            }
        }
    }
//    log_println("refresh calc sum:%d", sum);
}

void sheet_refreshsub(SHTCTL *ctl,
                      int vx0, int vy0,
                      int vx1, int vy1,
                      int layer, int layerend) {
    sheet_refresh_base(ctl, vx0, vy0, vx1, vy1, layer, layerend,
                       sheet_refreshsub_0);
}

// 更新的层级：layer -> top
// relative position
void sheet_refreshmap(SHTCTL *ctl, int vx0, int vy0, int vx1, int vy1, int layer) {
    sheet_refresh_base(ctl, vx0, vy0, vx1, vy1, layer, ctl->top,
                       sheet_refreshmap_0);
}

void __sheet_refreshmap(SHTCTL *ctl, int vx0, int vy0, int vx1, int vy1, int layer) {
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
//        int sid = h + 1;
        int sid = sht->id;

//        sid = sht - ctl->sheet;
        //printdebug((unsigned)sid,0);
        unsigned char *buf = sht->buf;

        int bx0 = -1, by0 = -1; // left right
        int bx1 = -1, by1 = -1;
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
            // not overlap`
        }
        if (bx0 == -1) continue;

        // 等价的
        /*
        bx0 = (sht_x0 < vx0) * vx0 +
              (sht_x0 >= vx0 && sht_x0<= vx1) * sht_x0;
         */

        int sht_x1 = sht->vx0 + sht->bxsize;
        bx1 = (sht_x1 < vx0) * -1 +
              (vx0 <= sht_x1 && sht_x1 <= vx1) * sht_x1 +
              (vx1 < sht_x1) * vx1;
        if (bx1 == -1) continue;

        int sht_y0 = sht->vy0;
        by0 = (sht_y0 < vy0) * vy0 +
              (vy0 <= sht_y0 && sht_y0 <= vy1) * sht_y0;
        if (by0 == -1) continue;

        int sht_y1 = sht->vy0 + sht->bysize;
        by1 = (sht_y1 < vy0) * -1 +
              (vy0 <= sht_y1 && sht_y1 <= vy1) * sht_y1 +
              (vy1 < sht_y1) * vy1;
        if (by1 == -1) continue;


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

    // 1. check
    if (height > ctl->top + 1) {
        height = ctl->top + 1;
    }

    if (height < -1) {
        height = -1;
    }

    // 2. update sheet
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
            // 初次出现，从顶向下交换
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

void show_block(const unsigned char *buf, int xsize, int ysize, unsigned char clo_inv) {
    log_info("====================================\n");
    for (int j = 0; j < ysize; ++j) {
        for (int i = 0; i < xsize; ++i) {
            unsigned char a = buf[i * xsize + j];
            if (a == clo_inv)
                log_info("%4c", '.');
            else
                log_info("%4d", a);
        }
        log_info("\n");
    }
}

void show_sheet(SHEET *sht) {
//    show_block(sht->buf, sht->bxsize, sht->bysize, sht->col_inv);
    unsigned char *buf = sht->ctl->map;
    int xsize = sht->ctl->xsize;
    log_info("====================================\n");
    for (int j = sht->vy0; j <= sht->vy0 + sht->bysize; ++j) {
        for (int i = sht->vx0; i <= sht->vx0 + sht->bxsize; ++i) {
            unsigned char a = buf[i * xsize + j];
            if (a == sht->col_inv)
                log_info("%4c", '.');
            else
                log_info("%4d", a);
        }
        log_info("\n");
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
        log_println("sheet_move:old_vx0:%d, old_vy0:%d  -> vx0:%d, vy0:%d", old_vx0, old_vy0, vx0, vy0);
        sheet_refreshmap(ctl, old_vx0, old_vy0,
                         old_vx0 + sht->bxsize, old_vy0 + sht->bysize,
                         0);
        sheet_refreshmap(ctl, vx0, vy0,
                         vx0 + sht->bxsize, vy0 + sht->bysize,
                         sht->height);
        //sheet_refresh(ctl);

        sheet_refreshsub(ctl, old_vx0, old_vy0,
                         old_vx0 + sht->bxsize, old_vy0 + sht->bysize,
                         0, sht->height - 1);
        sheet_refreshsub(ctl, vx0, vy0,
                         vx0 + sht->bxsize, vy0 + sht->bysize,
                         sht->height, sht->height);

//        show_block(ctl->map, sht->bxsize, sht->bysize, sht->col_inv);
//        show_sheet(sht);
    }
}

void sheet_free(SHEET *sht) {
    if (sht->height >= 0)
        sheet_updown(sht, -1);

    sht->flags = 0;
}
