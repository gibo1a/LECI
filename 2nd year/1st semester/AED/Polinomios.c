#include <stdio.h>
#include <assert.h>
#include <math.h>

void DisplayPol(double* coef, size_t degree){
    assert(coef != NULL);
    assert(degree >= 0);

    printf("Pol (x) = ");

    for(int i = 0;i <= degree; i++){
        printf("%.2lf * x^%d ",coef[i],i);
    }
}

double ComputePol(double* coef,size_t degree, double x){
    assert(coef != NULL && degree >= 0);
    double sum;
    for(int i = 0; i <=degree; i++){
        sum += coef[i] * pow(x,i);
    } 
    return sum;
}
unsigned int GetRealRoots(double* coef,size_t degree, double* root_1, double* root_2){
    assert(coef != NULL && degree == 2 && coef[0] != 0);
    assert(root_1 != NULL && root_2 != NULL);
    *root_1 = (-(unsigned int)coef[1] + sqrt(pow((unsigned int)coef[1],2) - (4 * (unsigned int)coef[0] * (unsigned int)coef[2])))/2*(unsigned int)coef[0];
    *root_2 = (-(unsigned int)coef[1] - sqrt(pow((unsigned int)coef[1],2) - (4 * (unsigned int)coef[0] * (unsigned int)coef[2])))/2*(unsigned int)coef[0];
    if(root_1 == NULL && root_2 == NULL){
        *root_1 = 0.0;
        *root_2 = 0.0;
        return 0;
    }else if(root_1 != NULL && root_2 != NULL){
        return 2;
    }else{
        return 1;
    }
}

int main(){
    double pol[] = {1.0,4.0,1.0};
    double *p_pol = pol;
    DisplayPol(p_pol,2);
    double result = ComputePol(p_pol,2,2);
    printf("%.2lf",result);
    double root_1 = 0;
    double root_2 = 0;
    GetRealRoots(p_pol,2,&root_1,&root_2);
    return 0;
}