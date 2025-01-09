#include <stdio.h>
#define MAX_QUEUE_SIZE 5

typedef struct {
    int front;
    int rear;
    int data[MAX_QUEUE_SIZE];
} QueueType;


void init_queue(QueueType *q){
    q->rear = -1;
    q->front = -1;
}

void queue_print(QueueType *q){
    for(int i=0;i<MAX_QUEUE_SIZE;i++){
        if(i<= q->front|| i> q->rear) printf("   | ");
        else printf("%d | ", q->data[i]);
    }
    printf("\n");
}

void enqueue(QueueType *q, int item){
    q->data[++(q->rear)]=item; 
}

int dequeue(QueueType *q){
    int item = q->data[++(q->front)]; //front를 늘려서 인덱스 범위 제한한
    return item;
}

int main(){
    int item = 0;
    QueueType q;

    init_queue(&q);

    enqueue(&q, 10); queue_print(&q);
    enqueue(&q, 20); queue_print(&q);
    enqueue(&q, 30); queue_print(&q);

    item = dequeue(&q); queue_print(&q);
    item = dequeue(&q); queue_print(&q);
    item = dequeue(&q); queue_print(&q);

    return 0;
}