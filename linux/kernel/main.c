#include <asmfunc.h>
#include <color.h>

//注意这里的函数名字为bootmain，因为在entry.S中设定的入口名字也是bootmain，两者要保持一致
void bootmain(void){
	init_palette();
	int i;
	// 0xa0000 -> 0xaffff is screen memery
	int start = 0xa0000;
	int end = 0xaffff;

	for(i=0xa0000;i<=0xa4fff;i++){
		// write_mem8(i,x);
		*((char *)i) = i & 0x0f;
	}
	for(i=0xa6000;i<=0xaffff;i++){
		*((char *)i) = 25;
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