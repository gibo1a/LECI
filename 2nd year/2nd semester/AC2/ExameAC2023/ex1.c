#include <detpic32.h>

int main(void){
    TRISE = TRISE & 0xFF03;
    TRISB = TRISB | 0x0005;
    unsigned int freq = 2739726;
    unsigned int value = 0x0030;
    while(1){
        if((PORTBbits.RB0 & PORTBbits.RB2)==0){
            freq = 4347826;
        }else{
            freq = 2739726;
        }
        while(value != 0x0003){
            LATE = ((LATE & 0xFF03)|value)<<2;
            resetCoreTimer();
            while(readCoreTimer()<freq);
            value = value >>1;
        }
        value = 0x0030;
    }
    return 0;
}
