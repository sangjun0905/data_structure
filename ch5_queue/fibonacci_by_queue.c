#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 3

typedef struct{
    int front;
    int rear;
    int data[MAX_QUEUE_SIZE];
} QueueType;


void init_queue(QueueType *q){
    q->front = q->rear = 0;
}
void first_init_fibonacci(QueueType *q){
    q->data[++(q->rear)]=0;
    q->data[++(q->rear)]=1;
}

void enqueue(QueueType *q, int item){
    q-> rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

int dequeue(QueueType *q){
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

int main(){
    int input;

    QueueType queue;
    first_init_fibonacci(&queue);
    scanf("%d", &input);

    for(int i=0;i<input-2;i++){
        int prev = dequeue(&queue);
        enqueue(&queue, prev + queue.data[queue.rear]);
    }

    printf("%d번째 피보나치는 %d 입니다", input, queue.data[queue.rear]);

    return 0;
}

// 0 1 1 2 3 5 8 13