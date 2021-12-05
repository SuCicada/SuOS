#include <asmfunc.h>
#include <color.c>

//注意这里的函数名字为bootmain，因为在entry.S中设定的入口名字也是bootmain，两者要保持一致
// void init_palette(void);
void bootmain(void)
{
	init_palette();
	int i;
	// 0xa0000 -> 0xaffff is screen memery
	int start = 0xa0000;
	int end = 0xaffff;

	for(i=0xa0000;i<=0xa4fff;i++){
		// write_mem8(i,x);
		*((char *)i) = i & 0xff;
	}
	for(i=0xa6000;i<=0xaffff;i++){
		*((char *)i) = 0;
		// write_mem8(i,3);
	}
	// for(i=start;i<=end;i++){
	// 	write_mem8(i,15);
	// }
	// // while(1);
fin:
	io_hlt();
	goto fin;
}

// void set_palette(int start, int end, unsigned char *rgb_table);

// unsigned char rgb_table[16 * 3] = {
// 	0xff, 0xff, 0xff, // 000000 : 0 : 黒
// 	0xff, 0x00, 0x00, // ff0000 : 1 : 明るい赤
// 	0x00, 0xff, 0x00, // 00ff00 : 2 : 明るい緑
// 	0xff, 0xff, 0x00, // ffff00 : 3 : 黄色
// 	0x00, 0x00, 0xff, // 0000ff : 4 : 明るい青
// 	0xff, 0x00, 0xff, // ff00ff : 5 : 明るい紫
// 	0x00, 0xff, 0xff, // 00ffff : 6 : 明るい水色
// 	0xff, 0xff, 0xff, // ffffff : 7 : 白
// 	0xc6, 0xc6, 0xc6, // c6c6c6 : 8 : 明るい灰色
// 	0x84, 0x00, 0x00, // 840000 : 9 : 暗い赤
// 	0x00, 0x84, 0x00, // 008400 : 10: 暗い緑
// 	0x84, 0x84, 0x00, // 848400 : 11: 暗い黄色
// 	0x00, 0x00, 0x84, // 000084 : 12: 暗い青
// 	0x84, 0x00, 0x84, // 840084 : 13: 暗い紫
// 	0x00, 0x84, 0x84, // 008484 : 14: 暗い水色
// 	0x84, 0x84, 0x84, // 848484 : 15: 暗い灰色
// };
// void init_palette()
// {
// 	// set_palette(0, 15, rgb_table);
// 	//   return;
// 	// static char 命令は、データにしか使えないけどDB命令担当
// 	// }

// 	// void set_palette(int start, int end, unsigned char *rgb_table){
// 	int start = 0, end = 15;
// 	int flag = io_read_eflags();
// 	io_cli();
// 	unsigned char *rgb_table_pnt = rgb_table;
// 	io_out8(0x03c8, start);
// 	for (int i = start; i <= end; i++)
// 	{
// 		// io_out8(0x03c9, 0xff);
// 		// io_out8(0x03c9, 0x00);
// 		// io_out8(0x03c9, 0x00);
// 		for (int j = 0; j < 3; j++)
// 		{
// 			// io_out8(0x03c9, rgb_table_pnt[j] + 0x0f);
// 			io_out8(0x03c9, rgb_table[i * 3 + j] / 4);
// 			// rgb_table[j]
// 		}
// 		rgb_table_pnt += 3;
// 	}
// 	io_store_eflags(flag);
// 	// io_sti();
// 	return;
// }
