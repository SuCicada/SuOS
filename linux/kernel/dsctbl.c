/*
GDT、IDT、descriptor tabl系处理 
GDT: 用于记录段号的. 只能记录 13位即 8192个段
	每个段需要 8 字节存储, 所以一共 64KB, 即 2^16, 0x10000
IDT: 记录0-255中断码和函数的对应
*/

#include "asmfunc.h"
#include "header.h"


#define ADR_IDT			0x0026f800
#define LIMIT_IDT		0x000007ff
#define ADR_GDT			0x00270000
#define LIMIT_GDT		0x0000ffff

#define ADR_BOTPAK		0x00280000
#define LIMIT_BOTPAK	0x0007ffff

#define AR_DATA32_RW	0x4092
#define AR_CODE32_ER	0x409a
#define AR_INTGATE32	0x008e

void init_gdtidt(void)
{
	struct SEGMENT_DESCRIPTOR* gdt = (struct SEGMENT_DESCRIPTOR*)ADR_GDT;
	struct GATE_DESCRIPTOR* idt = (struct GATE_DESCRIPTOR*)ADR_IDT;
	int i;

	/* 存储 GDT 的内存空间初始化
	   0x00270000 -- 0x00270000 + 0x0000ffff : 设置为GDT, 这个地址可以随便指定
	*/
	for (i = 0; i <= LIMIT_GDT / 8; i++) {
		set_segmdesc(gdt + i, 0, 0, 0);
	}
	// cpu 能管理的全部内存本身, 4GB
	set_segmdesc(gdt + 1, 0xffffffff, 0x00000000, AR_DATA32_RW);

	/* 为我们的主程序准备
		设定第二段段空间
		todo: 这里大有文章, 需要以后慢慢研究, 目前只能保证能跑通
	 */
	set_segmdesc(gdt + 2, 0x000fffff, 0x00000000, 0x409a);
	set_segmdesc(gdt + 3, 0x0007ffff, 0x00280000, AR_CODE32_ER);

	/* 设定 ADR_GDT -> ADR_GDT+LIMIT_GDT 这段空间用于 GDT, 注册到 LGDT 寄存器 */
	load_gdtr(LIMIT_GDT, ADR_GDT);


	/* IDT初始化 */
	for (i = 0; i <= LIMIT_IDT / 8; i++) {
		set_gatedesc(idt + i, 0, 0, 0);
	}
	load_idtr(LIMIT_IDT, ADR_IDT);

	/* IDT设置
		注册函数到IDT, 中断发生会执行
		2<<3 : 代表属于2段, 低3位必须为0
	*/
	int int_seg_index = 2;

	// for (i = 0; i < 256; i++) {
	// 	set_gatedesc(idt + i, (int)asm_inthandler21, 3 * 8, 0x008e);
	// }
	int offset = 0;
	set_gatedesc(idt + 0x21, (int)asm_inthandler21 - offset, int_seg_index << 3, AR_INTGATE32);
	set_gatedesc(idt + 0x27, (int)asm_inthandler27 - offset, int_seg_index << 3, AR_INTGATE32);
	set_gatedesc(idt + 0x2c, (int)asm_inthandler2c - offset, int_seg_index << 3, AR_INTGATE32);

	return;
}

/*
limit 上限  只20位
base  基址
ar    (access_right) 段属性, 段的访问权属性,

段属性高4位要写入 limit_high 的上4位中, 低8位放置 ar
高4位: 扩展访问权, GD00: G:G bit, D:段模式, 1:32位模式, 0:16位模式
0x92 系统用, 可rw, 不可x
0x9a 系统用, 不可w, 可x
0xf2 应用用, 可rw, 不可x
0xfa 应用用, 不可w, 可x

 */
void set_segmdesc(struct SEGMENT_DESCRIPTOR* sd, unsigned int limit, int base, int ar)
{
	if (limit > 0xfffff) {
		ar |= 0x8000; /* G_bit = 1 */
		//01000000 00000000
		limit /= 0x1000;
	}
	sd->limit_low = limit & 0xffff;
	sd->base_low = base & 0xffff;
	sd->base_mid = (base >> 16) & 0xff;
	sd->access_right = ar & 0xff;
	// 最高的 4 位
	sd->limit_high = ((limit >> 16) & 0x0f) | ((ar >> 8) & 0xf0);
	sd->base_high = (base >> 24) & 0xff;
	return;
}

void set_gatedesc(struct GATE_DESCRIPTOR* gd, int offset, int selector, int ar)
{
	gd->offset_low = offset & 0xffff;
	gd->selector = selector;
	gd->dw_count = (ar >> 8) & 0xff;	// 1 byte
	gd->access_right = ar & 0xff;		// 1 byte
	gd->offset_high = (offset >> 16) & 0xffff;	// 2 byte
	return;
}
