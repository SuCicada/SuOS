	.file	"test_utils.c"
	.text
	.comm	temp_str,20,16
	.section	.rodata
.LC0:
	.string	"xxxx %d\n"
	.text
	.globl	su_sprintf
	.type	su_sprintf, @function
su_sprintf:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$240, %rsp
	movq	%rdi, -232(%rbp)
	movq	%rsi, -240(%rbp)
	movq	%rdx, -160(%rbp)
	movq	%rcx, -152(%rbp)
	movq	%r8, -144(%rbp)
	movq	%r9, -136(%rbp)
	testb	%al, %al
	je	.L20
	movaps	%xmm0, -128(%rbp)
	movaps	%xmm1, -112(%rbp)
	movaps	%xmm2, -96(%rbp)
	movaps	%xmm3, -80(%rbp)
	movaps	%xmm4, -64(%rbp)
	movaps	%xmm5, -48(%rbp)
	movaps	%xmm6, -32(%rbp)
	movaps	%xmm7, -16(%rbp)
.L20:
	movq	-232(%rbp), %rax
	movq	%rax, -192(%rbp)
	leaq	-240(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -184(%rbp)
	jmp	.L3
.L18:
	cmpb	$37, -219(%rbp)
	jne	.L4
	movq	-240(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -218(%rbp)
	movq	-240(%rbp), %rax
	movzbl	1(%rax), %eax
	movb	%al, -217(%rbp)
	movl	$0, -212(%rbp)
	movb	$32, -220(%rbp)
	cmpb	$47, -217(%rbp)
	jle	.L5
	cmpb	$57, -217(%rbp)
	jg	.L5
	movzbl	-218(%rbp), %eax
	movb	%al, -220(%rbp)
	movsbl	-217(%rbp), %eax
	subl	$48, %eax
	movl	%eax, -212(%rbp)
	movq	-240(%rbp), %rax
	addq	$2, %rax
	movq	%rax, -240(%rbp)
	jmp	.L6
.L5:
	cmpb	$47, -218(%rbp)
	jle	.L6
	cmpb	$57, -218(%rbp)
	jg	.L6
	movsbl	-218(%rbp), %eax
	subl	$48, %eax
	movl	%eax, -212(%rbp)
	movq	-240(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -240(%rbp)
.L6:
	movq	-240(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -240(%rbp)
	movzbl	(%rax), %eax
	movb	%al, -219(%rbp)
	movl	$0, -208(%rbp)
	movsbl	-219(%rbp), %eax
	cmpl	$120, %eax
	je	.L7
	cmpl	$120, %eax
	jg	.L21
	cmpl	$117, %eax
	je	.L9
	cmpl	$117, %eax
	jg	.L21
	cmpl	$37, %eax
	je	.L10
	cmpl	$100, %eax
	je	.L11
	jmp	.L21
.L7:
	movq	-184(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -196(%rbp)
	movl	-196(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$4, -184(%rbp)
	movl	$1, -208(%rbp)
	movl	-196(%rbp), %eax
	leaq	temp_str(%rip), %rsi
	movl	%eax, %edi
	call	int2hexstr
	movl	%eax, -216(%rbp)
	jmp	.L12
.L11:
	movq	-184(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -196(%rbp)
	addq	$4, -184(%rbp)
	movl	$1, -208(%rbp)
	movl	-196(%rbp), %eax
	leaq	temp_str(%rip), %rsi
	movl	%eax, %edi
	call	int2str
	movl	%eax, -216(%rbp)
	jmp	.L12
.L9:
	movq	-184(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -196(%rbp)
	addq	$4, -184(%rbp)
	movl	$1, -208(%rbp)
	movl	-196(%rbp), %eax
	leaq	temp_str(%rip), %rsi
	movl	%eax, %edi
	call	uint2str
	movl	%eax, -216(%rbp)
	jmp	.L12
.L10:
	movq	-192(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -192(%rbp)
	movb	$37, (%rax)
	jmp	.L12
.L21:
	nop
.L12:
	cmpl	$1, -208(%rbp)
	jne	.L3
	movl	-216(%rbp), %eax
	cmpl	-212(%rbp), %eax
	jge	.L13
	movl	$0, -204(%rbp)
	jmp	.L14
.L15:
	movq	-192(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -192(%rbp)
	movzbl	-220(%rbp), %edx
	movb	%dl, (%rax)
	addl	$1, -204(%rbp)
.L14:
	movl	-212(%rbp), %eax
	subl	-216(%rbp), %eax
	cmpl	%eax, -204(%rbp)
	jl	.L15
.L13:
	movl	$0, -200(%rbp)
	jmp	.L16
.L17:
	movq	-192(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -192(%rbp)
	movl	-200(%rbp), %edx
	movslq	%edx, %rdx
	leaq	temp_str(%rip), %rcx
	movzbl	(%rdx,%rcx), %edx
	movb	%dl, (%rax)
	addl	$1, -200(%rbp)
.L16:
	movl	-200(%rbp), %eax
	cmpl	-216(%rbp), %eax
	jl	.L17
	jmp	.L3
.L4:
	movq	-192(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -192(%rbp)
	movzbl	-219(%rbp), %edx
	movb	%dl, (%rax)
.L3:
	movq	-240(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -240(%rbp)
	movzbl	(%rax), %eax
	movb	%al, -219(%rbp)
	cmpb	$0, -219(%rbp)
	jne	.L18
	movq	-192(%rbp), %rax
	movb	$0, (%rax)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	su_sprintf, .-su_sprintf
	.globl	int2str
	.type	int2str, @function
int2str:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -4(%rbp)
	cmpl	$0, -20(%rbp)
	jns	.L23
	movq	-32(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -32(%rbp)
	movb	$45, (%rax)
	negl	-20(%rbp)
	movl	$1, -4(%rbp)
.L23:
	movq	-32(%rbp), %rcx
	movl	-20(%rbp), %eax
	movl	$10, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	int2basestr
	movl	-4(%rbp), %edx
	addl	%edx, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	int2str, .-int2str
	.globl	uint2str
	.type	uint2str, @function
uint2str:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	-4(%rbp), %eax
	movq	-16(%rbp), %rsi
	movl	$1, %ecx
	movl	$10, %edx
	movl	%eax, %edi
	call	int2basestr0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	uint2str, .-uint2str
	.globl	basechar2int
	.type	basechar2int, @function
basechar2int:
.LFB3:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	cmpb	$47, -4(%rbp)
	jle	.L28
	cmpb	$57, -4(%rbp)
	jg	.L28
	movsbl	-4(%rbp), %eax
	subl	$48, %eax
	jmp	.L29
.L28:
	movsbl	-4(%rbp), %eax
	subl	$87, %eax
.L29:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	basechar2int, .-basechar2int
	.globl	int2basechar
	.type	int2basechar, @function
int2basechar:
.LFB4:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	cmpl	$9, -4(%rbp)
	jg	.L31
	movl	-4(%rbp), %eax
	addl	$48, %eax
	jmp	.L32
.L31:
	movl	-4(%rbp), %eax
	addl	$87, %eax
.L32:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	int2basechar, .-int2basechar
	.globl	int2hexstr
	.type	int2hexstr, @function
int2hexstr:
.LFB5:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	cmpl	$0, -20(%rbp)
	jns	.L34
	addl	$-2147483648, -20(%rbp)
.L34:
	movq	-32(%rbp), %rcx
	movl	-20(%rbp), %eax
	movl	$16, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	int2basestr
	movl	%eax, -4(%rbp)
	movq	-32(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	basechar2int
	addl	$8, %eax
	movl	%eax, %edi
	call	int2basechar
	movq	-32(%rbp), %rdx
	movb	%al, (%rdx)
	movl	-4(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	int2hexstr, .-int2hexstr
	.globl	int2basestr
	.type	int2basestr, @function
int2basestr:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -8(%rbp)
	movl	-8(%rbp), %edx
	movq	-16(%rbp), %rsi
	movl	-4(%rbp), %eax
	movl	$0, %ecx
	movl	%eax, %edi
	call	int2basestr0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	int2basestr, .-int2basestr
	.globl	int2basestr0
	.type	int2basestr0, @function
int2basestr0:
.LFB7:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$40, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -24(%rbp)
	movl	%ecx, -36(%rbp)
	movl	$0, -12(%rbp)
.L41:
	cmpl	$0, -36(%rbp)
	je	.L39
	movl	-20(%rbp), %eax
	movl	-24(%rbp), %ecx
	movl	$0, %edx
	divl	%ecx
	movl	%edx, %eax
	movl	%eax, -8(%rbp)
	jmp	.L40
.L39:
	movl	-20(%rbp), %eax
	cltd
	idivl	-24(%rbp)
	movl	%edx, -8(%rbp)
.L40:
	movl	-8(%rbp), %eax
	movl	%eax, %edi
	call	int2basechar
	movb	%al, -14(%rbp)
	movl	-12(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -12(%rbp)
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movzbl	-14(%rbp), %eax
	movb	%al, (%rdx)
	movl	-20(%rbp), %eax
	cltd
	idivl	-24(%rbp)
	movl	%eax, -20(%rbp)
	cmpl	$0, -20(%rbp)
	jne	.L41
	movl	$0, -4(%rbp)
	jmp	.L42
.L43:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movb	%al, -13(%rbp)
	movl	-12(%rbp), %eax
	subl	-4(%rbp), %eax
	cltq
	leaq	-1(%rax), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rcx
	movq	-32(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	movl	-12(%rbp), %eax
	subl	-4(%rbp), %eax
	cltq
	leaq	-1(%rax), %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movzbl	-13(%rbp), %eax
	movb	%al, (%rdx)
	addl	$1, -4(%rbp)
.L42:
	movl	-12(%rbp), %eax
	movl	%eax, %edx
	shrl	$31, %edx
	addl	%edx, %eax
	sarl	%eax
	cmpl	%eax, -4(%rbp)
	jl	.L43
	movl	-12(%rbp), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	int2basestr0, .-int2basestr0
	.comm	s,100,32
	.section	.rodata
.LC1:
	.string	"%x|"
.LC2:
	.string	"%s|\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB14:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$-23, -8(%rbp)
	movl	-8(%rbp), %eax
	addl	$-2147483648, %eax
	movl	%eax, -4(%rbp)
	movl	$2634848, %edx
	leaq	.LC1(%rip), %rsi
	leaq	s(%rip), %rdi
	movl	$0, %eax
	call	su_sprintf
	leaq	s(%rip), %rsi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
