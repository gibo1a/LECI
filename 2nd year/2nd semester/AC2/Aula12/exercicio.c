#include <detpic32.h>

volatile int gama = 1;
volatile int pwn = 0;

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

void dutycycle(int percentage){
    OC5RS = ((PR3 + 1)*percentage)/100;
}

int main(void){
    U2BRG = 5;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 2;
    U2MODEbits.STSEL = 1;
    U2MODEbits.ON = 1;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2STAbits.URXISEL = 0;
    U2STAbits.UTXISEL = 0;
    IFS1bits.U2RXIF = 0;
    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    IEC1bits.U2EIE = 0;
    IPC8bits.U2IP = 2;


    TRISBbits.TRISB4 = 1; 
    AD1PCFGbits.PCFG4= 0;
    AD1CON1bits.SSRC = 7; 
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16; 
    AD1CON2bits.SMPI = 2-1;
    AD1CHSbits.CH0SA = 4; 
    AD1CON1bits.ON = 1; 
    IPC6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;

    T1CONbits.TCKPS = 2; 
    PR1 = 12499; 
    TMR1 = 0;
    T1CONbits.TON = 1;
    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0; 

    T3CONbits.TCKPS = 0; 
    PR3 = 2856; 
    TMR3 = 0;
    T3CONbits.TON = 1;
    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0; 

    OC5CONbits.OCM = 6;
    OC5CONbits.OCTSEL = 1;
    dutycycle(70);
    OC5CONbits.ON = 1;

    TRISD &= 0xFF9F;
    TRISB &= 0x80FF;

    TRISBbits.TRISB0 = 1;

    EnableInterrupts();
    while(1);
    return 0;
}

void _int_(32) uart2_isr(void){
    if(U2RXREG == 1){gama = 1;}
    if(U2RXREG == 2){gama = 2;}
    if(U2RXREG == 3){gama = 3;}
    IFS1bits.U2RXIF = 0;
}

void _int_(27) adc1_isr(void){
    int *p = (int*)ADC1BUF0;
    int media = 0;
    pwn = 0;
    for(;p<(int*)ADC1BUFF;p+=4){
        media += *p;
    } 
    media = media/2;
    if(gama == 1){
        pwn = media / 26;
        dutycycle(pwn);
    }
    if(gama == 2){
        pwn = media / 34;
        pwn = pwn + 40;
        dutycycle(pwn);
    }
    if(gama == 3){
        pwn = media / 35;
        pwn = pwn + 70;
        dutycycle(pwn);
    }
    IFS1bits.AD1IF = 0;
}

void _int_(4) t1_isr(void){
    AD1CON1bits.ASAM = 1;
    IFS0bits.T1IF = 0;
}

void _int_(12) t3_isr(void){
    if(PORTBbits.RB0 == 1){
        send2displays(toBcd(pwn));
        resetCoreTimer();
        while (readCoreTimer() < 300300);
    }
    IFS0bits.T3IF = 0;
}
