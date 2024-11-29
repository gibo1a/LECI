#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <libgen.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

#include "utils.h"
#include "thread.h"
#include "fifo_q4.h"

#define MAX_STR_LEN 100
#define N_POLL 10

struct Buffer
{
    char *str;
    uint32_t num_char;
    uint32_t num_digits;
    uint32_t num_letters;
    uint32_t done;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
};

static Fifo freeBuffers;
static Fifo pendingRequests;
static Buffer poll[N_POLL]; 

void BufferInit(Buffer buffer){
    buffer.str = (char*)mem_alloc(sizeof(char)*(MAX_STR_LEN+1));
    buffer.num_char = 0;
    buffer.num_digits = 0;
    buffer.num_letters = 0;
    buffer.done = 0;
    mutex_init(&buffer.mutex,NULL);
    cond_init(&buffer.cond,NULL);
}

uint32_t getFreeBuffer(){
    uint32_t id = fifoRetrieve(&freeBuffers);
    return id;
}

void putRequestData(char *item,uint32_t id){
    mutex_lock(&poll[id].mutex);
    poll[id].str = item;
    poll[id].done = 0;
    mutex_unlock(&poll[id].mutex);
}

void submitRequest(uint32_t id){
    fifoInsert(&pendingRequests,id);
    printf("%d\n",id);
}

void waitForResponse(uint32_t id){
    while(!(poll[id].done)){
        cond_wait(&poll[id].cond,&poll[id].mutex);
    }
}

void processResponseData(int id){
    printf("%d, %d, %d",poll[id].num_char,poll[id].num_digits,poll[id].num_letters);
}

void releaseBuffer(int id){
    fifoInsert(&freeBuffers,id);
}

void *clientThread(void *args){
    char *data = (char*)args;

    uint32_t id = getFreeBuffer(); 

    putRequestData(data,id);

    submitRequest(id);

    waitForResponse(id);

    processResponseData(id); 

    releaseBuffer(id);

    thread_exit(NULL);
    return NULL;
}

uint32_t getPendingRequest(){
    uint32_t id = fifoRetrieve(&pendingRequests);
    printf("%ds\n",id);
    return id;
}

Buffer *getRequestData(uint32_t id){
    return &poll[id];
}

uint32_t* produceResponse(Buffer *req){
    u_int32_t *results = (uint32_t*)malloc(sizeof(uint32_t)*3);
    char *ptr = req->str;
    while(*ptr != '\0'){
        if (isdigit(*ptr)){
            results[1] += 1;
        }
        if(isalpha(*ptr)){
            results[2] += 1;
        }
        results[0] += 1;
        ptr++;
    }
    return results;
}

void putResponseData(uint32_t *data,uint32_t id){
    mutex_lock(&poll[id].mutex);
    poll[id].num_char = data[0];
    poll[id].num_digits = data[1];
    poll[id].num_letters = data[2];
    mutex_unlock(&poll[id].mutex);
}

void notifyClient(uint32_t id){
    mutex_lock(&poll[id].mutex);
    poll[id].done = 1;
    cond_broadcast(&poll[id].cond);
    mutex_unlock(&poll[id].mutex);
}

void* serverThread(void *args){
    while(true){
        uint32_t id = getPendingRequest();

        if (id == N_POLL * N_POLL){break;}

        Buffer *buff = getRequestData(id);

        uint32_t *data = produceResponse(buff);

        putResponseData(data,id);

        notifyClient(id);
    }
    thread_exit(NULL);
    return NULL;
}

int main(void){

    // create free buffer id fifo
    fifoInit(&freeBuffers);
    for(uint32_t i = 0;i < N_POLL;i++){
        fifoInsert(&freeBuffers,i);
    }

    // create pending request id fifo
    fifoInit(&pendingRequests);

    // initialize buffers in poll
    for(uint32_t i = 0;i < N_POLL;i++){
        BufferInit(poll[i]);
    }

    char string_1[] = {"ola bom dia 12345"};
    char string_2[] = {"ola bom dia"};
    char string_3[] = {"ola bom dia"};
    char *test[] = {string_1,string_2,string_3};

    uint32_t n_clients = 3;
    pthread_t clients[n_clients];
    uint32_t clients_id[n_clients];

    pthread_t server[1];
    uint32_t server_id[1];

    for(uint32_t i = 0;i < n_clients;i++){
        clients_id[i] = i;
        thread_create(&clients[clients_id[i]],NULL,clientThread,test[i]);
    }

    for(uint32_t i = 0;i < 1;i++){
        server_id[i] = i;
        thread_create(&server[server_id[i]],NULL,serverThread,NULL);
    }

    for(uint32_t i = 0;i < n_clients;i++){
        thread_join(clients[clients_id[i]],NULL);
    }

    fifoInsert(&pendingRequests,N_POLL * N_POLL);

    for(uint32_t i = 0;i < 1;i++){
        thread_join(server[server_id[i]],NULL);
    }

    fifoDestroy(&freeBuffers);
    fifoDestroy(&pendingRequests);
    for(uint32_t i = 0;i < N_POLL;i++){
        mutex_destroy(&poll[i].mutex);
        cond_destroy(&poll[i].cond);
    }

    return 0;
}
