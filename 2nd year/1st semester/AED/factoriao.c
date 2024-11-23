#include <stdio.h>
#include <math.h>
#include <stdlib.h>

unsigned int factorial(unsigned int n){
    int i,factorial = 1;

    for(i = 2;i <=n; i++){
        factorial *= i;
    }
    return factorial;
}

int* digits(int n){
    int i = 0,digit = n;
    size_t size = floor(log10(n)+1);
    int* digits = calloc(size,sizeof(int));
    while (n != 0){
        digit = n%10;
        digits[i] = digit;
        i++;
        n = n/10;
    }
    
    return digits;
}

unsigned int factoriao(unsigned int n){
    int i,factoriao;
    int* digit = digits(n);
    size_t size = floor(log10(n))+1;
    for(i = 0; i <= size;i++){
        factoriao += factorial(digit[i]);
    }
    free(digit);
    printf("%d",factoriao);
    return factoriao;
}

int main(){
    factoriao(1234);
    return 0;
}