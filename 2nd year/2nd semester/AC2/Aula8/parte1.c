#include    <detpic32.h>

int main(void){
    T3CONbits.TCKPS = 7; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR3= 39062;        // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0;           // Clear timer T2 count register
    T3CONbits.TON = 1;                    // Configure Timer T3 (2 Hz with interrupts disabled)
    /*IPC3bits.T3IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T3IE = 1; // Enable timer T2 interrupts
    IFS0bits.T3IF = 0;*/
    while(1){
        while(IFS0bits.T3IF == 0);                 // Wait while T3IF = 0
        IFS0bits.T3IF = 0;                         // Reset T3IF
        putChar('.');
    }
    return 0;
}
