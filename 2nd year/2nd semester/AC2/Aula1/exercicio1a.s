# int cnt : $s0
# char c : $s1
    .data
    .text
    .globl main
main:
    li $s0,0
do:
    li $v0,2
    syscall
    move $s1,$v0
    li $v0,3
    move $a0,$s1
    syscall
    addi $s0,$s0,1
while:
    bne $s1,'\n',do
    li $v0,6
    move $a0,$s0
    li $a1,10
    syscall
    li $v0,0
