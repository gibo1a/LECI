
#include <detpic32.h>

int main(void){
    TRISBbits.TRISB4 = 1;      
    AD1PCFGbits.PCFG4 = 0;            
    AD1CON2bits.SMPI = 0;       
    AD1CHSbits.CH0SA = 4;  
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16; 
    AD1CON1bits.ON = 1; 

    IPC6bits.AD1IP = 2;
    IFS1bits.AD1IF = 0;
    IEC1bits.AD1IE = 1;
    EnableInterrupts();

    AD1CON1bits.ASAM = 1;

    TRISD = TRISD & 0xF7FF;

    while (1){
        LATDbits.LATD11 = 0; 
    }
    return 0;
}

void _int_(27) isr_adc(void){
    volatile int adc_value;  
    adc_value = ADC1BUF0;  
    AD1CON1bits.ASAM = 1;     //750 nanosegundos
    LATDbits.LATD11 = 1;     //30 ciclos de relógio
    IFS1bits.AD1IF = 0;
}
