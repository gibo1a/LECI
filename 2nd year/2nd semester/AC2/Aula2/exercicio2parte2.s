    .equ RESET_CORE_TIMER,12
    .equ READ_CORE_TIMER,11
    .equ PUT_CHAR,3
    .equ PRINT_INT,6
    .data
    .text
    .globl main
main:
    addi    $sp,$sp,-4
    sw  $ra,0($sp)
    li  $s0,0
    li  $s1,0
    li  $s2,0
while:
    li  $v0,RESET_CORE_TIMER
    syscall
    li  $a0,100
    jal delay
    addi    $s0,$s0,1
    rem $s3,$s0,2
    bne $s3,0,end_if
if: 
    addi    $s1,$s1,1
end_if:   
    rem $s3,$s0,10
    bne $s3,0,end_if1 
if1:    
    addi    $s2,$s2,1
end_if1:
    li  $v0,PUT_CHAR
    li  $a0,'\r'
    syscall
    li  $v0,PRINT_INT
    move  $a0,$s0
    li  $a1,5
    sll $a1,$a1,16
    ori $a1,$a1,10
    syscall
    li $v0,PUT_CHAR
    li  $a0,'\t'
    syscall
    li  $v0,PRINT_INT
    move  $a0,$s1
    li  $a1,5
    sll $a1,$a1,16
    ori $a1,$a1,10
    syscall
    li $v0,PUT_CHAR
    li  $a0,'\t'
    syscall
    li  $v0,PRINT_INT
    move  $a0,$s2
    li  $a1,5
    sll $a1,$a1,16
    ori $a1,$a1,10
    syscall
    j while
    lw  $ra,0($sp)
    li  $v0,0
    addi    $sp,$sp,4
    jr $ra


delay:
    move    $t0,$a0
    li  $v0,RESET_CORE_TIMER
    syscall
    li  $t1,0
    li  $t2,20000
    mul $t2,$t2,$t0
delay_while:
    bge $t1,$t2,end_delay_while
    li  $v0,READ_CORE_TIMER
    syscall
    move $t1,$v0
    j delay_while
end_delay_while:
    jr  $ra