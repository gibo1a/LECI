    .data
    .equ    SIZE,20
    .equ    printStr,8
    .equ    readStr,9
    .equ    printInt,6
    .equ    printInt10,7
str1:   .space 21
str2:   .space 21
str3:   .space 41
str4:   .asciiz "Introduza 2 strings: "
str5:   .asciiz "Resultados:\n"
    .text
    .globl main
main:
    addi    $sp,$sp,-4
    sw  $ra,0($sp)
    li  $v0,printStr
    la  $a0,str4
    syscall
    li  $v0,readStr
    la  $a0,str1
    li  $a1,SIZE
    syscall
    li  $v0,readStr
    la  $a0,str2
    li  $a1,SIZE
    syscall
    li  $v0,printStr
    la  $a0,str5
    syscall
    la  $a0,str1
    jal strlen
    move    $a0,$v0
    li  $v0,printInt
    li  $a1,10
    syscall
    la  $a0,str2
    jal strlen
    move    $a0,$v0
    li  $v0,printInt
    li  $a1,10
    syscall
    la  $a0,str3
    la  $a1,str1
    jal strcpy
    la  $a0,str3
    la  $a1,str2
    jal strcat
    move    $a0,$v0
    li  $v0,printStr
    syscall
    la  $a0,str1
    la  $a1,str2
    jal strcmp
    move    $a0,$v0
    li  $v0,printInt10
    syscall
    li  $v0,0
    lw  $ra,0($sp)
    addi    $sp,$sp,4
    jr  $ra


strlen:
    move $t0,$a0
    li  $t1,0
strlen_for:
    addi    $t1,$t1,1
    addiu    $t0,$t0,1
    lb  $t2,0($t0)
    bne $t2,0,strlen_for
    move $v0,$t1
    jr  $ra

strcpy:
    move    $t0,$a0
    move    $t1,$a1
strcpy_for:
    lb  $t2,0($t1)
    sb  $t2,0($t0)
    addiu   $t0,$t0,1
    addiu   $t1,$t1,1
    bne $t2,0,strcpy_for
    move    $v0,$a0
    jr  $ra

strcat:
    addi    $sp,$sp,-12
    sw  $s0,0($sp)
    sw  $s1,-4($sp)
    sw  $ra,-8($sp)
    move    $s0,$a0
    move    $s1,$a1
strcat_for:
    lb  $s2,0($s0)
    addiu   $s0,$s0,1
    bne $s2,0,strcat_for
    move    $a0,$s0
    move    $a1,$s1
    jal strcpy
    lw  $s0,0($sp)
    lw  $s1,-4($sp)
    lw  $ra,-8($sp)
    addi    $sp,$sp,12
    jr  $ra

strcmp:
    move    $t0,$a0
    move    $t1,$a1
strcmp_for:
    lb  $t2,0($t0)
    lb  $t3,0($t1)
    addiu   $t0,$t0,1
    addiu   $t1,$t1,1
    bne $t3,$t2,end_for
    bne $t2,0,strcmp_for
end_for:
    sub $v0,$t2,$t3
    jr  $ra

    

