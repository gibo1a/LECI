#include <detpic32.h>

void send2displays(unsigned char value){
    static const char disp7Scodes[] = {0x3F, 0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x39,0x5E,0x79,0x71};
    static char displayFlag = 0;
    unsigned int dh = value >> 4;
    unsigned int dl = value & 0x0F;
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 0;
    if(displayFlag == 0){
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | (disp7Scodes[dh]<<8);
    }else{
        LATDbits.LATD5 = 1;
        LATB = (LATB & 0x80FF) | (disp7Scodes[dl]<<8);
    }
    displayFlag = !displayFlag;
}

unsigned char toBcd(unsigned char value){
    return ((value / 10) << 4) + (value % 10);
}

int main(void){
    TRISBbits.TRISB4 = 1;      
    AD1PCFGbits.PCFG4 = 0;            
    AD1CON2bits.SMPI = 3;       
    AD1CHSbits.CH0SA = 4;  
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16; 
    AD1CON1bits.ON = 1; 

    TRISDbits.TRISD11 = 0;

    TRISB &= 0x80FF;
    TRISBbits.TRISB0 = 1;
    TRISD |= 0xBFFF;
    TRISD &= 0xFF9F;

    unsigned int counter = 0;
    volatile int aux;
    int media = 0;
    while(1){
        AD1CON1bits.ASAM = 1;
        LATDbits.LATD11 = 1;
        while(IFS1bits.AD1IF==0);
        LATDbits.LATD11 = 0;
        putChar('\r');
        printInt(ADC1BUF0, 16 | 3 << 16);
        aux = ADC1BUF0;
        IFS1bits.AD1IF = 0;
        int *p = (int *)(&ADC1BUF0);
        for(; p <= (int *)(&ADC1BUFF); p+=4 ) {
            printInt(*p, 16 | 4 << 16 );
            media += *p;
        }
        media /= 4; 
        int tensao = (((media * 33)+511)/1023);
        tensao = toBcd(tensao);
        send2displays(tensao);
        resetCoreTimer();
        while(readCoreTimer() < 2000000);
    }

    return 0;
}
