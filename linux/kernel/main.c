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
char mouse_cursor[16 * 16];

void bootmain(void) {

	struct BootInfo* binfo = (struct BootInfo*)ADR_BOOTINFO;
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

	init_mouse_cursor8(mouse_cursor);

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

		/*
			注意如果loop循环中包含过度频繁的操作处理逻辑
			会对中断处理产生延迟影响
			鼠标会乱跳, 不灵了
		*/
		// putfonts8_asc(15, 30, a, "can click");
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
struct MOUSE_DEC {
	int group_flag; // a gropu has 3
	unsigned char group[3]; // a gropu has 3
	int x, y, btn;
};

struct MOUSE_DEC mouse_dec;

int mouse_now_site_x;
int mouse_now_site_y;
char mouse_screen_origin[16 * 16];


void mousebuf_deal() {
	io_cli();
	// for(int i=0;i<100000;i++);
	Queue* buf_ptr = &mousebuf;
	unsigned char data;
	if (!queue_empty(buf_ptr)) {
		data = queue_pop(buf_ptr);
		if (mouse_dec.group_flag == -1) {
			if (data == 0xfa) {
				// 等待鼠标的
				mouse_dec.group_flag = 0;
			}
		}
		if ((mouse_dec.group_flag == 0)) {
			if ((data & 0xc8) == 0x08) {
				mouse_dec.group[mouse_dec.group_flag++] = data;
			}
		}
		else {
			mouse_dec.group[mouse_dec.group_flag++] = data;
			// // int size = queue_size(buf_ptr);
			// su_sprintf(tmp_string, "size: %d %x", mouse_dec.group_flag, data& 0xc8);
			// boxfill8_s(0, FONT_Y_SIZE * 6, 10 * FONT_X_SIZE, FONT_Y_SIZE, COL8_000000);
			// putfonts8_asc(0, FONT_Y_SIZE * 6, COL8_FFFFFF, tmp_string);
		}
	}

	if (mouse_dec.group_flag == 3) {
		mouse_dec.group_flag = 0;
		// show
		unsigned char m0 = mouse_dec.group[0];
		// 高4位中低2位与x,y的移动方向有关，
		// 当bit4为1时，表示鼠标向－x方向移动，当bit5为1时表示鼠标向-y方向移动


		mouse_dec.btn = m0 & 0x07; // 0b0111
		mouse_dec.x = mouse_dec.group[1];
		mouse_dec.y = mouse_dec.group[2];
		if ((m0 & 0x10) != 0) // 0b0001 0000
			mouse_dec.x |= 0xffffff00;
		// mouse_dec.x =0;
		if ((m0 & 0x20) != 0) // 0b0010 0000
			mouse_dec.y |= 0xffffff00;
		// mouse_dec.y =0;
// #define abs(a) (a<0?-a:a)
		// if(abs(mouse_dec.x)>22)mouse_dec.x=0;
		// if(abs(mouse_dec.y)>22)mouse_dec.y=0;
		// if(mouse_dec.x<0)mouse_dec.x=-1;

		// mouse_dec.x = mouse_dec.x > 0 ? 1 :(mouse_dec.x<0? -1:0);
		// mouse_dec.y = mouse_dec.y > 0 ? 1 :(mouse_dec.y<0? -1:0);
		// mouse_dec.y = mouse_dec.y > 0 ? 1 : -1;
		mouse_dec.y = -mouse_dec.y;

		// int tmp[3] = { mouse_dec.btn, mouse_now_site_x, mouse_now_site_y };
		int tmp[3] = { mouse_dec.btn,mouse_dec.x,mouse_dec.y };

		for (int i = 0; i < 3; i++) {
			int n = tmp[i];
			su_sprintf(tmp_string, "%d", n);
			int x = FONT_X_SIZE * (i * 5);
			boxfill8_s(x, 3 * FONT_Y_SIZE, 5 * FONT_X_SIZE, FONT_Y_SIZE, COL8_000000);
			putfonts8_asc(x, 3 * FONT_Y_SIZE, COL8_FFFFFF, tmp_string);
		}
		putblock(mouse_now_site_x, mouse_now_site_y, 16, 16, mouse_screen_origin);

		// if (mouse_dec.x >= 0 && mouse_dec.x <= DISPLAY_X_SIZE - 16)
		mouse_now_site_x += mouse_dec.x;
		if (mouse_now_site_x < 0) mouse_now_site_x = 0;
		if (mouse_now_site_x > DISPLAY_X_SIZE - 16) mouse_now_site_x = DISPLAY_X_SIZE - 16;
		// if (mouse_dec.y >= 0 && mouse_dec.y <= DISPLAY_Y_SIZE - 16)
		mouse_now_site_y += mouse_dec.y;
		if (mouse_now_site_y < 0) mouse_now_site_y = 0;
		if (mouse_now_site_y > DISPLAY_Y_SIZE - 16) mouse_now_site_y = DISPLAY_Y_SIZE - 16;

		getblock(mouse_now_site_x, mouse_now_site_y, 16, 16, mouse_screen_origin);
		putblock(mouse_now_site_x, mouse_now_site_y, 16, 16, mouse_cursor);
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
	mouse_dec.group_flag = -1;
	return; /* 顺利的话，键盘控制器会返回ACK(0xfa) */
}

void init_mouse_cursor8(char* mouse) {
	char outline = COL8_000000;
	char inside = COL8_FFFFFF;
	const static char mouse_cursor_img[16][16] = {
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
			char c = mouse_cursor_img[x][y];
			switch (c) {
			case 'O':
				m = inside;
				break;
			case '*':
				m = outline;
				break;
			case '.':
				m = -1;
				break;
			}
			mouse[y * 16 + x] = m;
		}
	}


	mouse_now_site_x = 100;
	mouse_now_site_y = 100;
	putblock(mouse_now_site_x, mouse_now_site_y, 16, 16, mouse);
}