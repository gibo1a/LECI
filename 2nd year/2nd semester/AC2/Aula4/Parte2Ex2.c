#include <detpic32.h>

void delay(int ms){
    resetCoreTimer();
    while (readCoreTimer()<20000*ms);
}

int main(void){
    unsigned char segment;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISB = TRISB & 0x80FF;
    while(1){
        segment = 1;
        for(int i = 0; i < 7; i++){
            LATB = (LATB & 0x80FF) | (segment<<8);
            delay(500);
            segment = segment << 1;
        }
        LATDbits.LATD5 = !LATDbits.LATD5;
        LATDbits.LATD6 = !LATDbits.LATD6;
    }
    return 0;
}
