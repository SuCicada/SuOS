extern void io_hlt(void);
extern void write_mem8(int addr, int data);
extern int io_read_eflags();
extern void io_cli();
extern void io_sti();
extern void io_store_eflags(int flag);
extern void io_out8(int port, int data);
extern char io_in8(int port);

extern void load_idtr(int limit, int addr);
extern void load_gdtr(int limit, int addr);

void asm_inthandler21();
void asm_inthandler27();
void asm_inthandler2c();