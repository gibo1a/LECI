#include <stdio.h>

void Permute(int* a, int* b, int* c)
{
    int temp = *a;
    *a = *c;
    *c = temp;
}