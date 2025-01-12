#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode{
    int data;
    struct ListNode *link;
} ListNode;

ListNode* insert_first(ListNode *head, int value); //리스트의 시작 부분에 항목을 삽입하는 함수
ListNode* insert(ListNode *head, ListNode *pre, int value); // 리스트의 중간 부분에 항목을 삽입하는 함수
ListNode* delete_first(ListNode *head); // 리스트의 첫 번째 항목을 삭제하는 함수
// delete() 리스트의 중간 항목을 삭제하는 함수
// print_list() 리스트를 방문하여 모든 항목을 출력하는 함수

ListNode* insert_first(ListNode *head, int value){  //리스트의 시작 부분에 항목을 삽입하는 함수
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

ListNode* insert(ListNode *head, ListNode *pre, int value){  // 리스트의 중간 부분에 항목을 삽입하는 함수
    ListNode *p = (ListNode *)malloc(sizeof(ListNode)); // 새 노드 생성
    p->data = value;
    p->link = pre->link;
    pre->link = p;
    return head;
}

ListNode* delete_first(ListNode *head){  // 리스트의 첫 번째 항목을 삭제하는 함수
    ListNode *removed; 
    if(head == NULL) return NULL;
    removed = head;  // removed에 동적 할당된 head를 복사
    head = removed->link; // 기존 head의 link를 head의 값에 넣음으로써 한칸 삭제
    free(removed); // 복사를 위해 만들어둔 removed 메모리 할당 해제
    return head;
}

ListNode* delete(ListNode *head, ListNode* pre){
    
}


ListNode *head = NULL;


int main(){
    head = (ListNode *)malloc(sizeof(ListNode));

    //헤드 값 저장
    head->data = 10;
    head->link = NULL;

    //노드 생성
    ListNode *p;
    p=(ListNode *)malloc(sizeof(ListNode));
    p->data = 20;
    p->link = NULL;

    //연결
    head->link = p;

    return 0;
}