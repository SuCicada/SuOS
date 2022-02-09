#include "mmu.h"

# Start the CPU: switch to 32-bit protected mode, jump into C.
# The BIOS loads this code from the first sector of the hard disk into
# memory at physical address 0x7c00 and starts executing in real mode
# with %cs=0 %ip=7c00.
#define CYLS			0x0ff0
#define LEDS			0x0ff1
#define VMODE			0x0ff2
#define SCRNX			0x0ff4
#define SCRNY			0x0ff6
#define VRAM			0x0ff8

.set PROT_MODE_CSEG, 0x8         # kernel code segment selector
.set PROT_MODE_DSEG, 0x10        # kernel data segment selector
.set CR0_PE_ON,      0x1         # protected mode enable flag

.globl entry
entry:
  .code16                     # Assemble for 16-bit mode
  jmp start

msg:
  .asciz "\r\n\n\rmy kernel is runing jos"

try:
  .asciz "\r\n\n\rtry it again"

puts:
    movb (%si),%al
    add $1,%si
    cmp $0,%al
    je over
    movb $0x0e,%ah
    movw $15,%bx
    int $0x10
    jmp puts
over:
    ret

start:

  # Set up the important data segment registers (DS, ES, SS).
  xorw    %ax,%ax             # Segment number zero
  movw    %ax,%ds             # -> Data Segment
  movw    %ax,%es             # -> Extra Segment
  movw    %ax,%ss             # -> Stack Segment

# 画面设置
  movb $0x13,%al            # ; vga 320x200x8 位,color mode
  movb $0x00,%ah
  int $0x10

  # save color mode in ram 0x0ff0
  movb $8,(VMODE)
  movw $320,(SCRNX)
  movw $200,(SCRNY)
  movl $0x000a0000,(VRAM)

# get keyboard led status
# 通过 BIOS 获取指示灯状态
  movb	$0x02,%ah
  int   $0x16			# keyboard interrupts
  movb  %al,(LEDS)

# diplay something
  movw $msg,%si
  call puts

  movw $try,%si
  call puts

#	PIC关闭一切中断
#	根据AT兼容机的规格，如果要初始化PIC，
#	必须在CLI之前进行，否则有时会挂起。
#	随后进行PIC的初始化。
  movb $0xff,%al
  outb %al, $0x21 # format  outb data port
  nop             # 如果连续执行OUT指令，有些机种会无法正常运
  out %al, $0xa1
  # jmp .
   cli                         # 禁止CPU级别的中断, Disable interrupts
  #  cld                         # String operations increment

# Enable A20:
#   For backwards compatibility with the earliest PCs, physical
#   address line 20 is tied low, so that addresses higher than
#   1MB wrap around to zero by default.  This code undoes this.
#	为了让CPU能够访问1MB以上的内存空间，设定A20GATE
seta20.1:
#   inb     $0x64,%al               # Wait for not busy
#   testb   $0x2,%al
#   jnz     seta20.1
  call waitkbdout
  movb    $0xd1,%al               # 0xd1 -> port 0x64
  outb    %al,$0x64

seta20.2:
#   inb     $0x64,%al               # Wait for not busy
#   testb   $02,%al
#   jnz     seta20.2
  call waitkbdout
  movb    $0xdf,%al               # 0xdf -> port 0x60
  outb    %al,$0x60

  call	waitkbdout
  jmp   set_lgdt

waitkbdout:
  inb     $0x64, %al               # Wait for not busy
  testb   $02,   %al
  inb 		$0x60, %al              # 空读（为了清空数据接收缓冲区中的垃圾数据）
  jnz     waitkbdout

set_lgdt:
  # Switch from real to protected mode, using a bootstrap GDT       this is vip ,but i don`t know it clearly now
  # and segment translation that makes virtual addresses
  # identical to their physical addresses, so that the
  # effective memory map does not change during the switch.
  lgdt    gdtdesc
  movl    %cr0, %eax
  andl		$0x7fffffff, %eax	# 设bit31为0（禁用分页）
  orl     $CR0_PE_ON, %eax  # bit0到1转换（保护模式过渡）, CR0_PE_ON=0x1
  movl    %eax, %cr0

  # 这个地方非常的重要，一但这条movl %eax,%cr0把cr0的pe位打开后，下面的
  # 代码就是32位的，所以空上ljmp的指令是条过度指令，选择 用的gdt是1*8,
  # 也就是第一个gdt(从0开始的)。
  # Jump to next instruction, but in 32-bit code segment.
  # Switches processor into 32-bit mode.
  # 跳转是为了让 cpu 跳过pipeline已经缓存的解释了的后面的指令,
  #   而要重新解释一遍指令
  ljmp    $(2<<3), $protcseg



# ######################################################################
# 正式进入32位的保护模式。
.code32                     # Assemble for 32-bit mode
protcseg:
  # Set up the protected-mode data segment registers
  movw    $(1<<3), %ax    # Our data segment selector
  movw    %ax, %ds                # -> DS: Data Segment
  movw    %ax, %es                # -> ES: Extra Segment
  movw    %ax, %fs                # -> FS
  movw    %ax, %gs                # -> GS
  movw    %ax, %ss                # -> SS: Stack Segment

  # Set up the stack pointer and call into C.
  movl    $start, %esp

#define KERNEL_CODE 0x00280000
copy_main:
  mov $main, %esi
  mov $(0x00080000 / 4), %ecx
  mov $KERNEL_CODE, %edi
  call memcpy


start_main:
  # mov $(bootmain - start + 0x00280000) , %eax
  # mov $0x00280000 , %eax
  pushl $0x00280000
  ret
  # 不知道为什么 ljmp 不行, cs也变了, 但貌似没正确跳转
  # ljmp  $(3<<3),  $0x00280000

  # call bootmain

  # If bootmain returns (it shouldn't), loop.
spin:
  jmp spin

# ================== memcpy ========================
# from:  esi
# size:  ecx
# to:    edi
memcpy:
  # mov %eax, %esi
  # mov %edx, %edi
  mov (%esi), %eax
  mov %eax, (%edi)
  add $4, %esi
  add $4, %edi
  loop memcpy
  ret

#  ======================================================

# Bootstrap GDT
.p2align 2                                # force 4 byte alignment
gdt:
  SEG_NULL			                        	 # null  seg  0
  SEG(STA_W, 0x0, 0xffffffff)	             # data  seg  1
  SEG(STA_X|STA_R, 0x0, 0xfffff<<12)	     # entry seg  2
  SEG(STA_X|STA_R, 0x00280000, 0x7ffff<12) # code  seg  3

  # .word 0xffff,0x0000,0x9200,0x00cf  # data selector 1
  # .word 0xffff,0x0000,0x9a00,0x0047  # entry code    2
  # .word 0xffff,0x0000,0x9a28,0x0047  # c code        3

  .word 0x00
  # .word 0x00
gdtdesc:
  .word   ((3 +1)<<3-1)                            # sizeof(gdt) - 1, 3<<3-1
  .long   gdt                             # address gdt

# .fill 310
main:
