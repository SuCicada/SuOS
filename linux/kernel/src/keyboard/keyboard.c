#include "header.h"
#include "keyboard.h"

KEYBUF keybuf;
unsigned char keybuf_mem[32]; // 为了能初始化固定的内存空间
char tmp_string[128];


void wait_KBC_sendready(void) {
    /* 等待键盘控制电路准备完毕 */
    for (;;) {
        if ((io_in8(PORT_KEYSTA) & KEYSTA_SEND_NOTREADY) == 0) {
            break;
        }
    }
    return;
}


void enable_keyboard(void) {
    /* 初始化键盘控制电路 */
    wait_KBC_sendready();
    io_out8(PORT_KEYCMD, KEYCMD_WRITE_MODE);
    wait_KBC_sendready();
    io_out8(PORT_KEYDAT, KBC_MODE);
    return;
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
