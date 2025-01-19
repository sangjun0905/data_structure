#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct DListNode{
    char data[100];
    struct DListNode *llink;
    struct DListNode *rlink;
} DListNode;

DListNode* current;

void init(DListNode* phead){
    phead->llink = phead;
    phead->rlink = phead;
}

void dinsert(DListNode *before, char data[]){
    DListNode *new = (DListNode*)malloc(sizeof(DListNode));
    strcpy(new->data, data);
    new->llink = before;
    new->rlink = before->rlink;
    before->rlink->llink = new;
    before->rlink = new;
}

void ddelete(DListNode *head, DListNode *removed){
    if(removed == head) return;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed); // 할당 해제 잊지 말기!!!!!!!!
}

void print_dlist(DListNode *phead){
    DListNode* p;
    for(p = phead->rlink; p != phead; p = p->rlink){
        printf("<-| |%s| |->", p->data);
    }
    printf("\n");
}

int main(){
    char ch;
    DListNode *head = (DListNode*)malloc(sizeof(DListNode));
    init(head);

    dinsert(head, "Mamamia");
    dinsert(head, "Dancing Queen");
    dinsert(head, "See You Again");

    current = head->rlink;

    print_dlist(head);

    do{
        printf("\n 명령어 입력(<,>,q): ");
        ch = getchar();
        if(ch == '<'){
            current = current->llink;
            if(current == head)
            current = current->llink;
        }
        else if(ch == '>'){
            current = current->rlink;
            if(current == head)
            current = head->rlink;
        }
        print_dlist(head);
        printf("현재 곡: %s\n", current->data);
        getchar();
    }while (ch != 'q');
    
    free(head);
    free(current);

    return 0;
}