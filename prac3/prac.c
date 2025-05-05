#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

// ---------------------- 입력 큐 정의 ----------------------
typedef struct TokenNode {
    char data[100];
    struct TokenNode* next;
} TokenNode;

typedef struct {
    TokenNode* front;
    TokenNode* rear;
} TokenQueue;

TokenQueue globalQueue = {0}; // 전역 큐 (이전 입력 보존)

// ---------------------- 큐 함수 ----------------------
void enqueue(TokenQueue* q, const char* str) {
    TokenNode* newNode = (TokenNode*)malloc(sizeof(TokenNode));
    strncpy(newNode->data, str, 99);
    newNode->data[99] = '\0';
    newNode->next = NULL;

    if (!q->rear) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

char* dequeue(TokenQueue* q) {
    if (!q->front) return NULL;
    TokenNode* temp = q->front;
    char* result = strdup(temp->data);
    q->front = temp->next;
    if (!q->front) q->rear = NULL;
    free(temp);
    return result;
}

int isEmpty(TokenQueue* q) {
    return q->front == NULL;
}

// ---------------------- my_scanf 구현 ----------------------
int my_scanf(const char* format, ...) {
    // 입력이 필요할 때만 입력 받음
    if (isEmpty(&globalQueue)) {
        char input[1024];
        if (!fgets(input, sizeof(input), stdin)) return -1;

        char* token = strtok(input, " \t\n");
        while (token) {
            enqueue(&globalQueue, token);
            token = strtok(NULL, " \t\n");
        }
    }

    va_list args;
    va_start(args, format);

    const char* p = format;
    int count = 0;

    while (*p) {
        if (isspace(*p)) {
            ++p;
            continue;
        }

        if (*p == '%') {
            ++p;
            char* token = dequeue(&globalQueue);
            if (!token) break;

            switch (*p) {
                case 'd': {
                    int* iptr = va_arg(args, int*);
                    *iptr = atoi(token);
                    count++;
                    break;
                }
                case 'f': {
                    float* fptr = va_arg(args, float*);
                    *fptr = (float)atof(token);
                    count++;
                    break;
                }
                case 's': {
                    char* sptr = va_arg(args, char*);
                    strncpy(sptr, token, 99);
                    sptr[99] = '\0';
                    count++;
                    break;
                }
                default:
                    break;
            }
            free(token);
        } else {
            ++p; // 포맷에 있는 일반 문자 무시
        }
    }

    va_end(args);
    return count;
}

// ---------------------- 테스트 main ----------------------
int main() {
    int i, j;
    float f;
    char str[100];

    printf("입력 (예: 123 4.56 hello 999): ");
    int count1 = my_scanf("%d %f %s", &i, &f, str);

    printf("읽은 개수: %d\n", count1);
    printf("i = %d, f = %.2f, str = %s\n", i, f, str);

    printf("my_scanf 재호출 (남은 토큰 자동 사용):\n");
    int count2 = my_scanf("%d", &j);

    printf("읽은 개수: %d\n", count2);
    printf("j = %d\n", j);

    return 0;
}
