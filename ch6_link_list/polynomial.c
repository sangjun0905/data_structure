#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode{
    int coef; // 계수
    int expon; // 차수
    struct ListNode *link;
} ListNode;

typedef struct  ListType{
    int size;
    ListNode *head;
    ListNode *tail;  
} ListType;

void error(char *message){
    fprintf(stderr, "%s\n", message);
    exit(1);
}

ListType* create(){
    ListType *plist = (ListType*)malloc(sizeof(ListType));
    plist->size = 0;
    plist->head = plist->tail = NULL;
    return plist;
}

void insert_last(ListType *plist, int coef, int expon){ //헤더노드에 있는 마지막 노드의 주소를 바로 이용
    ListNode* temp = (ListNode *)malloc(sizeof(ListNode));
    if(temp == NULL) error("memorry allocation error\n");
    temp->coef = coef;
    temp->expon = expon;
    temp->link = NULL;
    if(plist->tail == NULL){
        plist->head = plist->tail = temp;
    }
    else{
        plist->tail->link = temp;
        plist->tail = temp;
    }
    plist->size++;
}

void poly_add(ListType* plist1, ListType* plist2, ListType* plist3){ // plist 는 다항식을 의미함
    ListNode* a = plist1->head;
    ListNode* b = plist2->head;

    int sum;

    while (a && b){
        if(a->expon == b->expon){
            sum = a->coef + b->coef;
            if(sum != 0) insert_last(plist3, sum, a->expon);
            a=a->link; b=b->link;
        }
        else if(a->expon > b->expon){
            insert_last(plist3, a->coef, a->expon);
            a = a->link;
        }
        else{
            insert_last(plist3, b->coef, b->expon);
            b = b->link;
        }
    }

    // a와 b 중 하나가 끝나면 남아있는 항들을 모두 결과 다항식으로 복사
    for(;a != NULL; a = a->link){
        insert_last(plist3, a->coef, a->expon);
    }
    for(;b != NULL; b = b->link){
        insert_last(plist3, b->coef, b->expon);
    }
}

void poly_print(ListType* plist){
    ListNode *p = plist->head;

    printf("polynomial = ");
    for(; p != NULL; p = p->link){
        printf("%dx^%d + ", p->coef, p->expon);
    }
    printf("\n");
}

