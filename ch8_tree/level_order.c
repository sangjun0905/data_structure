// 레벨 순회는 큐를 이용한 순회법
// 큐에 하나라도 노드가 있으면 계속 반복
// 큐의 노드를 꺼내어 방문, 그 노드의 자식 노드를 큐에 삽입


#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;


#define MAX_QUEUE_SIZE 100
typedef TreeNode * element;

typedef struct{
    TreeNode* data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

void error(char *message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_queue(QueueType *q){
    q->front = q->rear = 0;
}

int is_empty(QueueType *q){
    return (q->front == q->rear);
}

int is_full(QueueType *q){
    return ((q->rear + 1)%MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType *q, TreeNode *item){
    if(is_full(q)) error("fullllll!!!!!!!");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

TreeNode *dequeue(QueueType *q){
    if(is_empty(q)) error("empty!!!!!!!!!!!");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}


void level_order(TreeNode *ptr){
    QueueType q;
    init_queue(&q);
     
    if(ptr == NULL) return;
    enqueue(&q, ptr);
    while (!is_empty(&q)){
        ptr = dequeue(&q);
        printf(" [%d] ", ptr->data);
        if(ptr->left) enqueue(&q, ptr->left);
        if(ptr->right) enqueue(&q, ptr->right);
    }
}

TreeNode n1 = { 1, NULL, NULL };                                //n6                                           15
TreeNode n2 = { 4, &n1, NULL };                         //n2              n5                            4               20
TreeNode n3 = { 16, NULL, NULL };                   //n1             //n3       n4                   1               16      25
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode *root = &n6;

int main(){
    printf("level order= ");
    level_order(root);
    printf("\n");
    return 0;
}
