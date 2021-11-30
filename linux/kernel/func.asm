; naskfunc
; TAB=4

; オブジェクトファイルのための情報

section .text
	GLOBAL	io_hlt			; このプログラムに含まれる関数名
	GLOBAL	write_mem8

; 以下は実際の関数


io_hlt:	; void io_hlt(void);
	HLT
	RET
write_mem8:
	MOV		ECX,[ESP+4]
	MOV		AL,[ESP+8]
	MOV		[ECX],AL
	RET
