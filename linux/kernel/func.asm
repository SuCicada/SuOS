; naskfunc
; TAB=4

; �I�u�W�F�N�g�t�@�C���̂��߂̏��

section .text
	GLOBAL	io_hlt			; ���̃v���O�����Ɋ܂܂��֐���
	GLOBAL	write_mem8

; �ȉ��͎��ۂ̊֐�


io_hlt:	; void io_hlt(void);
	HLT
	RET
write_mem8:
	MOV		ECX,[ESP+4]
	MOV		AL,[ESP+8]
	MOV		[ECX],AL
	RET
