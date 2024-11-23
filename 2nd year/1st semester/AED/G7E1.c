#include <stdio.h>
#include "IntegersQueue.h"
#include "IntegersStack.h"
#include <math.h>

#define MAX(a,b) ((a) > (b)? (a):(b))

int main(void){
    int num;
    int result;
    printf("Introduza um número: ");
    scanf("%d",&num);
    int num_len = (int)floor(log10(num));
    Stack* s = StackCreate(MAX(10,num_len));
    Queue* q = QueueCreate(MAX(10,num_len));
    int digits[num];
    for(int i = 0; i <= num_len;i++){
        if(num >=10){
            digits[i] = num%10;
        }else{
            digits[i] = num;
        }
        num /= 10;
    }

    for(int i = 0;i<=num_len;i++){
        StackPush(s,digits[i]);
        QueueEnqueue(q,digits[i]);
    }

    for(int i = 0;i<=num_len;i++){
        int digit_stack = StackPop(s);
        int digit_queue = QueueDequeue(q);
        if(digit_stack != digit_queue){
            result = 0;
            break;
        }
        result = 1;
    }

    if(result == 1){
        printf("True!\n");
    }else{
        printf("False!\n");
    }
    
    StackDestroy(&s);
    QueueDestroy(&q);
    return 0;
}
