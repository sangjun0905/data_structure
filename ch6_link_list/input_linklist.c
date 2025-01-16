#include <stdio.h>
#include<stdlib.h>


typedef struct ListNode{
    int data;
    struct ListNode *link;
} ListNode;

typedef struct ListType{
    int size;
    ListNode *head;
    ListNode *tail;
} ListType;

ListType* create(){
    ListType *plist = (ListType*)malloc(sizeof(ListType));
    plist->size = 0;
    plist->head = plist->tail = NULL;
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

void print_list(ListType *plist){
    
    for(ListNode *p = plist->head; p != NULL; p = p->link){
        printf(" %d ", p->data);
    }
    printf("\n");
}

int search_list(ListType* plist, int x){
    int cnt = 1;
    for(ListNode *p = plist->head; p != NULL; p = p->link){
        if(p->data == x){
            return cnt;
        }
        cnt++; 
    }
}

ListType* delete_odd(ListType *plist){
    if(plist->size%2 == 0){
        for(ListNode *i = plist->head; i != NULL; i = i->link){
        i->link = (i->link)->link;
        }
    }
    else {
        for(ListNode *i = plist->head; i->link != NULL; i = i->link){
        i->link = (i->link)->link;       
        }
    }

    return plist;
}

int main(){
    int num;

    ListType* plist = create();


    printf("입력할 숫자 개수:");
    scanf("%d", &num);

    for(int i = 0; i < num; i++){
        int value;
        printf("숫자 입력: ");
        scanf("%d", &value);
        insert_last(plist, value);
    }

    print_list(plist);

    printf("연결된 노드의 개수: %d", plist->size);

    int x;
    printf("찾을 숫자를 말해: ");
    scanf("%d", &x);

    printf("%d번째에 있어.", search_list(plist, x));


    delete_even(plist);

    print_list(plist);

    return 0;
    
}



