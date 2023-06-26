#include "header.h"
// #include "hankaku.h"
#include "color.h"
#include "mouse.h"
#include "keyboard.h"
#include "memory.h"
#include "serial.h"
#include "log.h"
#include "screen.h"
#include "window.h"
/*
  0xa0000 -> 0xaffff is screen memery
  注意这里的函数名字为bootmain，因为在entry.S中设定的入口名字也是bootmain，两者要保持一致
 */
//char tmp_string[128];
char aaaa[324];

/* 注意, bootmain 函数前面不能放任何函数 */
_Noreturn
void bootmain(void) {
    init_serial();
    write_serial_string("hello world\n");

    struct BootInfo *binfo = (struct BootInfo *) ADR_BOOTINFO;
    init_gdtidt();
    init_pic();
    io_sti(); /* IDT/PIC的初始化已经完成，于是开放CPU的中断 */

    init_display_info(binfo);
    keybuf_init();
    mousebuf_init();

    io_out8(PIC0_IMR, 0xf9); /* 开放PIC1和键盘中断(11111001) */
    io_out8(PIC1_IMR, 0xef); /* 开放鼠标中断(11101111) */

    init_palette();
    unsigned int memory_size;
    memory_size = memtest(MEMORY_START_ADDRESS, 0xffffffff);
    log_info("memory_size = %d B\n", memory_size);
    mem_init_config(MEMORY_START_ADDRESS, memory_size);

    int line = 0;
    char *tmp_string = mem_alloc(128);

    su_sprintf(tmp_string, "memory start: %x", memory_map_table.start_address);
    putfonts8_asc_v1(0, FONT_Y_SIZE * line++, COL8_FFFFFF, tmp_string);
    su_sprintf(tmp_string, "memory_size = %d B", memory_size);
    putfonts8_asc_v1(0, FONT_Y_SIZE * line++, COL8_FFFFFF, tmp_string);
    log_println(tmp_string);

    su_sprintf(tmp_string, "memory used = %d B", mem_get_used_size());
    putfonts8_asc_v1(0, FONT_Y_SIZE * line++, COL8_FFFFFF, tmp_string);
    log_println(tmp_string);

    su_sprintf(tmp_string, "DISPLAY_X_SIZE = %d ", DISPLAY_X_SIZE);
    putfonts8_asc_v1(0, FONT_Y_SIZE * line++, COL8_FFFFFF, tmp_string);

    su_sprintf(tmp_string, "0x%x  0x%x", tmp_string, &aaaa[1]);
    putfonts8_asc_v1(0, FONT_Y_SIZE * line++, COL8_FFFFFF, tmp_string);

    mem_free(tmp_string);


    unsigned char *desktop = (unsigned char *) mem_alloc(DISPLAY_X_SIZE * DISPLAY_Y_SIZE);
    unsigned char *win_buf = (unsigned char *) mem_alloc(160 * 65);

    SHTCTL *shtctl = shtctl_init(binfo->vram, binfo->scrnx, binfo->scrny);
    SHEET *sht_back, *sht_win;

    init_screen(desktop, DISPLAY_X_SIZE, DISPLAY_Y_SIZE);

    sht_back = sheet_alloc(shtctl);

    sheet_setbuf(sht_back, desktop, 320, 200, -1);
    sheet_move(sht_back, 0, 0);
    sheet_updown(sht_back, 0);

    // ----- mouse ----------
    unsigned char *mouse_cursor = (unsigned char *) mem_alloc(16 * 16);
    init_mouse_cursor8(mouse_cursor);

    SHEET *sht_mouse = sheet_alloc(shtctl);
    sheet_setbuf(sht_mouse, mouse_cursor, 16, 16, 99);
    sheet_move(sht_mouse, 0, 0);
    sheet_updown(sht_mouse, 2);

    make_window8(win_buf, 160, 68, "counter");


    sheet_refresh(sht_back, 0, 0, DISPLAY_X_SIZE, DISPLAY_Y_SIZE);

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

//        a++;
    }
    // io_hlt();
}



