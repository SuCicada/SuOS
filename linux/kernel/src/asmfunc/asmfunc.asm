; naskfunc
; TAB=4

; オブジェクトファイルのための情報

section .text
	GLOBAL	io_hlt			; このプログラムに含まれる関数名
	GLOBAL	write_mem8
	GLOBAL	io_cli, io_sti
	GLOBAL	io_load_eflags, io_store_eflags
	GLOBAL	io_out8, io_in8
	GLOBAL	load_gdtr, load_idtr
	GLOBAL 	asm_inthandler21, asm_inthandler2c, asm_inthandler27
	EXTERN  inthandler21, inthandler2c, inthandler27


; 以下は実際の関数


io_hlt:	; void io_hlt(void);
	HLT
	RET
io_cli:
	CLI
	RET
io_sti:
	STI
	RET
io_load_eflags:
	PUSHFD		; PUSH EFLAGS  32 bit
	POP 	EAX		; 32 bit
	RET
io_store_eflags:
	MOV		EAX, [ESP+4]
	PUSH	EAX
	POPFD
	RET

write_mem8:
	MOV		ECX, [ESP+4]
	MOV		AL,	 [ESP+8]
	MOV		[ECX], AL
	RET

; void io_out8(int port, int data);
io_out8:
	MOV		EDX, [ESP+4]	;port
	MOV		AL,	[ESP+8]		;data
	OUT 	DX, AL
	RET
; char io_in8(int port);
io_in8:
	MOV		EDX, [ESP+4]	;port
	MOV 	AX, 0
	IN		AL, DX
	RET


; void load_gdtr(int limit, int addr);
; ESP+6 -- ESP+7   2byte  段上限
; ESP+8 -- ESP+11  4byte  地址
load_gdtr:
	MOV		AX, [ESP+4]
	MOV 	[ESP+6], AX
	LGDT 	[ESP+6]		; give to GDTR register
	RET

; void load_idtr(int limit, int addr)
load_idtr:
	mov		ax, [esp + 4]		; limit
	mov 	[esp + 6], ax
	lidt	[esp + 6]
	ret

; asm_inthandler21:
; 	PUSH	ES
; 	PUSH	DS
; 	PUSHA
; 	MOV		EAX,ESP
; 	PUSH	EAX
; 	; 是为了C语言的 inthandler21 能顺利执行
; 	MOV		AX,SS
; 	MOV		DS,AX
; 	MOV		ES,AX
; 	CALL	inthandler21
; 	POP		EAX
; 	POPA
; 	POP		DS
; 	POP		ES
; 	IRET			; 中断返回

asm_inthandler2c:
	PUSH	ES
	PUSH	DS
	PUSHAD
	MOV		EAX,ESP
	PUSH	EAX
	MOV		AX,SS
	MOV		DS,AX
	MOV		ES,AX
	CALL	inthandler2c
	POP		EAX
	POPAD
	POP		DS
	POP		ES
	IRETD			; 中断返回

asm_inthandler27:
	PUSH	ES
	PUSH	DS
	PUSHAD
	MOV		EAX,ESP
	PUSH	EAX
	MOV		AX,SS
	MOV		DS,AX
	MOV		ES,AX
	CALL	inthandler27
	POP		EAX
	POPAD
	POP		DS
	POP		ES
	IRETD			; 中断返回
