# int counter : $t0
    
    .equ READ_CORE_TIMER,11
    .equ RESET_CORE_TIMER,12
    .equ PUT_CHAR,3
    .equ PRINT_INT,6
    .data
    .text
    .globl main
main: 
    li $t0,0
while:
    li  $v0,PUT_CHAR
    li  $a0,'\r'
    syscall
    li  $t1,4
    sll $t1,$t1,16
    ori $t1,$t1,10
    li  $v0,PRINT_INT
    move  $a0,$t0
    move  $a1,$t1
    syscall
    li  $v0,RESET_CORE_TIMER
    syscall
    li $t2,0
while_1:
    bge $t2,2000000,end_while_1
    li  $v0,READ_CORE_TIMER
    syscall
    move $t2,$v0
    j   while_1
end_while_1:
    addi $t0,$t0,1
    j   while
    li  $v0,0
    jr $ra
