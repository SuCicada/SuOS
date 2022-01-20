#include "header.h"
// #include "hankaku.h"
#include "color.h"
// #include "queue.h"

/*
  0xa0000 -> 0xaffff is screen memery
  注意这里的函数名字为bootmain，因为在entry.S中设定的入口名字也是bootmain，两者要保持一致
 */
void keybuf_init();
void keybuf_deal();

void mousebuf_init();
void mousebuf_deal();

void init_keyboard();
void enable_mouse();

char tmp_string[128];

KEYBUF keybuf;
unsigned char keybuf_mem[32]; // 为了能初始化固定的内存空间

Queue mousebuf;
unsigned char mousebuf_mem[32]; // 为了能初始化固定的内存空间

void bootmain(void) {

	struct BootInfo* binfo = (struct BootInfo*)ADR_BOOTINFO;
	char mouse[16 * 16];
	init_display_info(binfo);
	keybuf_init();
	mousebuf_init();

	init_gdtidt();
	init_pic();
	io_sti(); /* IDT/PIC的初始化已经完成，于是开放CPU的中断 */

	io_out8(PIC0_IMR, 0xf9); /* 开放PIC1和键盘中断(11111001) */
	io_out8(PIC1_IMR, 0xef); /* 开放鼠标中断(11101111) */

	init_palette();
	init_screen();

	su_sprintf(tmp_string, "DISPLAY_X_SIZE = %d ", DISPLAY_X_SIZE);
	putfonts8_asc(5, 10, COL8_FFFFFF, tmp_string);

	init_mouse_cursor8(mouse, BACK_COLOR);
	putblock(100, 100, 16, 16, mouse);

	init_keyboard();
	enable_mouse();

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
	// io_cli();
	for (;;) {
		// io_cli();
		// boxfill8_s(15, 30, 10 * FONT_X_SIZE, FONT_Y_SIZE, BACK_COLOR);
		// for(int i=0;i<1000000;i++);
		// io_sti();


		putfonts8_asc(15, 30, a, "can click");
		// for(int i=0;i<1000000;i++);
		keybuf_deal();
		mousebuf_deal();

		a++;
	}
	// io_hlt();
}


void keybuf_init() {
	keybuf.size = sizeof(keybuf_mem) / sizeof(unsigned char);
	queue_init(&keybuf.queue, keybuf_mem, keybuf.size);
}
void keybuf_deal() {
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

	}
	io_sti();
}

void mousebuf_init() {
	int size = sizeof(mousebuf_mem) / sizeof(unsigned char);
	queue_init(&mousebuf, mousebuf_mem, size);
}

void mousebuf_deal() {
	io_cli();
	// for(int i=0;i<100000;i++);
	Queue* buf_ptr = &mousebuf;
	if (!queue_empty(buf_ptr)) {
		unsigned char data = queue_pop(buf_ptr);

		su_sprintf(tmp_string, "0x%x", data);
		boxfill8_s(0, 3 * FONT_Y_SIZE, 5 * FONT_X_SIZE, FONT_Y_SIZE, COL8_000000);
		putfonts8_asc(0, 3 * FONT_Y_SIZE, COL8_FFFFFF, tmp_string);

		int size = queue_size(buf_ptr);
		su_sprintf(tmp_string, "size: %d", size);
		boxfill8_s(0, FONT_Y_SIZE * 6, 10 * FONT_X_SIZE, FONT_Y_SIZE , COL8_000000);
		putfonts8_asc(0, FONT_Y_SIZE * 6, COL8_FFFFFF, tmp_string);
	}
	io_sti();
}

#define PORT_KEYSTA				0x0064
#define PORT_KEYCMD				0x0064
#define PORT_KEYDAT				0x0060
#define KEYSTA_SEND_NOTREADY	0x02
#define KEYCMD_WRITE_MODE		0x60
#define KBC_MODE				0x47 	// 鼠标

void wait_KBC_sendready(void) {
	/* 等待键盘控制电路准备完毕 */
	for (;;) {
		if ((io_in8(PORT_KEYSTA) & KEYSTA_SEND_NOTREADY) == 0) {
			break;
		}
	}
	return;
}
void init_keyboard(void) {
	/* 初始化键盘控制电路 */
	wait_KBC_sendready();
	io_out8(PORT_KEYCMD, KEYCMD_WRITE_MODE);
	wait_KBC_sendready();
	io_out8(PORT_KEYDAT, KBC_MODE);
	return;

}
#define KEYCMD_SENDTO_MOUSE		0xd4
#define MOUSECMD_ENABLE			0xf4

void enable_mouse(void) {
	/* 激活鼠标 */
	wait_KBC_sendready();
	io_out8(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);
	wait_KBC_sendready();
	io_out8(PORT_KEYDAT, MOUSECMD_ENABLE);
	return; /* 顺利的话，键盘控制器会返回ACK(0xfa) */
}


void .//_mouse_cursor8(char* mouse, char bg) {
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