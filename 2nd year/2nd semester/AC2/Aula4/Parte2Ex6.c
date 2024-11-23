#include <detpic32.h>

int main(void){
    TRIB = TRISB | 0x000F;
    TRISB = TRISB & 0x80FF;
    TRISD = TRISD & 0xFF9F;
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;
    static const char disp7Scodes[] = {0x3F, 0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x39,0x5E,0x79,0x71};
    while (1){
        int hexdigit = PORTB & 0x000F;
        LATB = (LATB & 0x80FF) | (disp7Scodes[hexdigit]<<8);
    }
    
    return 0;
}