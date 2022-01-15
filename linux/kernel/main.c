#include "header.h"
// #include "hankaku.h"
#include "color.h"
// #include "queue.h"

/*
  0xa0000 -> 0xaffff is screen memery
  注意这里的函数名字为bootmain，因为在entry.S中设定的入口名字也是bootmain，两者要保持一致
 */
void keyboard_init();
void keyboard_deal();
char tmp_string[128];

extern KEYBUF keybuf;
unsigned char keybuf_mem[32]; // 为了能初始化固定的内存空间

void bootmain(void) {

	struct BootInfo* binfo = (struct BootInfo*)ADR_BOOTINFO;
	char mouse[16 * 16];
	init_display_info(binfo);
	keyboard_init();
	init_gdtidt();
	init_pic();
	io_sti(); /* IDT/PIC的初始化已经完成，于是开放CPU的中断 */

	io_out8(PIC0_IMR, 0xf9); /* 开放PIC1和键盘中断(11111001) */
	io_out8(PIC1_IMR, 0xef); /* 开放鼠标中断(11101111) */

	init_palette();
	init_screen();
	init_mouse_cursor8(mouse, BACK_COLOR);
	putblock(100, 100, 16, 16, mouse);

	su_sprintf(tmp_string, "DISPLAY_X_SIZE = %d ", DISPLAY_X_SIZE);
	putfonts8_asc(5, 10, COL8_FFFFFF, tmp_string);

	// su_sprintf(tmp_string, "nihoa: %d %d", DISPLAY_Y_SIZE, 1234);
	// putfonts8_asc(15, 30, COL8_FFFFFF, tmp_string);

	// int start_y = 60;
	// boxfill8(COL8_000000, 30, start_y, 30 + 1 * FONT_X_SIZE, start_y + FONT_Y_SIZE);
	// putfonts8_asc(30, start_y, COL8_FFFFFF, "0 ");
	// start_y = 60 + FONT_Y_SIZE * 1;
	// boxfill8(COL8_000000, 30, start_y, 30 + 2 * FONT_X_SIZE, start_y + FONT_Y_SIZE);
	// putfonts8_asc(30, start_y, COL8_FFFFFF, "00");
	// start_y = 60 + FONT_Y_SIZE * 2;
	// boxfill8(COL8_000000, 30, start_y, 30 + 3 * FONT_X_SIZE, start_y + FONT_Y_SIZE);
	// putfonts8_asc(30, start_y, COL8_FFFFFF, "000");


	int a;
	io_cli();
	for (;;) {
		// io_cli();
		// boxfill8_s(15, 30, 10 * FONT_X_SIZE, FONT_Y_SIZE, BACK_COLOR);
		// for(int i=0;i<1000000;i++);
		// io_sti();


		putfonts8_asc(15, 30, a, "can click");
		// for(int i=0;i<1000000;i++);
		keyboard_deal();


		a++;
	}
	// io_hlt();
}


void keyboard_init() {
	keybuf.size = sizeof(keybuf_mem) / sizeof(unsigned char);
	queue_init(&keybuf.queue, keybuf_mem, keybuf.size);
}
void keyboard_deal() {
	io_cli();
	// for(int i=0;i<100000;i++);
	if (!queue_empty(&keybuf.queue)) {
		unsigned char data = queue_pop(&keybuf.queue);

		su_sprintf(tmp_string, "0x%x", data);
		boxfill8(0, 16, 4 * FONT_X_SIZE, 31, COL8_000000);
		putfonts8_asc(0, 16, COL8_FFFFFF, tmp_string);

		int size = queue_size(&keybuf.queue);
		su_sprintf(tmp_string, "size: %d", size);
		boxfill8(0, FONT_Y_SIZE * 5, 10 * FONT_X_SIZE, FONT_Y_SIZE * (5 + 1), COL8_000000);
		putfonts8_asc(0, FONT_Y_SIZE * 5, COL8_FFFFFF, tmp_string);

		io_sti();
	}
	else {
		io_sti();
	}
}