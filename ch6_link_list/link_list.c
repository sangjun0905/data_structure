#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode{
    int data;
    struct ListNode *link;
} ListNode;


// //헤드 값 저장
//     head->data = 10;
//     head->link = NULL;

//     //노드 생성
//     ListNode *p;
//     p=(ListNode *)malloc(sizeof(ListNode));
//     p->data = 20;
//     p->link = NULL;

//     //연결
//     head->link = p;


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

ListNode* delete(ListNode *head, ListNode* pre){ // 리스트의 중간 항목을 삭제하는 함수
    ListNode *removed;
    removed = pre->link;
    pre->link = removed->link;
    free(removed);
    return head;
}

void print_list(ListNode *head){ // 리스트의 모든 항목 출력 함수
    for(ListNode *p = head; p != NULL; p = p->link){
        printf("%d->",p->data);
    }
    printf("NULL \n");
}

ListNode* serch_list(ListNode *head, int x){ // 특정 값을 탐색
    ListNode *p = head;

    while(p!=NULL){
        if(p->data == x) return p;
        p=p->link;
    }

    return NULL; // 탐색 실패패
}

ListNode* merge_list(ListNode *head1, ListNode *head2){ // 연결 리스트 병합

    for(ListNode *p = head1; p != NULL ; p=p->link){
        if(p->link == NULL){
            p->link = head2;
            break;
        }
    }

    return head1;
}



ListNode* reverse(ListNode *head) {
    ListNode *prev = NULL;  // 이전 노드, prev에 역순으로 저장
    ListNode *curr = head; // 현재 노드
    ListNode *next = NULL; // 다음 노드
    
    while (curr != NULL) {
        next = curr->link;  // 다음 노드 저장
        curr->link = prev;  // 현재 노드의 링크를 이전 노드로 변경
        prev = curr;        // 이전 노드를 현재 노드로 이동
        curr = next;        // 현재 노드를 다음 노드로 이동
    }
    
    


    return prev; // 새로운 헤드 반환
}





int main(){
    ListNode *head = NULL;
    ListNode *head2 = NULL;
    
    for(int i = 0; i < 5; i++){
        head =  insert_first(head, i);
    }
    print_list(head);


    for(int i = 5; i < 10; i++){
        head2 = insert_first(head2, i);
    }
    print_list(head2);


    merge_list(head, head2);

    print_list(head);

    printf("찾았다: %d\n", (serch_list(head, 7))->data);

    printf("역순: "); print_list(reverse(head));
    for(int i = 0; i < 10; i++){
        head = delete_first(head);
        print_list(head);
    }

    return 0;
}
