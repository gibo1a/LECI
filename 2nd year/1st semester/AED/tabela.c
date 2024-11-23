#include <stdio.h>
#include <math.h>

int main(void){
    int linhas;
    printf("Indique o número de linhas! ");
    scanf("%d",&linhas);
    printf("%s %s %s\n","Número","Quadrado","Raíz");
    for(int i = 1; i <=linhas;i++){
        printf("%6d %8.2lf %4.2lf\n",i,pow(i,2),sqrt(i));
    }
    return 0;

} 