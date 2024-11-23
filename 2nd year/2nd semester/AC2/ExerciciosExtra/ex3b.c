#include <detpic32.h>

int main(void){
    TRISE = TRISE & 0xFFF0;
    char c;
    LATE = (LATE & 0xFFF0) | 0x0000;
    while(1){
        putChar('\r');
        c = getChar();
        if(c == '0'){
            putChar(c);
            LATE = (LATE & 0xFFF0) | 0x0001;
        }else if(c == '1'){
            putChar(c);
            LATE = (LATE & 0xFFF0) | 0x0002;
        }else if(c == '2'){
            putChar(c);
            LATE = (LATE & 0xFFF0) | 0x0004;
        }else if(c == '3'){
            putChar(c);
            LATE = (LATE & 0xFFF0) | 0x0008;
        }else{
            LATE = (LATE & 0xFFF0) | 0x000F;
            resetCoreTimer();
            while(readCoreTimer()< 20000 * 1000);
            LATE = (LATE & 0xFFF0) | 0x0000;
        }
    }
    return 0;
}
