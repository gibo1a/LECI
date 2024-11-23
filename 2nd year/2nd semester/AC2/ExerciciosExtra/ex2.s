    .data
    .equ    ADDR_BASE_HI,0xBF88
    .equ    TRISE,0x6100
    .equ    PORTE,0x6110
    .equ    LATE,0x6120
    .equ    getChar,2
    .equ    putChar,3
    .equ    readCoreTimer,11
    .equ    resetCoreTimer,12
    .text
    .globl main
main:
    lui $s0,ADDR_BASE_HI
    lw  $s1,TRISE($s0)
    andi $s1,$s1,0xFFF0
    sw  $s1,TRISE($s0)
while:
    li $v0,putChar
    li $a0,'\r'
    syscall
    li $v0,getChar
    syscall
    beq $v0,'0',led_0
    beq $v0,'1',led_1
    beq $v0,'2',led_2
    beq $v0,'3',led_3
    j   led_all
led_0:
    lw  $s2,LATE($s0)
    andi    $s2,$s2,0xFFF0
    ori $s2,$s2,0x0001
    sw  $s2,LATE($s0)
    j   while
led_1:
    lw  $s2,LATE($s0)
    andi    $s2,$s2,0xFFF0
    ori $s2,$s2,0x0002
    sw  $s2,LATE($s0)
    j   while
led_2:
    lw  $s2,LATE($s0)
    andi    $s2,$s2,0xFFF0
    ori $s2,$s2,0x0004
    sw  $s2,LATE($s0)
    j   while
led_3:
    lw  $s2,LATE($s0)
    andi    $s2,$s2,0xFFF0
    ori $s2,$s2,0x0008
    sw  $s2,LATE($s0)
    j   while
led_all:
    lw  $s2,LATE($s0)
    andi    $s2,$s2,0xFFF0
    ori $s2,$s2,0x000F
    sw  $s2,LATE($s0)
    li $v0,resetCoreTimer
    syscall
while_timer:
    li  $v0,readCoreTimer
    syscall
    lui $s3,20000
    lui $s4,1000
    mul $s3,$s3,$s4
    blt $v0,$s3,while_timer
    lw  $s2,LATE($s0)
    andi    $s2,$s2,0xFFF0
    ori $s2,$s2,0x000F
    sw  $s2,LATE($s0)
    j   while
    jr  $ra
