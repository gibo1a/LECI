#include <stdio.h>
#include <assert.h>

size_t nadd = 0;
size_t ncall = 0;
size_t mem[100][100];

int Delannoy(int n, int m){
    assert(n >= 0 && m >= 0);
    ncall ++;
    if(n == 0|| m == 0){
        return 1;
    }else{
        nadd += 2;
        return Delannoy(n-1,m) + Delannoy(n-1,m-1) + Delannoy(n,m-1);
    }
}

size_t Delannoy1(size_t n,size_t m){
    assert(n >= 0 && m >= 0);
    ncall ++;
    size_t i,j;
    size_t array[n+1][m+1];
    for(i = 0; i <= n;i++){
        for(j = 0; j <= m;j++){
            if(i == 0 || j == 0){
                array[i][j] = 1;
            }else{
                nadd += 2;
                array[i][j] = array[i -1][j] + array[i-1][j-1] + array[i][j-1];
            }
        }
    }
    return array[n][m];
}

size_t Delannoy2(size_t n,size_t m){
    assert(n >= 0 && m >= 0);
    ncall++;
    size_t i,j;
    for(i = 0;i <= n;i++){
        for(j = 0;j <= m;j++){
            if(i == 0 || j == 0){
                mem[i][j] = 1;
            }else{
                nadd += 2;
                mem[i][j] = mem[i-1][j] + mem[i-1][j-1] + mem[i][j-1];
            }
        }
    }
    return mem[n][m];
}

int printTable(size_t n, size_t m){
    printf("Mehthod%5s%5s%15s%10s%10s\n","n","m","del(n,m)","nadd","ncall");
    size_t r = Delannoy(n,m);
    printf("RM%10ld%5ld%15ld%10ld%10ld\n",n,m,r,nadd,ncall);
    ncall = 0;
    nadd = 0;
    r = Delannoy1(n,m);
    printf("PD%10ld%5ld%15ld%10ld%10ld\n",n,m,r,nadd,ncall);
    ncall = 0;
    nadd = 0;
    r = Delannoy2(n,m);
    printf("PDM%9ld%5ld%15ld%10ld%10ld\n",n,m,Delannoy2(n,m),nadd,ncall);
    return 0;
}

int main(void){
    printTable(6,6);
    return 0;
}