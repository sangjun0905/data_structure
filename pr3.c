#include <stdio.h>



typedef struct{
    int*data;
    int capacity;
    int top;
} stack;

void init(stack *s){
    s->top = -1;
    s-> capacity = 1;
    s->data = (int*)malloc(s->capacity*sizeof(int));
}

void push(stack *s, int item){
    s->top++; s->capacity++;
    s->data = (int*)realloc(s->data,s->capacity*sizeof(int));
    s->data[s->top] = item;
}

int pop(stack *s){
    return s->data[(s->top)--];
}

int main(){
    stack s;
    char Case[] = "((())(()))"; 
    init(&s);
    for(int i=0;i<strlen(Case);i++){
        if(Case[i]=='('){
            printf("%d ",s.capacity);
            push(&s,s.capacity);
        }
        else {
            printf("%d", pop(&s));
        }
    }
    printf("%d", s.data[2]);
    free(s.data);
    return 0;
}