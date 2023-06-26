#ifndef COLOR_H
#define COLOR_H
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

#define FONT_X_SIZE 8
#define FONT_Y_SIZE 16

void set_palette(int start, int end, unsigned char* rgb_table);
void boxfill8_s(int x0, int y0, int x1, int y1,int color_flag);
void boxfill8_v1(int x0, int y0, int x1, int y1, int color_flag);
void putfont(unsigned char *vram, int xsize, int x, int y, char color, char* font);

void putfonts8_asc_v1(int x, int y, char color, char*);
void puts8(unsigned char *vram, int xsize, int x, int y, char color,  char* msg);

// void init_display_info(struct BootInfo* binfo);
void putblock(int x, int y, int xsize, int ysize, char* vblock);
void getblock(int x, int y, int xsize, int ysize, char* vblock);

//void init_screen();
void init_palette();

extern int DISPLAY_X_SIZE;
extern int DISPLAY_Y_SIZE;
extern unsigned char* DISPLAY_ADDRE; // (char*)0xa0000;

#define BACK_COLOR COL8_008484

#endif // COLOR_H
