#include "header.h"
#include "mouse.h"
#include "keyboard.h"

int mouse_now_site_x;
int mouse_now_site_y;
char mouse_screen_origin[16 * 16];

Queue mousebuf;

//char tmp_string[128];

unsigned char mousebuf_mem[32]; // 为了能初始化固定的内存空间
char mouse_cursor[16 * 16];

struct MOUSE_DEC mouse_dec;

void mousebuf_init() {
    int size = sizeof(mousebuf_mem) / sizeof(unsigned char);
    queue_init(&mousebuf, mousebuf_mem, size);
}


void enable_mouse(void) {
    /* 激活鼠标 */
    wait_KBC_sendready();
    io_out8(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);
    wait_KBC_sendready();
    io_out8(PORT_KEYDAT, MOUSECMD_ENABLE);
    mouse_dec.group_flag = -1;
    /* 顺利的话，键盘控制器会返回ACK(0xfa) */
}

void init_mouse_cursor8() {
    char *mouse = mouse_cursor;
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
                default:
                    break;
            }
            mouse[y * 16 + x] = m;
        }
    }


    mouse_now_site_x = 100;
    mouse_now_site_y = 100;
    putblock(mouse_now_site_x, mouse_now_site_y, 16, 16, mouse);
}


void mousebuf_deal() {
    io_cli();
    // for(int i=0;i<100000;i++);
    Queue *buf_ptr = &mousebuf;
    unsigned char data;
    if (!queue_empty(buf_ptr)) {
        data = queue_pop(buf_ptr);
        if (mouse_dec.group_flag == -1) {
            if (data == 0xfa) {
                // 等待鼠标的
                mouse_dec.group_flag = 0;
            }
        }
        if (mouse_dec.group_flag == 0) {
            if ((data & 0xc8) == 0x08) {
                mouse_dec.group[mouse_dec.group_flag++] = data;
            }
        } else {
            mouse_dec.group[mouse_dec.group_flag++] = data;
            // // int size = queue_size(buf_ptr);
            // su_sprintf(tmp_string, "size: %d %x", mouse_dec.group_flag, data& 0xc8);
            // boxfill8_s(0, FONT_Y_SIZE * 6, 10 * FONT_X_SIZE, FONT_Y_SIZE, COL8_000000);
            // putfonts8_asc(0, FONT_Y_SIZE * 6, COL8_FFFFFF, tmp_string);
        }
    }

    if (mouse_dec.group_flag == 3) {
        mouse_dec.group_flag = 0;
        // tree_show
        unsigned char m0 = mouse_dec.group[0];
        // 高4位中低2位与x,y的移动方向有关，
        // 当bit4为1时，表示鼠标向－x方向移动，当bit5为1时表示鼠标向-y方向移动


        mouse_dec.btn = m0 & 0x07; // 0b0111
        mouse_dec.x = mouse_dec.group[1];
        mouse_dec.y = mouse_dec.group[2];
        if ((m0 & 0x10) != 0) // 0b0001 0000
            mouse_dec.x |= (int) 0xffffff00;
        // mouse_dec.x =0;
        if ((m0 & 0x20) != 0) // 0b0010 0000
            mouse_dec.y |= (int) 0xffffff00;
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
        int tmp[3] = {mouse_dec.btn, mouse_dec.x, mouse_dec.y};

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
