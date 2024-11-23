#include <detpic32.h>

int main(void){
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB2 = 1;

    T3CONbits.TCKPS = 2; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
    PR3 = 41666; // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0; // Reset timer T2 count register
    T3CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)
    OC2CONbits.OCM = 6; // PWM mode on OCx; fault pin disabled
    OC2CONbits.OCTSEL = 1;// Use timer T2 as the time base for PWM generation
    OC2RS = 31250; // Ton constant
    OC2CONbits.ON = 1; // Enable OC1 module

    while(1){
        if((PORTBbits.RB0 & PORTBbits.RB2)==1){
            OC2RS = 12500;
        }else if((PORTBbits.RB0 & PORTBbits.RB2)==0){
            OC2RS = 20833;
        }else{
            OC2RS = OC2RS;
        }
        resetCoreTimer();
        while(readCoreTimer()< 7199);
    }
    return 0;
}
