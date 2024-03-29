.global asm_inthandler21
.global load_cr0, store_cr0

.code32

asm_inthandler21:
  pushw %es
  pushw %ds
  pushal
  movl %esp,%eax
  pushl %eax
  movw %ss,%ax
  movw %ax,%ds
  movw %ax,%es
  call inthandler21
  popl %eax
  popal
  popw %ds
  popW %es
    # pushl %eax
    # popl %ebx
    # pushl
#   ret
    # pushl %ebx
    # pushl %eax

# 总是跳到 0x0000e05b
# f000:e05b is the address that the debugger breaks at in the BIOS when bochs starts up.
# https://stackoverflow.com/questions/29928991/x86-processor-clearing-idtr-and-jumping-to-eip-0xe05b-after-an-int-0x80
  iretl


load_cr0: # int load_cr0()
  mov   %cr0, %eax
  ret
store_cr0: # void store_cr0(int cr0)
  mov   4(%esp), %eax
  mov   %eax, %cr0
  ret
