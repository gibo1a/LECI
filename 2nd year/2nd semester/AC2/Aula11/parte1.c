#include <detpic32.h>

void putc(char byte){
// wait while UART2 UTXBF == 1
// Copy "byte" to the U2TXREG register
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
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
    U2BRG = 10;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    IPC8bits.U2IP = 3;
    IFS1bits.U2RXIF = 0;
    U2STAbits.URXISEL = 0;

    TRISCbits.TRISC14 = 0;
                                        // Configure UART2: 115200, N, 8, 1
                                        // Configure UART2 interrupts, with RX interrupts enabledand TX interrupts disabled:enable U2RXIE, disable U2TXIE (register IEC1)
                                                                    //set UART2 priority level (register IPC8)
                                                                    //clear Interrupt Flag bit U2RXIF (register IFS1)
                                                                    //define RX interrupt mode (URXISEL bits)
                                                                    // Enable global Interrupts
    EnableInterrupts();
    while(1);
    return 0;
}

void _int_(32) isr_uart2(void){
    if (IFS1bits.U2RXIF == 1){
        char c = getc();
        if(c == '?'){putstr("AC2-Guiao 11");}
        if(c == 'T'){LATCbits.LATC14 = 1;}
        if(c == 't'){LATCbits.LATC14 = 0;}
        putc(c);
        IFS1bits.U2RXIF == 0;
        // Read character from FIFO (U2RXREG)
        // Send the character using putc()
        // Clear UART2 Rx interrupt flag
    }
}
