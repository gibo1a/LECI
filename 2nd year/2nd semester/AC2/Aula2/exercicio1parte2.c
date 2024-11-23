void main(void){
    int cnt1 = 0;
    int cnt5 = 0;
    int cnt10 = 0;
    while(1){
        resetCoreTimer();
        delay(1000);
        cnt10++;
        if(cnt10%2==0){
            cnt5+=5;
        }
        if(cnt10%10==0){cnt1+=10;}
        putChar('\r');
        printInt(cnt1,10|5<<16);
        printInt(cnt5,10|5<<16);
        printInt(cnt10,10|5<<16);
    }
}