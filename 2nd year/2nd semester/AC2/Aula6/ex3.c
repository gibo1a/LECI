#include <detpic32.h>

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
    volatile int aux;
    unsigned int media = 0;
    while(1){
        AD1CON1bits.ASAM = 1;
        LATDbits.LATD11 = 1;
        while(IFS1bits.AD1IF==0);
        LATDbits.LATD11 = 0;
        putChar('\r');
        aux = ADC1BUF0;
        IFS1bits.AD1IF = 0;
        int *p = (int *)(&ADC1BUF0);
        for(; p <= (int *)(&ADC1BUFF); p+=4 ) {
            printInt(*p, 16 | 4 << 16 );
            putChar(' ');
            media += *p;
        }
        media /= 4; 
        unsigned int tensao = (((media * 33)+511)/1023);
    }
    return 0;
}

