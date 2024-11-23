#include <detpic32.h>

volatile int cnt = 16;

int main(void){
    U2BRG = 129;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 3;
    U2MODEbits.STSEL = 1;
    U2STAbits.URXEN = 1;
    U2STAbits.UTXEN = 1;
    U2MODEbits.ON = 1;

    U2STAbits.UTXISEL = 0;
    U2STAbits.URXISEL = 0;

    IFS1bits.U2RXIF = 0;
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    IPC8bits.U2IP = 2;

    TRISE = TRISE & 0xFFF0;

    EnableInterrupts();

    while(1);
    return 0;
}

void _int_(32) u2_isr(void){
    if(U2STAbits.OERR == 1){U2STAbits.OERR == 0;}
    char c = U2RXREG;
    if(c == 'U'){
        cnt = (cnt+1)%16;
        LATE = LATE & 0xFFF0;
        LATE = (LATE | cnt);
    }else if(c == 'R'){
        cnt = 0;
        LATE = LATE & 0xFFF0;
        LATE = (LATE | cnt);
        char string[] = "RESET";
        while(U2STAbits.UTXBF == 1);
        char *str = string;
        while (*str != '\0'){
            U2TXREG = *str;
            str++;
        }  
    }
    IFS1bits.U2RXIF = 0;
}
