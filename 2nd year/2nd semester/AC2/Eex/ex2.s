    .data
    .equ    getChar,2
    .equ    resetCoreTimer,12
    .equ    readCoreTimer,11
    .equ    TRISE,0xBF886100
    .equ    LATE,0xBF886120
    .text
    .globl main
main:
    li  $s1,TRISE
    lw  $s0,0($s1)
    andi    $s0,$s0,0xFFF0
    sw  $s0,0($s1)
while:
    li  $s1,LATE
    li  $v0,getChar
    syscall
    beq $v0,'0',en_0
    beq $v0,'1',en_1
    beq $v0,'2',en_2
    beq $v0,'3',en_3
    lw  $s0,0($s1)
    andi    $s0,$s0,0xFFF0
    ori $s0,$s0,0x000F
    sw  $s0,0($s1)
    li  $s2,20000
    li  $s3,1000
    mul $s2,$s3,$s2
    li  $v0,resetCoreTimer
    syscall
timer:
    li  $v0,readCoreTimer
    syscall
    blt $v0,$s2,timer
    lw  $s0,0($s1)
    andi    $s0,$s0,0xFFF0
    ori $s0,$s0,0x0000
    sw  $s0,0($s1)
    j   while
en_0:
    lw  $s0,0($s1)
    andi    $s0,$s0,0xFFF0
    ori $s0,$s0,0x0001
    sw  $s0,0($s1)
    j   while
en_1:
    lw  $s0,0($s1)
    andi    $s0,$s0,0xFFF0
    ori $s0,$s0,0x0002
    sw  $s0,0($s1)
    j   while
en_2:
    lw  $s0,0($s1)
    andi    $s0,$s0,0xFFF0
    ori $s0,$s0,0x0004
    sw  $s0,0($s1)
    j   while
en_3:
    lw  $s0,0($s1)
    andi    $s0,$s0,0xFFF0
    ori $s0,$s0,0x0008
    sw  $s0,0($s1)
    j   while
    jr  $ra
    