    .data
    .equ    TRISB,0xBF886040
    .equ    PORTB,0xBF886050
    .equ    TRISE,0xBF886100
    .equ    LATE,0xBF886120         #ver
    .text
    .globl main
main:
    li  $s1,TRISB
    lw  $s0,0($s1)
    ori $s0,$s0,0x000F
    sw  $s0,0($s1)
    li  $s1,TRISE
    lw  $s0,0($s1)
    andi    $s0,$s0,0xFFF0
    sw  $s0,0($s1)
while:
    li  $s1,PORTB
    lw  $s0,0($s1)
    andi    $s0,$s0,0x000F
    li  $s1,LATE
    sw  $s0,0($s1)
    j   while
    jr  $ra
