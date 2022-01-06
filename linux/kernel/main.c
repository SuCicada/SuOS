#include "header.h"
// #include "hankaku.h"
#include "color.h"

/*
  0xa0000 -> 0xaffff is screen memery
  注意这里的函数名字为bootmain，因为在entry.S中设定的入口名字也是bootmain，两者要保持一致
 */
void bootmain(void){

	struct BootInfo* binfo = (struct BootInfo*)ADR_BOOTINFO;
	char mouse[16 * 16];
	char s[128];
	init_display_info(binfo);

	init_gdtidt();
	init_pic();
	io_sti(); /* IDT/PIC的初始化已经完成，于是开放CPU的中断 */

 	io_out8(PIC0_IMR, 0xf9); /* 开放PIC1和键盘中断(11111001) */
	io_out8(PIC1_IMR, 0xef); /* 开放鼠标中断(11101111) */
	
	init_palette();
	init_screen();
	init_mouse_cursor8(mouse, BACKGROUND);
	putblock(100, 100, 16, 16, mouse);

	su_sprintf(s, "DISPLAY_X_SIZE = %d ", DISPLAY_X_SIZE);
	putfonts8_asc(5, 10, COL8_FFFFFF, s);
	su_sprintf(s, "nihoa: %d %d", DISPLAY_Y_SIZE, 1234);
	putfonts8_asc(15, 30, COL8_FFFFFF, s);

	for (;;)
		io_hlt();
}
