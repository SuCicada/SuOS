#include <stdio.h>
// #include "../kernel/utils.c"
#include "../kernel/header.h"
// #include "../kernel/mmu.h"
// #include "../kernel/dsctbl.c"
#include <unistd.h>
#define STA_X		0x8	    // Executable segment
#define STA_E		0x4	    // Expand down (non-executable segments)
#define STA_C		0x4	    // Conforming code segment (executable only)
#define STA_W		0x2	    // Writeable (non-executable segments)
#define STA_R		0x2	    // Readable (executable segments)
#define STA_A		0x1	    // Accessed
void set_gatedesc(struct GATE_DESCRIPTOR* gd, int offset, int selector, int ar)
{
    gd->offset_low = offset & 0xffff;
    gd->selector = selector;
    gd->dw_count = (ar >> 8) & 0xff;	// 1 byte
    gd->access_right = ar & 0xff;		// 1 byte
    gd->offset_high = (offset >> 16) & 0xffff;	// 2 byte
    return;
}
void seg(int type, int base, int lim) {
    printf("0x%04x \n", ((lim) >> 12) & 0xffff);
    printf("0x%04x \n", ((base) & 0xffff));
    printf("0x%02x \n", ((base) >> 16) & 0xff);
    printf("0x%02x \n", (0x90 | (type)));
    printf("0x%02x \n", (0xC0 | (((lim) >> 28) & 0xf)));
    printf("0x%02x \n", (((base) >> 24) & 0xff));


(0xC0 | (((lim) >> 28) & 0xf)) == 0x47

}
int main() {
    sleep(1);
    unsigned char s[100] = { 0 };
    int len;


    struct SEGMENT_DESCRIPTOR* gdt = (struct SEGMENT_DESCRIPTOR*)s;

    // 0x280000
    // set_gatedesc(gdt, 0x7ffff, 0x00280000, 0x409a);
    // for (int i = 0;i < 8;i++) {
    //     printf("0x%02x ", (unsigned  int)s[i]);
    // }
    // seg(STA_W, 0x0, 0xffffffff);
    // printf("\n");

    seg(STA_X | STA_R, 0x0, 0x0007ffff << 12);
    return 0;

}
