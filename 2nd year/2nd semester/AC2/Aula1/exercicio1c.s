# int value : $s0
    .data
str1: .asciiz "\nIntroduza um inteiro (sinal e modulo): "
str2: .asciiz "\nValor em base 10 (signed): "
str3: .asciiz "\nValor em base 2: "
str4: .asciiz "\nValor em base 16: "
str5: .asciiz "\nValor em base 10 (unsigned): "
str6: .asciiz "\nValor em base 10 (unsigned), formatado: "
    .text
    .globl main
main:
while:
    li $v0,8
    la $a0,str1
    syscall
    li $v0,5
    syscall
    move $s0,$v0
    li $v0,8
    la $a0,str2
    syscall
    li $v0,7
    move $a0,$s0
    syscall
    li $v0,8
    la $a0,str3
    syscall
    li $v0,6
    move $a0,$s0
    li $a1,2
    syscall
    li $v0,8
    la $a0,str4
    syscall
    li $v0,6
    move $a0,$s0
    li $a1,16
    syscall
    li $v0,8
    la $a0,str5
    syscall
    li $v0,6
    move $a0,$s0
    li $a1,10
    syscall
    li $v0,8
    la $a0,str6
    syscall
    li $s1,5
    sll $s1,$s1,16
    ori $s1,$s1,10
    li $v0,6
    move $a0,$s0
    move $a1,$s1
    syscall
    j while
    li $v0,0
