void io_hlt(void){}
void write_mem8(int addr, int data){}
void io_cli(){}
void io_sti(){}
int io_load_eflags(){}
void io_store_eflags(unsigned int flag){}
void io_out8(int port, int data){}
unsigned char io_in8(int port){}

void load_idtr(int limit, int addr){}
void load_gdtr(int limit, int addr){}
void asm_inthandler21(){}
void asm_inthandler27(){}
void asm_inthandler2c(){}
int load_cr0(){}
void store_cr0(unsigned int){}
