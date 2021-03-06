#include "header.h"
#include "keyboard.h"
// #include "queue.h"

/* keyboard buffer */

extern KEYBUF keybuf;
extern Queue mousebuf;

void init_pic(void)
/* PIC初始化 */
{
	io_out8(PIC0_IMR, 0xff); /* 禁止所有中断 */
	io_out8(PIC1_IMR, 0xff); /* 禁止所有中断 */

	io_out8(PIC0_ICW1, 0x11); /* 边缘触发模式（edge trigger mode） */
	io_out8(PIC0_ICW2, 0x20); /* IRQ0-7由INT20-27接收 */
	io_out8(PIC0_ICW3, 1 << 2); /* PIC1由IRQ2相连 */
	io_out8(PIC0_ICW4, 0x01); /* 无缓冲区模式 */

	io_out8(PIC1_ICW1, 0x11); /* 边缘触发模式（edge trigger mode） */
	io_out8(PIC1_ICW2, 0x28); /* IRQ8-15由INT28-2f接收 */
	io_out8(PIC1_ICW3, 2); /* PIC1由IRQ2连接 */
	io_out8(PIC1_ICW4, 0x01); /* 无缓冲区模式 */

	io_out8(PIC0_IMR, 0xfb); /* 11111011 PIC1以外全部禁止 */
	io_out8(PIC1_IMR, 0xff); /* 11111111 禁止所有中断 */

	return;
}

void inthandler21(int* esp)
/* 来自PS/2键盘的中断 */
{
	//	putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_000084, "");

	//IRQ-01に受付完了を通知
	io_out8(PIC0_OCW2, 0x61);
	unsigned char data = io_in8(PORT_KEYDAT);
	queue_push(&keybuf.queue, data);


	// char tmp_string[50];
	// su_sprintf(tmp_string, "0x%x", data);
	// boxfill8(0, 0, 4 * FONT_X_SIZE, 31, COL8_000000);
	// putfonts8_asc(0, 0, COL8_FFFFFF, tmp_string);

	// for (int i = 0;i < 10000;i++) {
		// io_hlt();
	// }

	return;
}

void inthandler2c(int* esp)
/* 来自PS/2鼠标的中断 */
{

	io_out8(PIC1_OCW2, 0x64);	/* 通知PIC IRQ-12 已经受理完毕 */
	io_out8(PIC0_OCW2, 0x62);	/* 通知PIC IRQ-02 已经受理完毕 */
	unsigned char data = io_in8(PORT_KEYDAT);
	queue_push(&mousebuf, data);

	// char tmp_string[50];
	// 	su_sprintf(tmp_string, "0x%x", data);
	// 	boxfill8(0, 16, 4 * FONT_X_SIZE, 31, COL8_000000);
	// 	putfonts8_asc(0, 16, COL8_FFFFFF, tmp_string);

	// boxfill8(0, 0, 32 * 8 - 1, 15, COL8_000000);
	// putfonts8_asc(0, 0, COL8_FFFFFF, "INT 2C (IRQ-12) : PS/2 mouse");
	// for (;;) {
	// 	io_hlt();
	// }
}

void inthandler27(int* esp)
/* PIC0中断的不完整策略 */
/* 这个中断在Athlon64X2上通过芯片组提供的便利，只需执行一次 */
/* 这个中断只是接收，不执行任何操作 */
/* 为什么不处理？
	→  因为这个中断可能是电气噪声引发的、只是处理一些重要的情况。*/
{
	io_out8(PIC0_OCW2, 0x67); /* 通知PIC的IRQ-07（参考7-1） */
	return;
}