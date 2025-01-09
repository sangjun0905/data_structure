#include <stdio.h>
#include <stdlib.h>

#define  MAX_STACK_SIZE 100 
typedef int element;
typedef struct{
    element *data;
    int capacity;
    int top;
} StackType; // 앞선 두개의 프로그램은 top과 stack 이 전역으로 선언되므로 다양한 스택을 사용하기에 부적절하다. 때문에 여러개의 스택을 만들기 위해 위의 방법을 사용한다.

//typedef int element; //데이터의 자료형
// *** 동적 배열 스택 초기화 함수
void init_stack(StackType *s)
{
    s->top=-1; // 각 스택에서 값의 초기화를 받으려면 사용해야한다.
    s->capacity=1;
    s->data=(element *)malloc(s->capacity*sizeof(element));
}
//공백 상태 검출 함수
int is_empty(StackType *s)
{
    return (s->top==-1);
}
//포화 상태 검출 함수
int is_full(StackType *s)
{
    return (s->top==MAX_STACK_SIZE-1);
}
//삽입 함수
void push(StackType *s,element item) // 동적 할당시 스택의 크기를 두배로 요구한다
{
    if(is_full(s))
    {
        s->capacity*=2;
        s->data=(element *)realloc(s->data,s->capacity*sizeof(element));
        fprintf(stderr,"스택 포화에러");//printf 의 출력은 버퍼에 저장된 후 출력되지만 frintf의 경우엔 버퍼에 저장되지 않고 출력되므로 실행중 프로그램이 죽어도 출력가능
        return;
    }
    else s->data[++(s->top)]=item; // 스택에 값이 입력되기 위해선 공간을 만든 후 입력해야한다.
}
//삭제 함수
element pop(StackType *s) 
{
    if(is_empty(s))
    {
        fprintf(stderr,"스택 공백에러");
        exit(1);
    }
    else return s->data[(s->top)--]; // 스택에서 제거될 경우 값이 출력되고 삭제된다.
}
//피크 함수
element peek(StackType *s)
{
    if(is_empty(s))
   {
        fprintf(stderr,"스택 공백에러");
        exit(1);
    }
    else return s->data[s->top];
}

int main() {
    StackType s;

    init_stack(&s);
    push(&s,1);
    push(&s,2);
    push(&s,3);
    printf("%d\n",peek(&s));
    printf("%d\n",pop(&s));
    printf("%d\n",pop(&s));
    printf("%d\n",pop(&s));
    free(s.data);
    return 0;
}