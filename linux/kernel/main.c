#include<header.h>
extern void io_hlt(void);

void bootmain(void){
//注意这里的函数名字为bootmain，因为在entry.S中设定的入口名字也是bootmain，两者要保持一致
fin:
	io_hlt();
	goto fin;
	// while(1);
}