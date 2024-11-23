# int counter : $s0
    .equ READ_CORE_TIMER,11
    .equ RESET_CORE_TIMER,12
    .equ PUT_CHAR,3
    .equ PRINT_INT,6
    .data
    .text
    .globl main
main: 
    li $s0,0
    addi $sp,$sp,-4
    sw $ra,0($sp)
while:
    li  $v0,PUT_CHAR
    li  $a0,'\r'
    syscall
    li  $s1,4
    sll $s1,$s1,16
    ori $s1,$s1,10
    li  $v0,PRINT_INT
    move  $a0,$s0
    move  $a1,$s1
    syscall
    li  $a0,1
    jal delay
    addi $s0,$s0,1
    j   while
    li  $v0,0
    lw    $ra,0($sp)
    addi $sp,$sp,4
    jr $ra

delay:
    move    $t0,$a0
    li  $v0,RESET_CORE_TIMER
    syscall
    li  $t1,0
    li  $t2,2000000
    mul $t2,$t2,$t0
delay_while:
    bge $t1,$t2,end_delay_while
    li  $v0,READ_CORE_TIMER
    syscall
    move $t1,$v0
    j delay_while
end_delay_while:
    jr  $ra
