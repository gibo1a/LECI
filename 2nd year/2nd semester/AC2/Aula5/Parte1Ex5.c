#include <detpic32.h>

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
// declare variables
// initialize ports
    TRISB &= 0x80FF;
    TRISBbits.TRISB0 = 1;
    TRISD |= 0xBFFF;
    TRISD &= 0xFF9F;
    unsigned int counter = 0;
    unsigned int i = 0;
    unsigned int i2 = 0;
    while(1){
        if((PORTB & 0x0000) == 0){
            resetCoreTimer();
            while(readCoreTimer()<500000);
            if((i%10)==0){counter = (counter + 1)%60;}
            send2displays(counter);
            i++;
            if((counter%60) == 59){LATD &= 0x4000;}
        }else{
            resetCoreTimer();
            while(readCoreTimer()<2000000);
            if((i%10)==0){counter = (counter + 59)%60;}
            send2displays(counter);
            i++;
            if((counter%60) == 59){LATD &= 0x4000;}
        }
    }
    return 0;
}
