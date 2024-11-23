#include <detpic32.h>

int main(void){
    T3CONbits.TCKPS = 0; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
    PR3 = 19999; // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0; // Reset timer T2 count register
    T3CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)
    OC3CONbits.OCM = 6; // PWM mode on OCx; fault pin disabled
    OC3CONbits.OCTSEL =1;// Use timer T2 as the time base for PWM generation
    OC3RS = 12500; // Ton constant
    OC3CONbits.ON = 1; // Enable OC1 module

    TRISBbits.TRISB4 = 1; // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0; // RBx configured as analog input
    AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
    // mode an internal counter ends sampling and
    // starts conversion
    AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
    // interrupt is generated. At the same time,
    // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 1-1; // Interrupt is generated after N samples
    // (replace N by the desired number of
    // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace x by the desired input
    // analog channel (0 to 15)
    AD1CON1bits.ON = 1; // Enable A/D converter
    // This must the last command of the A/D
    // configuration sequence
    OC5CONbits.OCM = 6; // PWM mode on OCx; fault pin disabled
    OC5CONbits.OCTSEL =1;// Use timer T2 as the time base for PWM generation
    OC5RS = 12500; // Ton constant
    OC5CONbits.ON = 1; // Enable OC1 module
    int media = 0;

    while(1){
        media = 0;
        AD1CON1bits.ASAM = 1; 
        while( IFS1bits.AD1IF == 0 );
        int *p = (int*)(&ADC1BUF0);
        for(;p <= (int*)(&ADC1BUFF);p+=4){
            media += *p;
        }
        media = media / 10;
        OC3RS = ((PR3+1)*media)/100;
        OC5RS = (100-(((PR3+1)*media)/100));
        resetCoreTimer();
        while(readCoreTimer()<2000000);
        IFS1bits.AD1IF = 0;
    }
    return 0;
}
