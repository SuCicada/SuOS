extern void io_hlt(void);
extern void write_mem8(int addr, int data);
extern void io_cli();
extern void io_sti();
extern int io_load_eflags();
extern void io_store_eflags(unsigned int flag);
extern void io_out8(int port, int data);
extern char io_in8(int port);

extern void load_idtr(int limit, int addr);
extern void load_gdtr(int limit, int addr);

void asm_inthandler21();
void asm_inthandler27();
void asm_inthandler2c();

int load_cr0();
void store_cr0(unsigned int);
