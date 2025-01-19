// 연결 스택은 헤드 포인터가 top이 된다.
// 삽입 연산 = 첫번째 노드로 삽입.

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct StackNode {
    int data;
    struct StackNode* link;
} StackNode;

typedef struct{
    StackNode *top;
} LinkedStackType;

void init(LinkedStackType *s){
    s->top = NULL;
}

int is_empty(LinkedStackType *s){
    return (s->top == NULL);
}

int is_full(LinkedStackType *s){
    return 0;
}

void push(LinkedStackType *s, int item){
    StackNode *temp = (StackNode*)malloc(sizeof(StackNode));
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
}

void print_stack(LinkedStackType *s){
    for(StackNode *p = s->top; p != NULL; p = p->link){
        printf("%d->", p->data);
    }
    printf("NULL \n");
}

int pop(LinkedStackType *s){
    if(is_empty(s)){
        fprintf(stderr, "공백입니다\n");
        exit(1);
    }
    else{
        StackNode *temp =s->top;
        int data = temp->data;
        s->top = s->top->link;
        free(temp);
        return data;        
    }
}

int peek(LinkedStackType *s){
    if(is_empty(s)){
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    }
    else{
        return s->top->data;
    }
}


int main(){
    LinkedStackType s;
    init(&s);
    push(&s,1); print_stack(&s); //top(head)는 1;
    push(&s,2); print_stack(&s); //top(head)는 2;
    push(&s,3); print_stack(&s); //top(head)는 3;
    pop(&s); print_stack(&s);
    pop(&s); print_stack(&s);
    pop(&s); print_stack(&s);
    return 0;
}