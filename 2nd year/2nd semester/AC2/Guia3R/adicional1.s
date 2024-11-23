    .data
    .equ    TRISB,0xBF886040
    .equ    PORTB,0xBF886050
    .equ    TRISE,0xBF886100
    .equ    LATE,0xBF886120
    .equ    TRISD,0xBF8860C0
    .equ    LATD,0xBF8860E0
    .text
    .globl  main
main:
    #li  $t0,TRISB
    #lw  $t1,0($t0)
    #ori    $t1,$t1,0x000F
    #sw  $t1,0($t0)
    #li  $t0,TRISE
    #lw  $t1,0($t0)
    #andi    $t1,$t1,0xFFC3
    #sw  $t1,0($t0)
    li  $t0,TRISE
    lw  $t1,0($t0)
    andi    $t1,$t1,0xFFFE
    sw  $t1,0($t0)
    li  $t0,TRISD
    lw  $t1,0($t0)
    andi    $t1,$t1,0xFFFE
    sw  $t1,0($t0)
    li  $t0,0
while:
    li  $t1,LATE
    lw  $t2,0($t1)
    andi    $t2,$t2,0xFFFE
    or $t2,$t2,$t0
    sw  $t2,0($t1)
    li  $t1,LATD
    lw  $t2,0($t1)
    andi    $t2,$t2,0xFFFE
    or $t2,$t2,$t0
    sw  $t2,0($t1)
    li  $v0,12
    syscall
while_cnt:
    li  $v0,11
    syscall
    li  $t3,20000
    li  $t4,500
    mul $t3,$t3,$t4
    blt $v0,$t3,while_cnt
    li  $t3,1
    xor $t0,$t0,$t3
    j   while
    jr  $ra

    