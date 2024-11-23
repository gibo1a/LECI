#include <detpic32.h>

void putc(char byte){
// wait while UART2 UTXBF == 1
// Copy "byte" to the U2TXREG register
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

int main(void){
    U2BRG = 1040;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2MODEbits.ON = 1;

    TRISB = TRISB | 0x000F;

    while(1){
        char string[] = "RB30=";
        char *c = string;
        putc('\r');
        while (*c != '\0'){
            putc(*c);
            c++;
        }
        PORTBbits.RB3?putc('1'):putc('0');
        PORTBbits.RB2?putc('1'):putc('0');
        PORTBbits.RB1?putc('1'):putc('0');
        PORTBbits.RB0?putc('1'):putc('0');
    }
    return 0;
}
