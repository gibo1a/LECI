#include <detpic32.h>

int main(void){
    TRISE = TRISE & 0xFFF0;
    TRISD = TRISD & 0xFF9F;
    TRISB = TRISB & 0x80FF;
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;
    unsigned int cnt;
    while (1){
        char c = getChar();
        switch (c){
        case '0':
            LATE = (LATE & 0xFFF0)|0x0001;
            while(1){
                LATDbits.LATD5 = !LATDbits.LATD5;
                LATDbits.LATD6 = !LATDbits.LATD6;
                LATB = LATDbits.LATD5 ? ((LATB & 0x80FF)|0x003F)<<8 : ((LATB & 0x80FF)|0x003F)<<8;
                resetCoreTimer();
                while(readCoreTimer()<20000 * 10);
            }
            break;
        case '1':
            LATE = (LATE & 0xFFF0)|0x0002;
            while(1){
                LATDbits.LATD5 = !LATDbits.LATD5;
                LATDbits.LATD6 = !LATDbits.LATD6;
                LATB = LATDbits.LATD5 ? ((LATB & 0x80FF)|0x0006)<<8 : ((LATB & 0x80FF)|0x003F)<<8;
                resetCoreTimer();
                while(readCoreTimer()<20000 * 10);
            }
            break;
        case '2':
            LATE = (LATE & 0xFFF0)|0x0004;
            while(1){
                LATDbits.LATD5 = !LATDbits.LATD5;
                LATDbits.LATD6 = !LATDbits.LATD6;
                LATB = LATDbits.LATD5 ? ((LATB & 0x80FF)|0x005B)<<8 : ((LATB & 0x80FF)|0x003F)<<8;
                resetCoreTimer();
                while(readCoreTimer()<20000 * 10);
            }
            break;
        case '3':
            LATE = (LATE & 0xFFF0)|0x0008;
            while(1){
                LATDbits.LATD5 = !LATDbits.LATD5;
                LATDbits.LATD6 = !LATDbits.LATD6;
                LATB = LATDbits.LATD5 ? ((LATB & 0x80FF)|0x004F)<<8 : ((LATB & 0x80FF)|0x003F)<<8;
                resetCoreTimer();
                while(readCoreTimer()<20000 * 10);
            }
            break;
        default:
            cnt = 0;
            while(cnt!=100){
                LATE = (LATE & 0xFFF0)|0x000F;
                LATDbits.LATD5 = !LATDbits.LATD5;
                LATDbits.LATD6 = !LATDbits.LATD6;
                LATB = LATDbits.LATD5 ? ((LATB & 0x80FF)|0x0071)<<8 : ((LATB & 0x80FF)|0x0071)<<8;
                resetCoreTimer();
                while(readCoreTimer()<20000 * 10);
                cnt++;
            }
            LATE = (LATE & 0xFFF0)|0x0000;
            break;
        }
    }
    return 0;
}
