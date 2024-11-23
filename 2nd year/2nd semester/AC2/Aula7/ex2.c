#include <detpic32.h>

volatile unsigned char voltage = 0;

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
    AD1CON2bits.SMPI = 7;       
    AD1CHSbits.CH0SA = 4;  
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16; 
    AD1CON1bits.ON = 1; 

    IPC6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;
    EnableInterrupts();

    TRISD &= 0xFF9F;
    TRISB &= 0x80FF;

    unsigned int cnt = 0;

    while (1){
        if(cnt == 0){
            AD1CON1bits.ASAM = 1;
        }
        send2displays(toBcd(voltage));
        cnt = (cnt + 1)%20;
        resetCoreTimer();
        while(readCoreTimer() < 200000);
    }
    return 0;
}

void _int_(27) isr_adc(void){
    int *p = (int *)(&ADC1BUF0),VAL_AD=0;
    for(; p <= (int *)(&ADC1BUFF); p+=4 ) {
        VAL_AD += *p;
    }
    VAL_AD =VAL_AD / 8;
    voltage = (((VAL_AD * 33)+511)/1023);
    IFS1bits.AD1IF = 0;
}
