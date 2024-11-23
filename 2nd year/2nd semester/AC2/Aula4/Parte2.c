#include <detpic32.h>

int main(void){
    TRISB = TRISB & 0x80FF;
    TRISD = TRISD & 0xFF9F;
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;
    while (1){
        int letra = getChar();
        if(letra == 'a'|| letra == 'A'){LATB = (LATB & 0x80FF) | 0x0100;}
        if(letra == 'b'|| letra == 'B'){LATB = (LATB & 0x80FF) | 0x0200;}
        if(letra == 'c'|| letra == 'C'){LATB = (LATB & 0x80FF) | 0x0400;}
        if(letra == 'd'|| letra == 'D'){LATB = (LATB & 0x80FF) | 0x0800;}
        if(letra == 'e'|| letra == 'E'){LATB = (LATB & 0x80FF) | 0x1000;}
        if(letra == 'f'|| letra == 'F'){LATB = (LATB & 0x80FF) | 0x2000;}
        if(letra == 'g'|| letra == 'G'){LATB = (LATB & 0x80FF) | 0x4000;}
    }    
}
