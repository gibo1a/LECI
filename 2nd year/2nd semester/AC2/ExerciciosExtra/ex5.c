#include <detpic32.h>

unsigned char toBcd(unsigned char value){
    return ((value / 10) << 4) + (value % 10);
}

int main(void){
    //static const char disp7Scodes[] = {0x3F, 0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x39,0x5E,0x79,0x71};
    TRISD = TRISD & 0xFF9F;
    TRISB = TRISB & 0x80FF;
    unsigned int counter = 0;
    char c = getChar();
    while(1){
        unsigned int freq = 20000000;
        c = inkey();
        if(c == '0'){
            freq /= 2*(1+0);
        }else if(c=='1'){
            freq /= 2*(1+1);
        }else if(c == '2'){
            freq /= 2*(1+2);
        }else if(c=='3'){
            freq /= 2*(1+3);
        }else if(c=='4'){
            freq /= 2*(1+4);
        }else if(c == 'f'){
            putChar('\t');
            printInt(freq,10 | 2 <<10);
            putChar('\t');
            printInt(counter,10 | 2 <<10);
            //unsigned int num = toBcd(counter);
            //send2displays(num);
            //resetCoreTimer();
            //while(readCoreTimer()<400000);
        }
        putChar('\r');
        printInt(counter,10 | 2 <<10);
        resetCoreTimer();
        while(readCoreTimer()<freq);
        counter = (counter+1)%100;
    }
    return 0;
}
