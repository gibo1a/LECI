#include <detpic32.h>

int main(void){
    // Configure UART2 (115200, N, 8, 1)
    // config RD11 as output
    U2BRG = 10;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2MODEbits.ON = 1;

    TRIDbits.TRISD11 = 0;
    while(1){
        // Wait while TRMT == 0
        while(U2STAbits.TRMT == 0);
        LATDbits.LATD11 = 1;
        // Set RD11
        putstr("12345");
        // Reset RD11
        LATDbits.LATD11 = 0;
    }
    return 0;
}