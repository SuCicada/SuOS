// #include<header.h>
extern void io_hlt(void);
extern void write_mem8(int addr, int data);
void bootmain(void){
//注意这里的函数名字为bootmain，因为在entry.S中设定的入口名字也是bootmain，两者要保持一致
	int i;
	for(i=0xa0000;i<=0xa4fff;i++){
		// write_mem8(i,x);
		*((char *)i ) = i & 0xff;
	}
	// for(i=0xa6000;i<=0xaffff;i++){
	// 	write_mem8(i,9);
	// }

fin:
	io_hlt();
	goto fin;
	// while(1);
}