; naskfunc
; TAB=4

; オブジェクトファイルのための情報

section .text
	GLOBAL	io_hlt			; このプログラムに含まれる関数名


; 以下は実際の関数


io_hlt:	; void io_hlt(void);
		HLT
		RET
