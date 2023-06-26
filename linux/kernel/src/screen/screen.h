//
// Created by Pengyifu on 2023/06/05.
//

#ifndef SUOS_SCREEN_H
#define SUOS_SCREEN_H
#include "memory.h"

typedef struct SHEET {
    int id;
    unsigned char *buf; // start address
    int bxsize;         // x size
    int bysize;         // y size
    int vx0;            // x position
    int vy0;            // y position
    unsigned char col_inv;
    int height;         // z position
    int flags;          // is allocated
    struct SHTCTL * ctl;
} SHEET;
#define MAX_SHEETS 256
typedef struct SHTCTL {
    unsigned char *vram, *map;
    int xsize;
    int ysize;
    int top;
    SHEET sheet[MAX_SHEETS];
    SHEET *sheets[MAX_SHEETS];

} SHTCTL;

void boxfill8(unsigned char *vram, int xsize,
              unsigned char color,
              int x0, int y0, int x1, int y1);
void make_window8(unsigned char *buf, int xsize, int ysize, char *title);

SHTCTL *shtctl_init(unsigned char *vram, int xsize, int ysize);
SHEET *sheet_alloc(SHTCTL *ctl) ;

void sheet_setbuf(SHEET *sht, unsigned char *buf, int xsize, int ysize, int col_inv);
void sheet_move(SHEET *sht, int vx0, int vy0);
void sheet_refresh(SHEET *sht, int bx0, int by0, int bx1, int by1);
void sheet_free(SHEET *sht);
void sheet_updown(SHEET *sht, int height);

void sheet_refreshmap(SHTCTL *ctl, int vx0, int vy0, int vx1, int vy1, int layer);
void sheet_refreshsub(SHTCTL *ctl,
                      int vx0, int vy0,
                      int vx1, int vy1,
                      int layer, int layerend);

#endif //SUOS_SCREEN_H
