CYLS    EQU     0x0ff0
LEDS    EQU     0x0ff1
VMODE   EQU     0x0ff2
SCRNX   EQU     0x0ff4
SCRNY   EQU     0x0ff6
VRAM    EQU     0x0ff8

    ORG     0xc400

    MOV     AL,0x13
    MOV     AH,0
    INT     0x10
    MOV     BYTE [VMODE],8
    MOV     WORD [SCRNX],320
    MOV     WORD [SCRNY]
fin:
    HLT
    JMP     fin