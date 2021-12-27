#include <asmfunc.h>
#include "hankaku.h"

#define COL8_000000 0  // 黒
#define COL8_FF0000 1  // 明るい赤
#define COL8_00FF00 2  // 明るい緑
#define COL8_FFFF00 3  // 黄色
#define COL8_0000FF 4  // 明るい青
#define COL8_FF00FF 5  // 明るい紫
#define COL8_00FFFF 6  // 明るい水色
#define COL8_FFFFFF 7  // 白
#define COL8_C6C6C6 8  // 明るい灰色
#define COL8_840000 9  // 暗い赤
#define COL8_008400 10 // 暗い緑
#define COL8_848400 11 // 暗い黄色
#define COL8_000084 12 // 暗い青
#define COL8_840084 13 // 暗い紫
#define COL8_008484 14 // 暗い水色
#define COL8_848484 15 // 暗い灰色

void set_palette(int start, int end, unsigned char* rgb_table);
void boxfill(int color_flag, int x0, int y0, int x1, int y1);
void putfont(int x, int y, char color, char* font);
void putfont_asc(int x, int y, char color, char*);

struct BootInfo {
    char cyls, leds, vmode, reserve; // 1 byte * 4 ;
    short scrnx, scrny;				 // 2 byte * 2 ; x_size, y_size
    char* vram;						 // 4 byte
};

int DISPLAY_X_SIZE = 320;
int DISPLAY_Y_SIZE = 200;
char* DISPLAY_ADDRE = (char*)0xa0000;

void init_display_info(struct BootInfo* binfo)
{
    DISPLAY_ADDRE = binfo->vram;
    DISPLAY_X_SIZE = binfo->scrnx,
        DISPLAY_Y_SIZE = binfo->scrny;
}

void init_palette()
{
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

void set_palette(int start, int end, unsigned char* rgb_table)
{
    // int start = 0,
    //     end = 15;
    int flag = io_read_eflags();
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
void boxfill(int color_flag, int x0, int y0, int x1, int y1)
{
    for (int y = y0; y <= y1; y++)
        for (int x = x0; x <= x1; x++)
            ((char*)DISPLAY_ADDRE)[y * DISPLAY_X_SIZE + x] = color_flag;
}

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

void putfont_asc(int x, int y, char color, char* msg) {
    // static char a[] = "nihoa";
    // msg = a;
    for (int i = 0; msg[i] != 0;i++) {
        int font = msg[i];
        putfont(10 * i + x, y, color, hankaku[font]);
    }
}

void putblock(int x, int y, int xsize, int ysize, char* vblock) {
    for (int i = 0; i < xsize; i++) {
        for (int j = 0; j < ysize; j++) {
            int display_size = (y + j) * DISPLAY_X_SIZE + x + i;
            DISPLAY_ADDRE[display_size] = vblock[j * xsize + i];
        }
    }
}

void init_mouse_cursor8(char* mouse, char bg) {
    char outline = COL8_000000;
    char inside = COL8_FFFFFF;
    const static char cursor[16][16] = {
        "**************..",
        "*OOOOOOOOOOO*...",
        "*OOOOOOOOOO*....",
        "*OOOOOOOOO*.....",
        "*OOOOOOOO*......",
        "*OOOOOOO*.......",
        "*OOOOOOO*.......",
        "*OOOOOOOO*......",
        "*OOOO**OOO*.....",
        "*OOO*..*OOO*....",
        "*OO*....*OOO*...",
        "*O*......*OOO*..",
        "**........*OOO*.",
        "*..........*OOO*",
        "............*OO*",
        ".............***"
    };
    char m;
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            char c = cursor[x][y];
            switch (c) {
            case 'O':
                m = inside;
                break;
            case '*':
                m = outline;
                break;
            case '.':
                m = bg;
                break;
            }
            mouse[y * 16 + x] = m;
        }
    }
}