; naskfunc
; TAB=4

; �I�u�W�F�N�g�t�@�C���̂��߂̏��

section .text
	GLOBAL	io_hlt			; ���̃v���O�����Ɋ܂܂��֐���
	GLOBAL	write_mem8
	GLOBAL	io_cli, io_sti
	GLOBAL	io_read_eflags, io_store_eflags
	GLOBAL	
	GLOBAL	io_out8

; �ȉ��͎��ۂ̊֐�


io_hlt:	; void io_hlt(void);
	HLT
	RET
io_cli: 
	CLI
	RET
io_sti:
	STI
	RET
io_read_eflags:
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
io_out8:
	MOV		EDX, [ESP+4]	;port
	MOV		AL,	[ESP+8]	;data
	OUT 	DX, AL
	RET
