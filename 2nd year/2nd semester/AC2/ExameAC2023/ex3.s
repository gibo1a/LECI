    .data
    .equ TRISE,0xBF886100
    .equ LATE,0xBF886120
    .equ printInt,6
    .equ resetCoreTimer,12
    .equ readCoreTimer,11
    .equ putChar,3
    .text
    .globl main
main:
    li  $s1,TRISE
    lw  $s0,0($s1)
    andi $s0,$s0,0xFF83
    sw  $s0,0($s1)
    li  $s2,0
    li  $s3,25
    li  $s5,20000
    li  $s6,1000
    li  $s7,24
    mul $s5,$s5,$s6
while:
    li  $v0,resetCoreTimer
    syscall
timer:
    li  $v0,readCoreTimer
    syscall
    blt $v0,$s5,timer
    addiu    $s2,$s2,-24
    #addi    $s2,$s2,1
    remu $s2,$s2,$s3
    li  $a0,'\r'
    li  $v0,putChar
    syscall
    li  $v0,printInt
    move    $a0,$s2
    li  $s4,5
    sll $s4,$s4,16
    ori $s4,$s4,10
    move    $a1,$s4
    syscall
    li  $s1,LATE
    lw  $s0,0($s1)
    andi    $s0,$s0,0xFF83
    sll $s7,$s2,2
    or $s0,$s0,$s2
    sw  $s0,0($s1)
    j   while

