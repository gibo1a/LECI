#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <libgen.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "process.h"

int main(void){
    int shmid = pshmget(IPC_PRIVATE, sizeof(int), 0600 | IPC_CREAT | IPC_EXCL);
    int *counter = (int *)pshmat(shmid, NULL, 0);
    *counter = 0;

    pid_t pid = pfork();

    if(pid == 0){
        int number = 0;
        while((number < 10) | (number >20)){
            printf("%s","Insert an integer between 10 and 20 \n");
            scanf("%u",&number);
        }
        for(int i = 0;i < number;i++){
            *counter = *counter + 1;
            printf("%d\n",*counter);
        }
        exit(EXIT_SUCCESS);
    }else{
        pwait(NULL);
        while (*counter > 1){
            *counter = *counter - 1;
            printf("%d\n",*counter);
        }
        pshmdt(counter);
        pshmctl(shmid, IPC_RMID, NULL);
        exit(0);   
    }
    return 0;
}