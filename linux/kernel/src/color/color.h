
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
void boxfill8(int x0, int y0, int x1, int y1,int color_flag);
void putfont(int x, int y, char color, char* font);

void putfonts8_asc(int x, int y, char color, char*);
// void init_display_info(struct BootInfo* binfo);
void putblock(int x, int y, int xsize, int ysize, char* vblock);
void getblock(int x, int y, int xsize, int ysize, char* vblock);
void init_screen();
void init_palette();

extern int DISPLAY_X_SIZE;
extern int DISPLAY_Y_SIZE;
extern char* DISPLAY_ADDRE; // (char*)0xa0000;

#define BACK_COLOR COL8_008484
