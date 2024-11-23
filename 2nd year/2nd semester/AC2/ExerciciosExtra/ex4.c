#include <detpic32.h>

int main(void){
    TRISE = TRISE & 0xFFF0;
    TRISD = TRISD & 0xFF9F;
    TRISB = TRISB & 0x80FF;
    char c;
    LATE = (LATE & 0xFFF0) | 0x0000;
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;
    putChar('\r');
    c = getChar();
    if(c == '0'){
        while(1){
            putChar('\r');
            putChar(c);
            LATE = (LATE & 0xFFF0) | 0x0001;
            LATDbits.LATD5 = !LATDbits.LATD5;
            LATDbits.LATD6 = !LATDbits.LATD6;
            LATB = LATDbits.LATD5?(LATB & 0x80FF) | (0x3F<<8):(LATB & 0x80FF) | (0x3F<<8);
            resetCoreTimer();
            while(readCoreTimer()<200000);
        }
    }else if(c == '1'){
        while(1){
            putChar('\r');
            putChar(c);
            LATE = (LATE & 0xFFF0) | 0x0002;
            resetCoreTimer();
            while(readCoreTimer()<200000);
            LATDbits.LATD5 = !LATDbits.LATD5;
            LATDbits.LATD6 = !LATDbits.LATD6;
            LATB = LATDbits.LATD5?(LATB & 0x80FF) | (0x06<<8):(LATB & 0x80FF) | (0x3F<<8);
        }
    }else if(c == '2'){
        while(1){
            putChar('\r');
            putChar(c);
            LATE = (LATE & 0xFFF0) | 0x0004;
            resetCoreTimer();
            while(readCoreTimer()<200000);
            LATDbits.LATD5 = !LATDbits.LATD5;
            LATDbits.LATD6 = !LATDbits.LATD6;
            LATB = LATDbits.LATD5?(LATB & 0x80FF) | (0x5B<<8):(LATB & 0x80FF) | (0x3F<<8);
        }
    }else if(c == '3'){
        while(1){
            putChar('\r');
            putChar(c);
            LATE = (LATE & 0xFFF0) | 0x0008;
            resetCoreTimer();
            while(readCoreTimer()<200000);
            LATDbits.LATD5 = !LATDbits.LATD5;
            LATDbits.LATD6 = !LATDbits.LATD6;
            LATB = LATDbits.LATD5?(LATB & 0x80FF) | (0x4F<<8):(LATB & 0x80FF) | (0x3F<<8);
        }
    }else{
        LATE = (LATE & 0xFFF0) | 0x000F;
        resetCoreTimer();
        while(readCoreTimer()< 20000 * 1000);
        LATE = (LATE & 0xFFF0) | 0x0000;
        resetCoreTimer();
        while(readCoreTimer()<200000);
        LATDbits.LATD5 = !LATDbits.LATD5;
        LATDbits.LATD6 = !LATDbits.LATD6;
        LATB = (LATB & 0x80FF) | (0x71<<8);
    }
    return 0;
}
