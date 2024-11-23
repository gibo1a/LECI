    .data
    .equ    RESET_CORE_TIMER,12
    .equ    READ_CORE_TIMER,11
    .text
    .globl main
main:
    addi    $sp,$sp,-4
    sw  $ra,0($sp)
#CONTADOR CRESCENTE DE 1HZ 
    li  $s0,0
contador_1hz:
    beq $s0,0x000F,end_contador_1hz
    li  $a0,1000
    jal delay
    addi    $s0,$s0,1
    j contador_1hz
end_contador_1hz:
    lw $ra,0($sp)
    jr $ra
    
#CONTADOR DECRESCENTE DE 4HZ
    li  $s0,0xFFFF
contador_4hz:
    beq $s0,$0,end_contador_4hz
    li,$v0,RESET_CORE_TIMER
    syscall
while_contador_4hz:
    li  $v0,READ_CORE_TIMER
    syscall
    beq $v0,250,end_while_contador_4hz
    j   while_contador_4hz
end_while_contador_4hz:
    addi $s0,$s0,-1
    j contador_4hz
end_contador_4hz:
    jr  $ra





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
