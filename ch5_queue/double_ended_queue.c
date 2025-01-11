#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5 // |0|1|2|3|4|

typedef struct{
    int data[MAX_QUEUE_SIZE];
    int front, rear;
} DequeType;

void error(char* message){
    fprintf(stderr,"%s\n", message);
    exit(1);
}

void init_deque(DequeType *q){
    q->front = q->rear = 0;
}

int is_empty(DequeType *q){
    return (q->front == q->rear);
}

int is_full(DequeType *q){
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void deque_print(DequeType *q){
    printf("DEQUE(front = %d, rear = %d) = ", q->front,q->rear);
    if(!is_empty(q)){
        int i = q->front;
        do{
            i =(i+1)%MAX_QUEUE_SIZE; //front는 0번째 원소를 가리키므로 +1
            printf("%d | ", q->data[i]);
            if(i==q->rear) break;
        }while(i!=q->front);
    }
    printf("\n");
}

void add_rear(DequeType *q, int item){
    if(is_full(q)) error("큐가 포화 상태");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

int delete_front(DequeType *q){
    if(is_empty(q)) error("큐가 공백");
    return q->data[q->front];
}

int get_front(DequeType *q){
    if(is_empty(q)) error("큐가 공백");
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE]; //front 뒤에 있는 덱의 첫번째 값 반환
}

void add_front(DequeType *q, int item){
    if(is_full(q)) error("큐가 포화");
    q->front = (q->front - 1 + MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE;
    q->data[(q->front + 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE] = item;
}

int delete_rear(DequeType *q){
    if(is_empty(q)) error("큐가 공백");
    q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    return q->data[(q->rear + 1) % MAX_QUEUE_SIZE];
}

int get_rear(DequeType *q){
    if(is_empty(q)) error("큐가 공백");
    return q->data[q->rear];
}

int main(){
    DequeType queue;

    init_deque(&queue);

    for(int i=0;i<3;i++){
        add_front(&queue, i);
        deque_print(&queue);
    }

    for(int i=0;i<3;i++){
        delete_rear(&queue);
        deque_print(&queue);
    }

    return 0;
}