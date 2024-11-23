#include <detpic32.h>

int main(void){
    TRISBbits.TRISB4 = 1; // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0; // RBx configured as analog input
    AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
    // mode an internal counter ends sampling and
    // starts conversion
    AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
    // interrupt is generated. At the same time,
    // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 4-1; // Interrupt is generated after N samples
    // (replace N by the desired number of
    // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace x by the desired input
    // analog channel (0 to 15)
    AD1CON1bits.ON = 1; // Enable A/D converter
    // This must the last command of the A/D
    // configuration sequence
    TRISB = TRISB | 0x0002;
    TRISD = TRISD & 0xFF9F;
    TRISB = TRISB & 0x80FF;
    TRISEbits.TRISE4 = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    while(1){
        AD1CON1bits.ASAM = 1;
        LATEbits.LATE4 = !LATEbits.LATE4;
        while(IFS1bits.AD1IF == 0);
        IFS1bits.AD1IF = 0;
        int *p = (int*)(&ADC1BUF0);
        int media = 0;
        for(;p<=(int*)(&ADC1BUF3);p+=4){
            media += *p;
        }
        media = media /4;
        resetCoreTimer();
        while(readCoreTimer()<1666666);
        putChar('\r');
        printInt(media,2 | 10<<16);
        media = media / 128;
        putChar('\t');
        printInt(media,10 | 1<<16);
        int display = PORTBbits.RB1;
        if(display){
            LATDbits.LATD5 = 1;
            LATDbits.LATD6 = 0;
        }else{
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 1;
        }

    }
    return 0;
}
