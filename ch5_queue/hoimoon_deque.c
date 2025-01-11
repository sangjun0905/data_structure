#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE_DEQUEUE 10

typedef struct{
    int front;  
    int rear;
    char word[MAX_SIZE_DEQUEUE];
} DequeueType;

void init_dequeue(DequeueType *q){
    q->front = q->rear = 0;
}

en