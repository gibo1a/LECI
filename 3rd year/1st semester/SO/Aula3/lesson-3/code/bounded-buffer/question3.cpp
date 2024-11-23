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
    int number = 0;
    while((number < 10) | (number >20)){
        printf("%s","Insert an integer between 10 and 20 \n");
        scanf("%d",&number);
    }
    *counter = number;

    int sem = psemget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    psem_up(sem,0);

    pid_t pids[2];

    for(int i = 0;i < 2;i++){
        if ((pids[i] = pfork() == 0)){
            while(*counter != 1){
                psem_down(sem,0);
                *counter = *counter - 1;
                printf("%d %d\n",getpid(),*counter);
                psem_up(sem,0);
            }
        }
    }
    pwait(NULL);
    pshmdt(counter);
    pshmctl(shmid, IPC_RMID, NULL);
    psemctl(sem, 0, IPC_RMID, NULL);
    return 0;
}