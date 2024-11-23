#include <detpic32.h>

volatile int voltage;

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

    IPC6bits.AD1IP = 4; 
    IEC1bits.AD1IE = 1; 

    TRISB &= 0x80FF;
    TRISBbits.TRISB0 = 1;
    TRISD |= 0xBFFF;
    TRISD &= 0xFF9F;

    T3CONbits.TCKPS = 2; 
    PR3= 49999;        
    TMR3 = 0;           
    T3CONbits.TON = 1;

    IPC3bits.T3IP = 3; 
    IEC0bits.T3IE = 1; 

    T1CONbits.TCKPS = 2; 
    PR1= 62499;        
    TMR1 = 0;           
    T1CONbits.TON = 1;

    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;

    IFS0bits.T1IF = 0;
    IFS0bits.T3IF = 0;
    IFS1bits.AD1IF = 0;

    EnableInterrupts();
    while(1);
    return 0;
}

void _int_(4) isr_t1(void){
    AD1CON1bits.ASAM = 1;
    IFS0bits.T1IF = 0;
}

void _int_(12) isr_t3(void){
    int voltage_dec = toBcd(voltage);
    send2displays(voltage_dec);
    IFS0bits.T3IF = 0;
}

void _int_(27) isr_adc(void){
    int media = 0;
    int *p = (int *)(&ADC1BUF0);
    putChar('\r');
    for(; p <= (int *)(&ADC1BUFF); p+=4 ) {
        printInt(*p, 16 | 4 << 16 );
        media += *p;
    }
    media /= 8; 
    voltage = ((media * 33+511)/1023);
    IFS1bits.AD1IF=0;
}
