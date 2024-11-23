#include <detpic32.h>

int main(void){
    T3CONbits.TCKPS = 5; 
    PR3= 49999;        
    TMR3 = 0;           
    T3CONbits.TON = 1;

    T1CONbits.TCKPS = 3; 
    PR1= 62499;        
    TMR1 = 0;           
    T1CONbits.TON = 1;

    IPC1bits.T1IP = 3; 
    IEC0bits.T1IE = 1; 
    IFS0bits.T1IF = 0;

    IPC3bits.T3IP = 2; 
    IEC0bits.T3IE = 1; 
    IFS0bits.T3IF = 0;

    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD2 = 0;
    LATDbits.LATD0 = 0;
    LATDbits.LATD2 = 0;

    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE3 = 0;

    EnableInterrupts();

    while(1);
    return 0;
}

void _int_(4) isr_T1(void){
    putChar('1');
    IFS0bits.T1IF = 0;
    LATDbits.LATD0 = !LATDbits.LATD0;       //T = 1.59 s
    LATEbits.LATE1 = !LATEbits.LATE1;
}

void _int_(12) isr_T3(void){
    putChar('3');
    IFS0bits.T3IF = 0;
    LATDbits.LATD2 = !LATDbits.LATD2;   //T = 159.9 ms
    LATEbits.LATE3 = !LATEbits.LATE3;
}
