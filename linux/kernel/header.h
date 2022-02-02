#include "asmfunc.h"
#include "queue.h"

int su_sprintf(char* __stream, char* __format, ...);

struct BootInfo {
	char cyls, leds, vmode, reserve; // 1 byte * 4 ;
	short scrnx, scrny;				 // 2 byte * 2 ; x_size, y_size
	char* vram;						 // 4 byte
};

// 记录 boot 信息的地址
#define ADR_BOOTINFO	0x00000ff0
void init_display_info(struct BootInfo* binfo);


void init_pic(void);
void inthandler21(int* esp);
void inthandler27(int* esp);
void inthandler2c(int* esp);

/* dsctbl.c */
struct SEGMENT_DESCRIPTOR {     // 8 byte
	short limit_low, base_low;
	char base_mid, access_right;
	char limit_high, base_high;
};
struct GATE_DESCRIPTOR {         // 8 byte
	short offset_low, selector;  // 2 + 2
	char dw_count, access_right; // 1 +2
	short offset_high;           // 2
};


/*  int.c */
/*初始化关系 */
#define PIC0_ICW1		0x0020
#define PIC0_OCW2		0x0020
#define PIC0_IMR		0x0021
#define PIC0_ICW2		0x0021
#define PIC0_ICW3		0x0021
#define PIC0_ICW4		0x0021
#define PIC1_ICW1		0x00a0
#define PIC1_OCW2		0x00a0
#define PIC1_IMR		0x00a1
#define PIC1_ICW2		0x00a1
#define PIC1_ICW3		0x00a1
#define PIC1_ICW4		0x00a1

void set_segmdesc(struct SEGMENT_DESCRIPTOR* sd, unsigned int limit, int base, int ar);
void set_gatedesc(struct GATE_DESCRIPTOR* gd, int offset, int selector, int ar);
void init_gdtidt(void);


/* color.h  */
void init_palette();


/* 键盘端口 */
#define PORT_KEYDAT 0x0060

struct KEYBUF {
	Queue queue;
	int size;
};
#define KEYBUF struct KEYBUF