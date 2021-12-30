
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
void boxfill8(int color_flag, int x0, int y0, int x1, int y1);
void putfont(int x, int y, char color, char* font);
void putfonts8_asc(int x, int y, char color, char*);
// void init_display_info(struct BootInfo* binfo);
void init_mouse_cursor8(char* mouse, char bg);
void putblock(int x, int y, int xsize, int ysize, char* vblock);
void init_screen();

int DISPLAY_X_SIZE;
int DISPLAY_Y_SIZE;
char* DISPLAY_ADDRE; // (char*)0xa0000;

#define BACKGROUND COL8_008484
