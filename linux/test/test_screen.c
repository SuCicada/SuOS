
#include <stdlib.h>
#include "screen.h"
#include "mouse.h"
#include "stdio.h"
#include "utils/vram.c"
#include "window.h"

void sheet_show(SHEET *sht) {
    printf("sht->height: %d\n", sht->height);
    printf("sht->col_inv: %d\n", sht->col_inv);
//    printf("sht->height: %d\n", sht->height);
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

void show_sheet(SHEET *sht) {
    show_block(sht->buf, sht->bxsize, sht->bysize, sht->col_inv);
}

int xsize = 320;
int ysize = 200;

int test_mouse() {
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
    unsigned char *desktop = (unsigned char *) mem_alloc(DISPLAY_X_SIZE * DISPLAY_Y_SIZE);


    sheet_setbuf(sht_mouse, mouse_cursor, 16, 16, 255);
//    sheet_updown(sht_mouse, 1);
    ctl->top++;
    ctl->sheets[0] = sht_mouse;

    shtctl_show(ctl);

    init_screen(desktop, DISPLAY_X_SIZE, DISPLAY_Y_SIZE);

    printf("sizeof(SHTCTL): %d\n", sizeof(SHTCTL));

    sheet_refreshmap(ctl,
                     sht_mouse->vx0, sht_mouse->vy0,
                     sht_mouse->vx0 + sht_mouse->bxsize, sht_mouse->vy0 + sht_mouse->bysize,
                     0);
//    show_block(ctl->map, xsize, ysize, 0);
//    vram_simulator(ctl->map, xsize, ysize);

    printf("==================== sheet_refreshsub ====================\n");
    sheet_refreshsub(ctl,
                     sht_mouse->vx0, sht_mouse->vy0,
                     sht_mouse->vx0 + sht_mouse->bxsize, sht_mouse->vy0 + sht_mouse->bysize,
                     0, 1);
//    vram_simulator(ctl->vram, xsize, ysize);

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

void sheet_refresh_whole(SHTCTL *shtctl, SHEET *sht) {
    sheet_refreshmap(shtctl,
                     sht->vx0, sht->vy0,
                     sht->vx0 + sht->bxsize, sht->vy0 + sht->bysize,
                     sht->height);
    sheet_refreshsub(shtctl,
                     sht->vx0, sht->vy0,
                     sht->vx0 + sht->bxsize, sht->vy0 + sht->bysize,
                     sht->height, sht->height);

}

int main() {
    DISPLAY_X_SIZE = xsize, DISPLAY_Y_SIZE = ysize;
    unsigned char *vram = (unsigned char *) malloc(xsize * ysize);
    SHTCTL *shtctl = shtctl_init(vram, xsize, ysize);
    SHEET *sht_back = create_background_sheet(shtctl);

    SHEET *sht_mouse = create_mouse_sheet(shtctl);
//    shtctl->top =1;
//    shtctl->top =1;
    sheet_show(sht_back);
    sheet_show(sht_mouse);
//    sheet_refresh_whole(shtctl, sht_back);
//    sheet_refresh_whole(shtctl, sht_mouse);
    printf("shtctl->top: %d\n", shtctl->top);
    sheet_updown(sht_back, 0);

    show_sheet(sht_mouse);

//    sheet_refreshmap(shtctl,
//                     sht_mouse->vx0, sht_mouse->vy0,
//                     sht_mouse->vx0 + sht_mouse->bxsize, sht_mouse->vy0 + sht_mouse->bysize,
//                     0);
//    sheet_refreshsub(shtctl,
//                     sht_mouse->vx0, sht_mouse->vy0,
//                     sht_mouse->vx0 + sht_mouse->bxsize, sht_mouse->vy0 + sht_mouse->bysize,
//                     0, 1);
//
//    show_block(shtctl->vram, xsize, ysize, -1);
    unsigned char *vram0 = shtctl->vram;
    vram_simulator_init(xsize, ysize);
    vram_simulator_update(vram0);
//    SDL_Delay(1000);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        printf("event.type: %d\n", event.type);
    }
    sheet_updown(sht_mouse, 99);
    vram_simulator_update(vram0);
    SDL_Delay(1000);


    sheet_move(sht_mouse, 100,100);
    vram_simulator_update(vram0);


    vram_simulator_wait();
}
