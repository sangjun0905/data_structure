#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode{
    int data;
    struct ListNode *link;
} ListNode;

typedef struct ListType{
    int size;
    ListNode *head;
    ListNode *tail;
} ListType;

ListType* create_ListType(){
    ListType *plist =(ListType*)malloc(sizeof(ListType));
    plist->head = plist->tail = NULL;
    plist->size = 0;
    return plist;
}

void insert_last(ListType *plist, int value){
    ListNode *temp =(ListNode*)malloc(sizeof(ListNode));
    temp->data = value;
    temp->link = NULL;

    if (plist->tail == NULL) {  // 리스트가 비어 있을 때
        plist->head = plist->tail = temp;  // 헤드와 테일 모두 새 노드를 가리킴.
    } else {  // 리스트에 이미 노드가 있을 때
        plist->tail->link = temp;  // 테일 노드의 link를 새 노드로 설정
        plist->tail = temp;  // 새 노드를 테일로 설정
    }

    plist->size++;
}

ListType* alternate(ListType *plist1, ListType* plist2, ListType* plist3){
    ListNode* p1 = plist1->head;
    ListNode* p2 = plist2->head;
    
    int i=1;
    if(plist3->head == NULL){
        insert_last(plist3, p1->data);
        p1 = p1->link;
        i++;
    }
    for(ListNode* p = plist3->head;     p1 != NULL && p2 != NULL; p=p->link){
        if(i%2 == 1){
            insert_last(plist3, p1->data);
            p1 = p1->link;
        }
        else if(i%2 == 0){
            insert_last(plist3, p2->data);
            p2 = p2->link;
        }
        i++;
    }

    for(;p1 != NULL; p1 = p1->link){
        insert_last(plist3, p1->data);
    }
    for(;p2 != NULL; p2 = p2->link){
        insert_last(plist3, p2->data);
    }

    return plist3;
}

void print_list(ListNode *head){ // 리스트의 모든 항목 출력 함수
    for(ListNode *p = head; p != NULL; p = p->link){
        printf("%d->",p->data);
    }
    printf("NULL \n");
}


int main(){
    ListType *plist1 = create_ListType();
    ListType *plist2 = create_ListType();
    ListType *plist3 = create_ListType();

    for(int i=0; i<5; i++){
        insert_last(plist1, i+1); // 1 2 3 4 5
    }

    for(int i=0; i<8; i++){
        insert_last(plist2, i+10); // 10 11 12 13 14 15 16 17
    }

    alternate(plist1, plist2, plist3);

    print_list(plist3->head);
    
    return 0;
}