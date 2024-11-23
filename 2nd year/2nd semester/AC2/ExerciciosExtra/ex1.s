    .data
    .equ    ADDR_BASE_HI,0xBF88
    .equ    TRISE,0x6100
    .equ    PORTE,0x6110
    .equ    LATE,0x6120
    .equ    TRISB,0x6040
    .equ    PORTB,0x6050
    .equ    LATB,0x6060
    .text
    .globl main
main:
    lui $t0,ADDR_BASE_HI
    lw  $t1,TRISB($t0)
    ori    $t1,$t1,0x000F
    sw  $t1,TRISB($t0)
    lw  $t2,TRISE($t0)
    andi $t2,$t2,0xFFF0
    sw  $t2,TRISE($t0)
while:
    lw  $t3,PORTB($t0)
    sw  $t3,LATE($t0)
    j   while
    jr  $ra
    