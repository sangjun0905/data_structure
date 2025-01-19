// 원형 연결리스트, head는 가장 먼저 들어간 마지막 노드드
// 모든 노드를 따라가다보면 시작 노드로 복귀 가능

#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode{
    int data;
    struct ListNode *link;
} ListNode;

ListNode* insert_first(ListNode* head, int data){
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    node->data = data;
    if(head == NULL){
        head = node;
        node->link = head;
    }
    else{
        node->link = head->link;
        head->link = node;
    }

    return head;
}

ListNode* insert_last(ListNode* head, int data){
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    node->data = data;
    if(head == NULL){
        head = node;
        node->link = head;
    }else{
        node->link = head->link;
        head->link = node;
        head = node; // head의 위치만 바꿔서 새로운 노드가 마지막 노드가 됨.
    }

    return head;
}

void print_list(ListNode* head){
    ListNode* p;
    if(head == NULL) return;
    p = head->link;
    do{
        printf("%d->", p->data);
        p = p->link;
    }while (p != head->link);
}

int main(){
    ListNode *head = NULL;
    head = insert_last(head,20);
    head = insert_last(head,30);
    head = insert_last(head,40);
    head = insert_last(head,50); 
    head = insert_first(head,10);
    print_list(head); //head는 50
    printf("\n%d", head->data);
    return 0;
}