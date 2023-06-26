#include "hankaku.h"
#include "header.h"
#include "color.h"

int DISPLAY_X_SIZE;
int DISPLAY_Y_SIZE;
unsigned char* DISPLAY_ADDRE; // (char*)0xa0000;

void init_display_info(struct BootInfo* binfo) {
    DISPLAY_ADDRE = binfo->vram;
    DISPLAY_X_SIZE = binfo->scrnx,
        DISPLAY_Y_SIZE = binfo->scrny;
}

void init_screen0() {
    int xsize = DISPLAY_X_SIZE, ysize = DISPLAY_Y_SIZE;
    boxfill8_v1(0, 0, xsize - 1, ysize - 29, BACK_COLOR);
    boxfill8_v1(0, ysize - 28, xsize - 1, ysize - 28, COL8_C6C6C6);
    boxfill8_v1(0, ysize - 27, xsize - 1, ysize - 27, COL8_FFFFFF);
    boxfill8_v1(0, ysize - 26, xsize - 1, ysize - 1, COL8_C6C6C6);

    boxfill8_v1(3, ysize - 24, 59, ysize - 24, COL8_FFFFFF);
    boxfill8_v1(2, ysize - 24, 2, ysize - 4, COL8_FFFFFF);
    boxfill8_v1(3, ysize - 4, 59, ysize - 4, COL8_848484);
    boxfill8_v1(59, ysize - 23, 59, ysize - 5, COL8_848484);
    boxfill8_v1(2, ysize - 3, 59, ysize - 3, COL8_000000);
    boxfill8_v1(60, ysize - 24, 60, ysize - 3, COL8_000000);

    boxfill8_v1(xsize - 47, ysize - 24, xsize - 4, ysize - 24, COL8_848484);
    boxfill8_v1(xsize - 47, ysize - 23, xsize - 47, ysize - 4, COL8_848484);
    boxfill8_v1(xsize - 47, ysize - 3, xsize - 4, ysize - 3, COL8_FFFFFF);
    boxfill8_v1(xsize - 3, ysize - 24, xsize - 3, ysize - 3, COL8_FFFFFF);
}


void init_palette() {
    // rgb_table[0]=0xff;
    // int a = rgb_table[2];
    // rgb_table[0 * 3 + 1] = 0xff;
    // rgb_table[0 * 3 + 2] = 0xff;
    set_palette(0, 15, rgb_table);
    return;
    // static char 命令は、データにしか使えないけどDB命令担当
}

void set_palette(int start, int end, unsigned char* rgb_table) {
    // int start = 0,
    //     end = 15;
    int flag = io_load_eflags();
    io_cli();
    unsigned char* rgb_table_pnt = rgb_table;
    io_out8(0x03c8, start);

    for (int i = start; i <= end; i++)
    {
        // io_out8(0x03c9, 0xff);
        // io_out8(0x03c9, 0x00);
        // io_out8(0x03c9, 0x00);
        for (int j = 0; j < 3; j++)
        {
            io_out8(0x03c9, rgb_table_pnt[j] / 4);
            // io_out8(0x03c9, rgb_table[i * 3 + j] / 4);
            // rgb_table[j]
        }
        rgb_table_pnt += 3;
    }
    io_store_eflags(flag);
    // io_sti();
    return;
}


// ==================  draw =========================
void boxfill8_s(int x0, int y0, int xs, int ys, int color_flag) {
    boxfill8_v1(x0, y0, x0 + xs, y0 + ys, color_flag);
}
void boxfill8_v1(int x0, int y0, int x1, int y1, int color_flag) {
    for (int y = y0; y <= y1; y++)
        for (int x = x0; x <= x1; x++)
            ((char*)DISPLAY_ADDRE)[y * DISPLAY_X_SIZE + x] = color_flag;
}

/*  one font is 16 * 8  */
void putfont(
    unsigned char *vram,   // 4 byte
    int xsize,    // 4 byte
    int x,        // 4 byte
    int y,        // 4 byte
    char color,       // 1 byte
    char* font)   // 4 byte
{
    int i;
    char d;     // 1 byte
    unsigned char* p;    // 4 byte
    for (i = 0; i < 16; i++) {
        // 左上を(0, 0)として(x, y)の座標に描画
//        p = DISPLAY_ADDRE + (y + i) * DISPLAY_X_SIZE + x;   // 1 byte
        p = vram + (y + i) * xsize + x;   // 1 byte
        d = font[i];
        unsigned char tmp = 1 << 7;
        for (int j = 0; j < 8; j++, tmp >>= 1) {
            if ((d & tmp) != 0)
                p[j] = color;
        }
    }
    return;
}
void puts8(unsigned char *vram, int xsize, int x, int y, char color,  char* msg){
    for (int i = 0; msg[i] != 0;i++) {
        int font = msg[i];
        putfont(vram,xsize, FONT_X_SIZE * i + x, y, color, hankaku[font]);
    }
}

void putfonts8_asc_v1(int x, int y, char color, char* msg) {
    // static char a[] = "nihoa";
    // msg = a;
    for (int i = 0; msg[i] != 0;i++) {
        int font = msg[i];
        putfont(DISPLAY_ADDRE,DISPLAY_X_SIZE,
            FONT_X_SIZE * i + x, y, color, hankaku[font]);
    }
}

void getblock(int x, int y, int xsize, int ysize, char* vblock) {
    for (int i = 0; i < xsize; i++) {
        for (int j = 0; j < ysize; j++) {
            int display_size = (y + j) * DISPLAY_X_SIZE + x + i;
            vblock[j * xsize + i] = DISPLAY_ADDRE[display_size];
        }
    }
}

void putblock(int x, int y, int xsize, int ysize, char* vblock) {
    for (int i = 0; i < xsize; i++) {
        for (int j = 0; j < ysize; j++) {
            int display_size = (y + j) * DISPLAY_X_SIZE + x + i;
            char c = vblock[j * xsize + i];// color
            if (c >= 0) {
                DISPLAY_ADDRE[display_size] = c;
            }
        }
    }
}
