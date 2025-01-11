#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
typedef struct{
    int data[MAX_QUEUE_SIZE];
    int front, rear;
}QueueType;

void init_queue(QueueType *q){
    q->front = q->rear = 0;
}

int is_empty(QueueType *q){
    return (q->front == q->rear);
}

int is_full(QueueType*q){
    return ((q->rear + 1)%MAX_QUEUE_SIZE == q->front);
}

void queue_print(QueueType *q){
    printf("Queue(front = %d, rear = %d) = ", q->front, q->rear);
    if(!is_empty(q)){
        int i = q->front;
        do{
            i=(i+1)%(MAX_QUEUE_SIZE);
            printf("%d | ", q->data[i]);
            if(i==q->rear)
            break;
        } while(i!= q->front);
    }
    printf("\n");
}

void enqueue(QueueType *q, int item){
    if(is_full(q)) exit(1);
    q->rear = (q->rear + 1)%MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

int dequeue(QueueType *q){
    if(is_empty(q)) exit(1);
    q->front = (q->front + 1)%MAX_QUEUE_SIZE;
    return q->data[q->front];
}

int peek(QueueType *q){
    return q->data[(q->front+1)%MAX_QUEUE_SIZE];
}


int main(){
    QueueType queue;
    int element;
    init_queue(&queue);

    printf("--데이터 추가 단계--\n");
    while(!is_full(&queue)){
        printf("정수를 입력: ");
        scanf("%d", &element);
        enqueue(&queue, element);
        queue_print(&queue);
    }
    printf("큐 포화.\n\n");

    printf("--데이터 삭제 단계--\n");
    while(!is_empty(&queue)){
        element = dequeue(&queue);
        printf("꺼낸 정수: %d \n", element);
        queue_print(&queue);
    }
    printf("큐는 공백입니다");
    
    return 0;
}
