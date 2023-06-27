#ifndef MOUSE_H
#define MOUSE_H

#include "screen.h"

#define KEYCMD_SENDTO_MOUSE		0xd4
#define MOUSECMD_ENABLE			0xf4


struct MOUSE_DEC {
	int group_flag; // a gropu has 3
	unsigned char group[3]; // a gropu has 3
	int x, y, btn;
};


void mousebuf_init();
void mousebuf_deal(SHEET* mouse_sheet);

void enable_mouse();
void init_mouse_cursor8(unsigned char *mouse_cursor);

//extern unsigned char mouse_cursor[16 * 16];

#endif
