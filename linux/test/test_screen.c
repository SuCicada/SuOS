
#include <stdlib.h>
#include "screen.h"
#include "mouse.h"
#include "stdio.h"
#include "fake/vram.c"

void sheet_show(SHEET *sht) {
    printf("sht->height: %d\n", sht->height);
    printf("sht->height: %d\n", sht->height);
}

void shtctl_show(SHTCTL *shtctl) {
    printf("shtctl->top: %d\n", shtctl->top);
}

void show_block(const unsigned char *buf, int xsize, int ysize, unsigned char clo_inv) {

    printf("====================================\n");
    for (int j = 0; j < ysize; ++j) {
        for (int i = 0; i < xsize; ++i) {
            unsigned char a = buf[i * xsize + j];
            if (a == clo_inv)
                printf("%4c", '.');
            else
                printf("%4d", a);
        }
        printf("\n");
    }
}

int main() {
    int xsize = 320;
    int ysize = 200;
    unsigned char *vram = (unsigned char *) malloc(xsize * ysize);
    SHTCTL *ctl = shtctl_init(vram, xsize, ysize);
//    SHTCTL ctl = *shtctl;
//    printf("ctl.xsize: %d\n", ctl.xsize);
    unsigned char mouse_cursor[16 * 16];
    init_mouse_cursor8(mouse_cursor);
    show_block(mouse_cursor, 16, 16, -1);
//    for (int i = 0; i < 16; i++) {
//        for (int j = 0; j < 16; j++) {
//            printf("%4d", mouse_cursor[i * 16 + j]);
//        }
//        printf("\n");
//    }


    SHEET *sht_mouse = sheet_alloc(ctl);

    sheet_setbuf(sht_mouse, mouse_cursor, 16, 16, 255);
//    sheet_updown(sht_mouse, 1);
    ctl->top++;
    ctl->sheets[0] = sht_mouse;

    shtctl_show(ctl);

    printf("sizeof(SHTCTL): %d\n", sizeof(SHTCTL));

    sheet_refreshmap(ctl,
                     sht_mouse->vx0, sht_mouse->vy0,
                     sht_mouse->vx0 + sht_mouse->bxsize, sht_mouse->vy0 + sht_mouse->bysize,
                     0);
//    show_block(ctl->map, xsize, ysize, 0);
    vram_simulator(ctl->map, xsize, ysize);
//    sheet_refreshsub(ctl,
//                     sht_mouse->vx0, sht_mouse->vy0,
//                     sht_mouse->vx0 + sht_mouse->bxsize, sht_mouse->vy0 + sht_mouse->bysize,
//                     0, 1);

//    for (int j = 0; j < ysize; ++j) {
//        for (int i = 0; i < xsize; ++i) {
//            int a = ctl->map[i * xsize + j];
//            if (a == 0)
//                printf("%4c", '.');
//            else
//                printf("%4d", a);
//        }
//        printf("\n");
//    }
}
