#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int main(int argc,char** argv){
    long pid = strtol(argv[1], NULL, 10);
    kill(pid,SIGINT);
    return 0;
}