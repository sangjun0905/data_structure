// 이중 연결 리스트. llink는 선행 노드의 주소, rlink는 뒤 노드의 주소를 담음.
// p == p->llink->rlink == p->rlink->llink

// 헤드 포인터와는 다른 존재인 헤드 노드 존재. 
// 헤드 노드에는 값을 담지 않는 노드

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct DListNode{
    int data;
    struct DListNode *llink;
    struct DListNode *rlink
} DListNode;

void init(DListNode* phead){
    phead->llink = phead;
    phead->rlink = phead;
}

void dinsert(DListNode *before, int data){
    DListNode *new = (DListNode*)malloc(sizeof(DListNode));
    new->data = data;
    new->llink = before;
    new->rlink = before->rlink;
    before->rlink->llink = new;
    before->rlink = new;
}

void ddelete(DListNode *head, DListNode *removed){
    if(removed == head) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}

void print_dlist(DListNode *phead){
    DListNode* p;
    for(p = phead->rlink; p != phead; p = p->rlink){
        printf("<-| |%d| |->", p->data);
    }
    printf("\n");
}

int main(){
    DListNode *head = (DListNode*)malloc(sizeof(DListNode));
    init(head);
    printf("추가단계\n");
    for(int i = 0; i<5; i++){
        dinsert(head, i);
        print_dlist(head);
    }
    printf("\n삭제단계\n");
    for(int i=0; i<5; i++){
        print_dlist(head);
        ddelete(head, head->rlink);
    }
    
    free(head);
    return 0;
}
