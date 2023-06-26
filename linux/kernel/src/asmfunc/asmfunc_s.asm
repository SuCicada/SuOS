; Disassembly of file: output/asmfunc.o
; Wed Jun 21 11:18:21 2023
; Type: ELF32
; Syntax: NASM
; Instruction set: 80386, privileged instructions


SECTION .text
    global asm_inthandler21
    global load_cr0
    global store_cr0
    extern inthandler21                                     ; near



asm_inthandler21:; Function begin
; Note: Prefix bit or byte has no meaning in this context
        push es                                         ; 0000 _ 66: 06
; Note: Prefix bit or byte has no meaning in this context
        push ds                                         ; 0002 _ 66: 1E
        pushad                                          ; 0004 _ 60
        mov     eax, esp                                ; 0005 _ 89. E0
        push    eax                                     ; 0007 _ 50
        mov     ax, ss                                  ; 0008 _ 66: 8C. D0
        mov     ds, eax                                 ; 000B _ 8E. D8
        mov     es, eax                                 ; 000D _ 8E. C0
        call    inthandler21                            ; 000F _ E8, FFFFFFFC(rel)
        pop     eax                                     ; 0014 _ 58
        popad                                           ; 0015 _ 61
; Note: Prefix bit or byte has no meaning in this context
        pop  ds                                         ; 0016 _ 66: 1F
; Note: Prefix bit or byte has no meaning in this context
        pop  es                                         ; 0018 _ 66: 07
        iretd                                           ; 001A _ CF
; asm_inthandler21 End of function

load_cr0:; Function begin
        mov     eax, cr0                                ; 001B _ 0F 20. C0
        ret                                             ; 001E _ C3
; load_cr0 End of function

store_cr0:; Function begin
        mov     eax, dword [esp+4H]                     ; 001F _ 8B. 44 24, 04
        mov     cr0, eax                                ; 0023 _ 0F 22. C0
        ret                                             ; 0026 _ C3

