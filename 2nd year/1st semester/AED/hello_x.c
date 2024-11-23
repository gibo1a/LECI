#include <stdio.h>

int main(void){
    char nome[10];
    char apelido[10];

    printf("Introduza o seu nome! ");
    scanf("%s", &nome);
    printf("Introduza o seu apelido! ");
    scanf("%s",&apelido);
    printf("Hello %s %s!", nome, apelido);
    return 0;
}