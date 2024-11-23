    .equ    RESET_CORE_TIMER,12
    .equ    READ_CORE_TIMER,11
    .data
    .text
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

