#include <asmfunc.h>
#include <color.c>
/*
  0xa0000 -> 0xaffff is screen memery
  注意这里的函数名字为bootmain，因为在entry.S中设定的入口名字也是bootmain，两者要保持一致
 */
struct BootInfo
{
	char cyls, leds, vmode, reserve; // 1 byte * 4 ;
	short scrnx, scrny;				 // 2 byte * 2 ; x_size, y_size
	char *vram;						 // 4 byte
};

int DISPLAY_X_SIZE = 320;
int DISPLAY_Y_SIZE = 200;
char *DISPLAY_ADDRE = (char *)0xa0000;
void init_display_info(struct BootInfo *binfo);
void boxfill(int color_flag, int x0, int y0, int x1, int y1);
void init_screen();
void putfont(int x, int y, char color, char *font);

void bootmain(void)
{
	struct BootInfo *binfo = (struct BootInfo *)0x0ff0;

	init_display_info(binfo);
	init_palette();
	init_screen();

	static char font_A[16] = {
		0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x24,
		0x24, 0x7e, 0x42, 0x42, 0x42, 0xe7, 0x00, 0x00,
  	};
	putfont(10, 10, COL8_FFFFFF, font_A);

	// for (i = 0xa0000; i <= 0xa4fff; i++)
	// {
	// 	// write_mem8(i,x);
	// 	*((char *)i) = i & 0xff;
	// }
	// for (i = 0xa6000; i <= 0xaffff; i++)
	// {
	// 	*((char *)i) = 1;
	// 	// write_mem8(i,3);
	// }

	// for(i=start;i<=end;i++){
	// 	write_mem8(i,15);
	// }
	// // while(1);
	for (;;)
	{
		io_hlt();
	}
}

void putfont(//char *vram,   // 4 byte
              //int xsize,    // 4 byte
              int x,        // 4 byte
              int y,        // 4 byte
              char color,       // 1 byte
              char *font)   // 4 byte
{
  	int i;
  	char d;     // 1 byte
  	char *p;    // 4 byte
  	for (i = 0; i < 16; i++){
		// 左上を(0, 0)として(x, y)の座標に描画
		p = DISPLAY_ADDRE + (y + i) * DISPLAY_X_SIZE + x;   // 1 byte
		d = font[i];
		unsigned char tmp=1<<7;
		for(int j=0; j<8; j++,tmp>>=1){
			if ((d & tmp) != 0)
				p[j] = color;
		}
	}
  	return;
}

void init_display_info(struct BootInfo *binfo)
{
	DISPLAY_ADDRE = binfo->vram;
	DISPLAY_X_SIZE = binfo->scrnx,
	DISPLAY_Y_SIZE = binfo->scrny;
}
void boxfill(int color_flag, int x0, int y0, int x1, int y1)
{
	for (int y = y0; y <= y1; y++)
		for (int x = x0; x <= x1; x++)
			((char *)DISPLAY_ADDRE)[y * DISPLAY_X_SIZE + x] = color_flag;
}

void init_screen()
{
	int xsize = DISPLAY_X_SIZE, ysize = DISPLAY_Y_SIZE;
	boxfill(COL8_008484, 0, 0, xsize - 1, ysize - 29);
	boxfill(COL8_C6C6C6, 0, ysize - 28, xsize - 1, ysize - 28);
	boxfill(COL8_FFFFFF, 0, ysize - 27, xsize - 1, ysize - 27);
	boxfill(COL8_C6C6C6, 0, ysize - 26, xsize - 1, ysize - 1);

	boxfill(COL8_FFFFFF, 3, ysize - 24, 59, ysize - 24);
	boxfill(COL8_FFFFFF, 2, ysize - 24, 2, ysize - 4);
	boxfill(COL8_848484, 3, ysize - 4, 59, ysize - 4);
	boxfill(COL8_848484, 59, ysize - 23, 59, ysize - 5);
	boxfill(COL8_000000, 2, ysize - 3, 59, ysize - 3);
	boxfill(COL8_000000, 60, ysize - 24, 60, ysize - 3);

	boxfill(COL8_848484, xsize - 47, ysize - 24, xsize - 4, ysize - 24);
	boxfill(COL8_848484, xsize - 47, ysize - 23, xsize - 47, ysize - 4);
	boxfill(COL8_FFFFFF, xsize - 47, ysize - 3, xsize - 4, ysize - 3);
	boxfill(COL8_FFFFFF, xsize - 3, ysize - 24, xsize - 3, ysize - 3);
}
