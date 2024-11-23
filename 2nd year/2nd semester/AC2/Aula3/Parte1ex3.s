    .data
    .equ    ADDR_BASE_HI,0xBF88
    .equ    TRISE,0x6100
    .equ    PORTE,0x6110
    .equ    LATE,0x6120
    .equ    TRISD,0x60C0
    .equ    PORTD,0x60D0
    .equ    LATD,0x60E0
    .text
    .globl main
main:
    lui $t0,ADDR_BASE_HI
    lw  $t1,TRISE($t0)
    andi $t1,$t1,0xFFFE
    sw  $t1,TRISE($t0)
    lw  $t1,TRISD($t0)
    ori $t1,$t1,0x0100
    sw  $t1,TRISD($t0)
while:
    lw  $t1,PORTD($t0)
    lw  $t2,LATE($t0)
    andi $t1,$t1,0x0100
    srl $t1,$t1,8
    nor $t1,$t1,$0
    andi $t2,$t2,0xFFFE
    or  $t1,$t1,$t2
    sw  $t1,LATE($t0)
    j while
    jr  $ra
