#include <detpic32.h>

int main(void){
    unsigned int cnt = 0;
    unsigned int c;
    while(1){
        c = getChar();
        switch (c){
        case '0':
            putChar('\r');
            resetCoreTimer();
            while(readCoreTimer()<2000000/5);
            cnt = (cnt+1)%100;
            break;
        case '1':
            putChar('\r');
            resetCoreTimer();
            while(readCoreTimer()<2000000/5);
            cnt = (cnt+1)%100;
            break;
        case '2':
            putChar('\r');
            resetCoreTimer();
            while(readCoreTimer()<2000000/5);
            cnt = (cnt+1)%100;
            break;
        case '3':
            putChar('\r');
            resetCoreTimer();
            while(readCoreTimer()<2000000/5);
            cnt = (cnt+1)%100;
            break;
        case '4':
            putChar('\r');
            resetCoreTimer();
            while(readCoreTimer()<2000000/5);
            cnt = (cnt+1)%100;
            break;
        default:
            putChar('\r');
            resetCoreTimer();
            while(readCoreTimer()<2000000);
            cnt = (cnt+1)%100;
            break;
        }
        printInt(cnt,10 | 2 << 16);
    }
    return 0;
}
