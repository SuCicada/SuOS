#include "hankaku.h"
#include "header.h"
#include "color.h"

int DISPLAY_X_SIZE;
int DISPLAY_Y_SIZE;
char* DISPLAY_ADDRE; // (char*)0xa0000;

void init_display_info(struct BootInfo* binfo) {
    DISPLAY_ADDRE = binfo->vram;
    DISPLAY_X_SIZE = binfo->scrnx,
        DISPLAY_Y_SIZE = binfo->scrny;
}

void init_screen() {
    int xsize = DISPLAY_X_SIZE, ysize = DISPLAY_Y_SIZE;
    boxfill8(0, 0, xsize - 1, ysize - 29, BACK_COLOR);
    boxfill8(0, ysize - 28, xsize - 1, ysize - 28, COL8_C6C6C6);
    boxfill8(0, ysize - 27, xsize - 1, ysize - 27, COL8_FFFFFF);
    boxfill8(0, ysize - 26, xsize - 1, ysize - 1, COL8_C6C6C6);

    boxfill8(3, ysize - 24, 59, ysize - 24, COL8_FFFFFF);
    boxfill8(2, ysize - 24, 2, ysize - 4, COL8_FFFFFF);
    boxfill8(3, ysize - 4, 59, ysize - 4, COL8_848484);
    boxfill8(59, ysize - 23, 59, ysize - 5, COL8_848484);
    boxfill8(2, ysize - 3, 59, ysize - 3, COL8_000000);
    boxfill8(60, ysize - 24, 60, ysize - 3, COL8_000000);

    boxfill8(xsize - 47, ysize - 24, xsize - 4, ysize - 24, COL8_848484);
    boxfill8(xsize - 47, ysize - 23, xsize - 47, ysize - 4, COL8_848484);
    boxfill8(xsize - 47, ysize - 3, xsize - 4, ysize - 3, COL8_FFFFFF);
    boxfill8(xsize - 3, ysize - 24, xsize - 3, ysize - 3, COL8_FFFFFF);
}


void init_palette() {
    static unsigned char rgb_table[16 * 3] = {
        0x00, 0x00, 0x00, // 000000 : 0 : 黒
        0xff, 0x00, 0x00, // ff0000 : 1 : 明るい赤
        0x00, 0xff, 0x00, // 00ff00 : 2 : 明るい緑
        0xff, 0xff, 0x00, // ffff00 : 3 : 黄色
        0x00, 0x00, 0xff, // 0000ff : 4 : 明るい青
        0xff, 0x00, 0xff, // ff00ff : 5 : 明るい紫
        0x00, 0xff, 0xff, // 00ffff : 6 : 明るい水色
        0xff, 0xff, 0xff, // ffffff : 7 : 白
        0xc6, 0xc6, 0xc6, // c6c6c6 : 8 : 明るい灰色
        0x84, 0x00, 0x00, // 840000 : 9 : 暗い赤
        0x00, 0x84, 0x00, // 008400 : 10: 暗い緑
        0x84, 0x84, 0x00, // 848400 : 11: 暗い黄色
        0x00, 0x00, 0x84, // 000084 : 12: 暗い青
        0x84, 0x00, 0x84, // 840084 : 13: 暗い紫
        0x00, 0x84, 0x84, // 008484 : 14: 暗い水色
        0x84, 0x84, 0x84  // 848484 : 15: 暗い灰色
    };
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
    boxfill8(x0, y0, x0 + xs, y0 + ys, color_flag);
}
void boxfill8(int x0, int y0, int x1, int y1, int color_flag) {
    for (int y = y0; y <= y1; y++)
        for (int x = x0; x <= x1; x++)
            ((char*)DISPLAY_ADDRE)[y * DISPLAY_X_SIZE + x] = color_flag;
}

/*  one font is 16 * 8  */
void putfont(//char *vram,   // 4 byte
              //int xsize,    // 4 byte
    int x,        // 4 byte
    int y,        // 4 byte
    char color,       // 1 byte
    char* font)   // 4 byte
{
    int i;
    char d;     // 1 byte
    char* p;    // 4 byte
    for (i = 0; i < 16; i++) {
        // 左上を(0, 0)として(x, y)の座標に描画
        p = DISPLAY_ADDRE + (y + i) * DISPLAY_X_SIZE + x;   // 1 byte
        d = font[i];
        unsigned char tmp = 1 << 7;
        for (int j = 0; j < 8; j++, tmp >>= 1) {
            if ((d & tmp) != 0)
                p[j] = color;
        }
    }
    return;
}

void putfonts8_asc(int x, int y, char color, char* msg) {
    // static char a[] = "nihoa";
    // msg = a;
    for (int i = 0; msg[i] != 0;i++) {
        int font = msg[i];
        putfont(FONT_X_SIZE * i + x, y, color, hankaku[font]);
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
