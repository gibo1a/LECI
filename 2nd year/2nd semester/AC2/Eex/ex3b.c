#include <detpic32.h>

int main(void){
    TRISE = TRISE & 0xFFF0;
    while (1){
        char c = getChar();
        switch (c){
        case '0':
            LATE = (LATE & 0xFFF0)|0x0001;
            break;
        case '1':
            LATE = (LATE & 0xFFF0)|0x0002;
            break;
        case '2':
            LATE = (LATE & 0xFFF0)|0x0004;
            break;
        case '3':
            LATE = (LATE & 0xFFF0)|0x0008;
            break;
        default:
            LATE = (LATE & 0xFFF0)|0x000F;
            resetCoreTimer();
            while(readCoreTimer()<20000000);
            LATE = (LATE & 0xFFF0)|0x0000;
            break;
        }
    }
    return 0;
}
