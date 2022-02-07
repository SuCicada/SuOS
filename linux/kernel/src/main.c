#include "header.h"
// #include "hankaku.h"
#include "color.h"
#include "mouse.h"
#include "keyboard.h"

/*
  0xa0000 -> 0xaffff is screen memery
  注意这里的函数名字为bootmain，因为在entry.S中设定的入口名字也是bootmain，两者要保持一致
 */
char tmp_string[128];

_Noreturn void bootmain(void) {

    struct BootInfo* binfo = (struct BootInfo*)ADR_BOOTINFO;
    init_gdtidt();
    init_pic();
    io_sti(); /* IDT/PIC的初始化已经完成，于是开放CPU的中断 */

    init_display_info(binfo);
    keybuf_init();
    mousebuf_init();

    io_out8(PIC0_IMR, 0xf9); /* 开放PIC1和键盘中断(11111001) */
    io_out8(PIC1_IMR, 0xef); /* 开放鼠标中断(11101111) */

    init_palette();
    init_screen();

    su_sprintf(tmp_string, "DISPLAY_X_SIZE = %d ", DISPLAY_X_SIZE);
    putfonts8_asc(5, 10, COL8_FFFFFF, tmp_string);

    init_mouse_cursor8();

    enable_keyboard();
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


#define EFLAGS_AC_BIT       0x00040000
#define CR0_CACHE_DISABLE	0x60000000
unsigned int memtest_sub(unsigned int start, unsigned int end);

unsigned int memtest(unsigned int start, unsigned int end)
{
	char flg486 = 0;
	unsigned int eflg, cr0, i;

	/* 确认CPU是386还是486以上的 */
	eflg = io_load_eflags();
	eflg |= EFLAGS_AC_BIT; /* AC-bit = 1 */
	io_store_eflags(eflg);
	eflg = io_load_eflags();
	if ((eflg & EFLAGS_AC_BIT) != 0) {
		/* 如果是386，即使设定AC=1，AC的值还会自动回到0 */
		flg486 = 1;
	}

	eflg &= ~EFLAGS_AC_BIT; /* AC-bit = 0 */
	io_store_eflags(eflg);

	if (flg486 != 0) {
		cr0 = load_cr0();
		cr0 |= CR0_CACHE_DISABLE; /* 禁止缓存 */
		store_cr0(cr0);
	}

	i = memtest_sub(start, end);

	if (flg486 != 0) {
		cr0 = load_cr0();
		cr0 &= ~CR0_CACHE_DISABLE; /* 允许缓存 */
		store_cr0(cr0);
	}

	return i;
}

unsigned int memtest_sub(unsigned int start, unsigned int end){
    unsigned int i, old, pat0=0xaa55aa55, pat1=0x55aa55aa;
    volatile unsigned int *p;
    for(i=start; i<=end; i+=0x1000){
        p = (unsigned int *)(i+0xffc);
        old = *p;
        *p = pat0;
        *p ^= 0xffffffff;
        if(*p!=pat1){
            not_memory:
            *p = old;
            break;
        }
        *p ^= 0xffffffff;
        if(*p!=pat0){
            goto not_memory;
        }
        *p = old;
    }
    return i;
}
