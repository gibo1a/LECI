#include <stdio.h>
#include <assert.h>

size_t NUM_OPS;

int recursive_1(int n){
    assert(n > 0);
    if(n == 1){
        return 1;
    }else{
        NUM_OPS++;
        return recursive_1(n/2) + n;
    }
}

int recursive_2(int n){
    assert(n > 0);
    if(n== 1){
        return 1;
    }else{
        NUM_OPS += 2;
        return recursive_2(n/2) + recursive_2((n+1)/2) + n;
    }
}

int recursive_3(int n){
    assert(n > 0);
    if(n == 1){
        return 1;
    }else if (n%2 == 0){
        NUM_OPS++;
        return 2*recursive_3(n/2) + n;
    }else{
        NUM_OPS += 2;
        return recursive_3(n/2) + recursive_3((n+1)/2) + n;
    }
    
}

void print_table1(){
    int i,j,k;
    printf("Introduza um numero inteiro (não negativo)");
    scanf("%d",&j);
    for(i = 1; i <=j;i++){
        NUM_OPS = 0;
        k = recursive_1(i);
        printf("T(%3d)= %5d --- Numero de chamadas recursivas = %ld\n",i,k,NUM_OPS);
    }
}

void print_table2(){
    int i,j,k;
    printf("Introduza um numero inteiro (não negativo)");
    scanf("%d",&j);
    for(i = 1; i <=j;i++){
        NUM_OPS = 0;
        k = recursive_2(i);
        printf("T(%3d)= %5d --- Numero de chamadas recursivas = %ld\n",i,k,NUM_OPS);
    }
}

void print_table3(){
    int i,j,k;
    printf("Introduza um numero inteiro (não negativo)");
    scanf("%d",&j);
    for(i = 1; i <=j;i++){
        NUM_OPS = 0;
        k = recursive_3(i);
        printf("T(%3d)= %5d --- Numero de chamadas recursivas = %ld\n",i,k,NUM_OPS);
    }
}



int main(void){
    print_table3();
    return 0;
}