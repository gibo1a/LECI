#include <detpic32.h>

volatile int voltage;
volatile int voltMin;
volatile int voltMax;

void putc(char byte){
// wait while UART2 UTXBF == 1
// Copy "byte" to the U2TXREG register
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}

void putstr(char *str){
// use putc() function to send each charater ('\0' should notbe sent)
    char *c = str;
    while(*c != '\0'){
        putc(*c);
        c++;
    }
}

char getc(void){
// If OERR == 1 then reset OERR
// Wait while URXDA == 0
// Return U2RXREG
    if(U2STAbits.OERR == 1){U2STAbits.OERR = 0;}
    while(U2STAbits.URXDA == 0);
    return U2RXREG;
}

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

    U2BRG = 10;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    IPC8bits.U2IP = 3;
    IFS1bits.U2RXIF = 0;
    U2STAbits.URXISEL = 0;

    voltMin = 0;
    voltMax = 0;

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
        if(*p < voltMin){voltMin = *p;}
        if(*p > voltMax){voltMax = *p;}
    }
    media /= 8; 
    voltage = ((media * 33+511)/1023);
    IFS1bits.AD1IF=0;
}

void _int_(32) isr_uart2(void){
    if (IFS1bits.U2RXIF == 1){
        char c = getc();
        if(c == 'M'){
            putstr("VMax=");
            putc((char*)(toBcd(voltMax)&0xF0));
            putc((char*)(toBcd(voltMax)&0x0F));
            putc("V");
        }
        if(c == 'm'){
            putstr("VMin=");
            putc((char*)(toBcd(voltMin)& 0xF0));
            putc((char*)(toBcd(voltMin)& 0x0F));
            putc("V");
        }
        IFS1bits.U2RXIF == 0;
    }
}

