#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <libgen.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "utils.h"
#include "thread.h"

static int counter = 0;
static pthread_mutex_t accesso;
static pthread_cond_t even, odd;

void *odd_decrease(void *arg){
    while(true){
        mutex_lock(&accesso);

        if(counter <= 2){
            mutex_unlock(&accesso);
            thread_exit(NULL);
        }

        while((counter%2)==0){
            cond_wait(&even,&accesso);
        }

        counter = counter - 1;
        printf("%ld : %d\n",thread_self(),counter);

        cond_broadcast(&odd);

        mutex_unlock(&accesso);
    }
    return NULL;
}

void *even_decrease(void *arg){
    while(true){
        mutex_lock(&accesso);

        if(counter <= 1){
            mutex_unlock(&accesso);
            thread_exit(NULL);
        }
        
        while((counter%2 !=0)){
            cond_wait(&odd,&accesso);
        }

        counter = counter - 1;
        printf("%ld : %d\n",thread_self(),counter);

        cond_broadcast(&even);

        mutex_unlock(&accesso);
    }
}

int main(void){
    while((counter < 10) | (counter > 20)){
        printf("%s","Introduza um numero entre 10 e 20\n");
        scanf("%d",&counter);
    }

    cond_init(&even, NULL);
    cond_init(&odd, NULL);
    mutex_init(&accesso, NULL);

    pthread_t thr1,thr2;
    thread_create(&thr1, NULL,even_decrease, NULL);
    thread_create(&thr2, NULL,odd_decrease, NULL);
    thread_join(thr1, NULL);
    thread_join(thr2, NULL);

    mutex_destroy(&accesso);
    cond_destroy(&even);
    cond_destroy(&odd);

    printf("Both threads have terminated, final value: %d\n", counter);

    return 0;
}
