#include <detpic32.h>

int main(void){
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CHSbits.CH0SA = 4;
    AD1CON2bits.SMPI = 0;
    AD1CON1bits.ON = 1;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    TRISB |= 0x000F;
    int bit3,bit2,bit1,bit0;
    while(1){
       AD1CON1bits.ASAM = 1;
        while( IFS1bits.AD1IF == 0 );
        printInt(ADC1BUF0,10);
        putChar('\t');
        unsigned int rate = ADC1BUF0>>8;
        IFS1bits.AD1IF = 0;
        resetCoreTimer();
        while(readCoreTimer() < 20000000);
        bit3 = PORTBbits.RB3;
        bit2 = PORTBbits.RB2;
        bit1 = PORTBbits.RB1;
        bit0 = PORTBbits.RB0;
        putChar('\r');
        if(bit3){
            putChar('1');
        }else{
            putChar('0');
        }
        if(bit2){
            putChar('1');
        }else{
            putChar('0');
        }
        if(bit1){
            putChar('1');
        }else{
            putChar('0');
        }
        if(bit0){
            putChar('1');
        }else{
            putChar('0');
        }
    } 
    return 0;
}
