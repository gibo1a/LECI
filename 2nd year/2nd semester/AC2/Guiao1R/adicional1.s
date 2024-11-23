    .data
    .equ UP,1
    .equ DOWN,0
    .equ putChar,3
    .equ printInt,6
    .equ inKey,1
    .text
    .globl main
main:
    addi $sp,$sp,-4
    sw  $ra,0($sp)
    li  $s0,0   #int state
    li  $s1,0   #int cnt
do:
    li  $a0,'\r'
    li  $v0,putChar
    syscall
    li  $v0,printInt
    move $a0,$s1
    li  $a1,3
    sll $a1,$a1,16
    ori $a1,$a1,10
    syscall
    li  $v0,putChar
    li  $a0,'\t'
    syscall
    li  $v0,printInt
    move $a0,$s1
    li  $a1,8
    sll $a1,$a1,16
    ori $a1,$a1,2
    syscall
    li  $a0,5
    jal wait
    li  $v0,inKey
    syscall
    move  $s2,$v0   # c
    beq $s2,'+',state_up
    beq $s2,'-',state_down
    beq $s2,'s',while
    beq $s2,'r',restart
    j end_if
state_up:
    li  $s0,UP
    j end_if
state_down:
    li  $s0,DOWN
restart:
    beq $s0,UP,restart_up
    li  $s1,255
    j end_if
restart_up:
    li  $s1,0
end_if:
    bne $s0,UP,else
    addi $s1,$s1,1
    andi $s1,$s1,0xFF
    j   while
else:
    addi $s1,$s1,-1
    andi $s1,$s1,0xFF
while:
    bne $s2,'q',do
    li  $v0,0
    lw  $ra,0($sp)
    addi    $sp,$sp,0
    jr  $ra


wait:
    li  $t0,0
    move    $t1,$a0
wait_for:
    li  $t2,515000
    mul $t2,$t2,$t1
    addi    $t0,$t0,1
    blt $t0,$t2,wait_for
    jr  $ra







