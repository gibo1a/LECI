    .data
    .equ    ADDR_BASE_HI,0xBF88
    .equ    TRISE,0x6100
    .equ    PORTE,0x6110
    .equ    LATE,0x6120
    .equ    TRISB,0x6040
    .equ    PORTB,0x6050
    .equ    LATB,0x6060
    .equ RESET_CORE_TIMER,12
    .equ READ_CORE_TIMER,11
    .text
    .globl main
main:
    addi    $sp,$sp,-4
    sw  $ra,0($sp)
    lui  $s0,ADDR_BASE_HI
    lw  $s1,TRISE($s0)
    andi    $s1,$s1,0xFFE1
    sw  $s1,TRISE($s0)
    lw  $s1,TRISB($s0)
    ori $s1,$s1,0x000E
    sw  $s1,TRISB($s0)
    li  $s2,0
while:
    lw  $s1,LATE($s0)
    andi    $s1,$s1,0xFFE1
    sll $s3,$s2,1
    or  $s1,$s1,$s3
    sw  $s1,LATE($s0)
    li  $a0,1000
    jal delay
    addi    $s2,$s2,1
    andi    $s2,$s2,0x000F
    j   while
    lw  $ra,0($sp)
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