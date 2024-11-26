#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include <pthread.h>

#define BUFFER_SIZE 100

pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_not_empty=PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_not_full=PTHREAD_COND_INITIALIZER;
bool stop=false;

typedef struct{
    unsigned int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int size;
} CircularBuffer;

void initBuffer(CircularBuffer *cb){
    cb->head=0;
    cb->tail=0;
    cb->size=0;
}

bool isEmpty(CircularBuffer *cb){
    return cb->size==0;
}

bool isFull(CircularBuffer *cb){
    return cb->size==BUFFER_SIZE;
}

bool enqueue(CircularBuffer *cb, unsigned int value){
    if(isFull(cb)){
        printf("Buffer is full. Cannot enqueue %u.\n",value);
        return false;
    }
    cb->buffer[cb->tail]=value;
    cb->size++;
    cb->tail=(cb->tail+1)%BUFFER_SIZE;
    return true;
}

bool deque(CircularBuffer *cb, unsigned int *value){
    if(isEmpty(cb)){
        printf("Buffer is empty. Cannot deque.\n");
        return false;
    }
    *value=cb->buffer[cb->head];
    cb->head=(cb->head+1)%BUFFER_SIZE;
    cb->size--;
    return true;
}

void displayBuffer(CircularBuffer *cb){
    if(isEmpty(cb)){
        printf("Buffer_state: []\n");
        return;
    }
    printf("Buffer_state: [");
    int index=cb->head;
    for(int i=0;i<cb->size;i++){
        if(i==cb->size-1){
            printf("%u]\n",cb->buffer[index]);
            break;
        }
        printf("%u, ",cb->buffer[index]);
        index=(index+1)%BUFFER_SIZE;
    }
}

void *ConsumerFunc(void *arg){
    CircularBuffer *cb=(CircularBuffer *)arg;
    unsigned int val;
    while(true){
        pthread_mutex_lock(&lock);
        while(isEmpty(cb)){
            if(stop){
                pthread_mutex_unlock(&lock);
                pthread_exit(NULL);
            }
            pthread_cond_wait(&cond_not_empty,&lock);
        }
        deque(cb,&val);
        printf("Consumed : [%u] , ",val);
        displayBuffer(cb);
        pthread_cond_signal(&cond_not_full);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *ProducerFunc(void *arg){
    CircularBuffer *cb=(CircularBuffer *) arg;
    unsigned int input;
    FILE *inputFile=fopen("input-part1.txt","r");
    if (inputFile == NULL) {
        printf("Error opening file.\n");
        stop=true;
        return NULL;
    }
    while(fscanf(inputFile,"%u",&input) != EOF){
        if(input==0){
            stop=true;
            break;
        }
        pthread_mutex_lock(&lock);
        while(isFull(cb)){
            pthread_cond_wait(&cond_not_full,&lock);
        }
        enqueue(cb,input);
        pthread_cond_signal(&cond_not_empty);
        pthread_mutex_unlock(&lock);
    }
    fclose(inputFile); 
    stop=true;
    return NULL;
}


int main(int argc, char *argv[]){
    CircularBuffer *cb=malloc(sizeof(CircularBuffer));
    initBuffer(cb);
    FILE *outputFile=fopen("output-part1.txt","w");
    if(outputFile==NULL){
        printf("Error opening file.\n");
        free(cb);
        return 1;
    }
    freopen("output-part1.txt","w",stdout);
    pthread_t Consumer, Producer;
    pthread_create(&Producer,NULL,ProducerFunc,cb);
    pthread_create(&Consumer,NULL,ConsumerFunc,cb);
    pthread_join(Producer,NULL);
    pthread_join(Consumer,NULL);
    fclose(outputFile);
    free(cb);
    return 0;
}
