#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// 중위 선행자: 중위 순회에서 현재 노드 이전에 방문한 노드
// 중위 후속자: 중위 순회에서 현재 노드 다음으로 방문할 노드

typedef struct TreeNode{
    int data;
    struct TreeNode *left, *right;
    int is_thread; //만약 오른쪽 링크가 스레드이면 TRUE
} TreeNode;

// is thread가 True 이면 right는 중위 후속자이고 false이면 오른쪽 자식을 가리키는 포인터가 된다.

TreeNode *find_successor(TreeNode *p){
    // q는 p의 오른쪽 포인터
    TreeNode *q = p->right;;
    // 만약 오른쪽 포인터가 NULL이거나 스레드이면 오른쪽 포인터를 반환
    if(q == NULL || p->is_thread == true) return q;

    // 만약 오른쪽 자식이면 다시 가장 왼쪽 노드로 이동
    while (q->left != NULL) q = q->left;
    return q;
}

void thread_inorder(TreeNode *t){
    TreeNode *q;
    q = t;
    while(q->left) q = q->left; // 가장 왼쪽 노드로 간다.
    do{
        printf("%c ->", q->data); //데이터 출력
        q = find_successor(q);  // 후속자 함수 호출
    } while(q);                 // NULL 아니면
}