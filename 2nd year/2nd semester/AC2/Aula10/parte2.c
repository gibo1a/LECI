#include <detpic32.h>

void putc(char byte){
// wait while UART2 UTXBF == 1
// Copy "byte" to the U2TXREG register
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

void putc1(char byte){
// wait while UART2 UTXBF == 1
// Copy "byte" to the U2TXREG register
    while(U1STAbits.UTXBF == 1);
    U1TXREG = byte;
}

void putstr(char *str){
// use putc() function to send each charater ('\0' should notbe sent)
    char *c = str;
    while(*c != '\0'){
        putc(*c);
        c++;
    }
}

char getc(void){
// If OERR == 1 then reset OERR
// Wait while URXDA == 0
// Return U2RXREG
    if(U2STAbits.OERR == 1){U2STAbits.OERR = 0;}
    while(U2STAbits.URXDA == 0);
    return U2RXREG;
}

int main(void){
    U1BRG = 10;
    U1MODEbits.BRGH = 0;
    U1MODEbits.PDSEL = 0;
    U1MODEbits.STSEL = 0;
    U1STAbits.UTXEN = 1;
    U1MODEbits.ON = 1;

    U2BRG = 10;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2MODEbits.ON = 1;
    while (1){
        char c = 0x5A;
        putc1(c);
        resetCoreTimer();
        while (readCoreTimer()<200000);
    }
    return 0;
}
