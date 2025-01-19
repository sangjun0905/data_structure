//기본 연결리스트에 두개의 rear와 front 포인터를 추가한 것
// front 삭제 후 메모리 해제 필수

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct QueueNode {
    int data;
    struct QueueNode* link;
} QueueNode;

typedef struct{
    QueueNode *front, *rear;
} LinkedQueueType;

void init(LinkedQueueType *q){
    q->front = q->rear =  NULL;
}

int is_empty(LinkedQueueType *q){
    return (q->front == NULL);
}

int is_full(LinkedQueueType *q){
    return 0;
}

void enqueue(LinkedQueueType *q, int data){
    QueueNode *temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->data = data;
    temp->link = NULL;
    if(is_empty(q)){
        q->front = temp;
        q->rear = temp;
    }
    else {
        q->rear->link = temp;
        q->rear = temp;
    }
    
}

int dequeue(LinkedQueueType *q){
    int data;
    QueueNode *temp = q->front;

    if(is_empty(q)){
        fprintf(stderr, "공백상태");
        exit(1);
    }
    else{
        data = q->front->data;
        q->front = q->front->link;
        if(q->front == NULL){
            q->rear = NULL;
        }
        free(temp);
        return data;
    }
}

void print_queue(LinkedQueueType *q){
    QueueNode *p;
    for(p = q->front; p!=NULL; p=p->link){
        printf("%d->", p->data);
    }
    printf("\n");
}

int main(){
    LinkedQueueType queue;

    init(&queue);

    enqueue(&queue, 1); print_queue(&queue);
    enqueue(&queue, 2); print_queue(&queue);
    enqueue(&queue, 3); print_queue(&queue);
    enqueue(&queue, 4); print_queue(&queue);

    printf("%d\n", dequeue(&queue)); print_queue(&queue);
    printf("%d\n", dequeue(&queue)); print_queue(&queue);
    printf("%d\n", dequeue(&queue)); print_queue(&queue);
    printf("%d\n", dequeue(&queue)); print_queue(&queue);

    return 0;
}