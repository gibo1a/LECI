#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void DisplayArray(double* a, size_t n){
    assert(a != NULL);
    assert(n != 0);

    for(int i = 0 ; i < n;i++){
        printf("%.2lf\n",a[i]);
    }
}

double* ReadArray(size_t* size_p){
    assert(*size_p > 0);
    assert(size_p != NULL);
    double* ptr;
    ptr = (double*) calloc(*size_p,sizeof(double));
    if(ptr == NULL){
        size_p = 0;
        return NULL;
    }

    printf("Enter elements: ");
    for(int i = 0;  i < *size_p; i++ ){
        scanf("%lf",ptr + i);
    }

    for(int i = 0;i < *size_p;i++){
        printf("%.2lf\n",*(ptr++));
    }
}

double* Append(double* array_1,size_t size_1, double* array_2, size_t size_2){
    assert(array_1 != NULL && array_2 != NULL);
    assert(size_1 > 0 && size_2 > 0);
    double* ptr;
    ptr = (double*) calloc(size_1 + size_2, sizeof(double));
    if(ptr == NULL){
        return NULL;
    }
    for(int i = 0;i < size_1; i++){
        ptr = ptr +i ;
        *ptr = array_1[i];
    }    
    for(int i = size_1; i < size_2; i++){
        ptr = ptr + i;
        *ptr = array_2[i-size_1];
    }
    return ptr;
}

int main(){
    double array1[] = {1.0,2.0,3.0};
    double array2[] = {4.0,5.0,6.0,7.0};
    size_t size = 3;
    Append(&array1,3,&array2,4);
    return 0;
}