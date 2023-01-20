#ifndef KEYBUF
struct KEYBUF {
    Queue queue;
    int size;
};
#define KEYBUF struct KEYBUF
#endif

void wait_KBC_sendready(void);

void keybuf_init();
void keybuf_deal();
void enable_keyboard();

#ifndef TMP_STRING
#define TMP_STRING
static char tmp_string[128];
#endif
