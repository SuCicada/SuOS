#include <asmfunc.h>
#include "color.c"
// #include "hankaku.h"
#include "utils.c"
/*
  0xa0000 -> 0xaffff is screen memery
  注意这里的函数名字为bootmain，因为在entry.S中设定的入口名字也是bootmain，两者要保持一致
 */

void init_display_info(struct BootInfo* binfo);
void init_screen();


int BACKGROUND = COL8_008484;

void bootmain(void)
{
	struct BootInfo* binfo = (struct BootInfo*)0x0ff0;
	char mouse[16 * 16];

	init_display_info(binfo);
	init_palette();
	init_screen();
	init_mouse_cursor8(mouse, BACKGROUND);
	putblock(100, 100, 16, 16, mouse);

	static char s[128];
	su_sprintf(s, "DISPLAY_X_SIZE = %d ", DISPLAY_X_SIZE);
	putfont_asc(5, 10, COL8_FFFFFF, s);
	su_sprintf(s, "nihoa: %d %d", DISPLAY_Y_SIZE, 1234);
	putfont_asc(15, 30, COL8_FFFFFF, s);
	// putfont_asc( 5, 10, COL8_FFFFFF, "I'm SuCicada.--");
	// putfont_asc( 5, 10+15+1, COL8_000000, "I'm SuCicada.--");
	// putfont_asc( 5, 10+15, COL8_FFFFFF, "I'm SuCicada.--");

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




void init_screen()
{
	int xsize = DISPLAY_X_SIZE, ysize = DISPLAY_Y_SIZE;
	boxfill(BACKGROUND, 0, 0, xsize - 1, ysize - 29);
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
