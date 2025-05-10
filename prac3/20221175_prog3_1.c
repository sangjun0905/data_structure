#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024

typedef struct Node {
    char data[MAX_LINE];
    struct Node* link;
} Node;

Node* front = NULL;
Node* rear = NULL;

void enqueue(const char* line) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data, line);
    newNode->link = NULL;
    if (rear) rear->link = newNode;
    else front = newNode;
    rear = newNode;
}

void dequeue(char* out) {
    if (front == NULL) return;
    strcpy(out, front->data);
    Node* temp = front;
    front = front->link;
    if (front == NULL) rear = NULL;
    free(temp);
}

int isQueueEmpty() {
    return front == NULL;
}


int my_scanf(char* format, ...) {
    static char buffer[MAX_LINE];
    static char* next = NULL; // 입력 문자열 읽어들이기

    if (!next || *next == '\0') {
        if (isQueueEmpty()) {  // 큐에 입력이 존재하지 않는 경우에 입력 받기
            if (!fgets(buffer, MAX_LINE, stdin)) return -1;
            enqueue(buffer);
        }
        dequeue(buffer);
        next = buffer;
    }

    va_list args;
    va_start(args, format);
    char* fmt = format;
    char* inp = next;
    int count = 0;

    while (*fmt) {
        if (isspace(*fmt)) {
            while (isspace(*inp)) ++inp;
            ++fmt;
            continue;
        }

        if (*fmt != '%') {
            if (*fmt++ != *inp++) break;
            continue;
        }

        ++fmt;

        int length_flag = 0; // h와 l의 개수 저장

        if (*fmt == 'h') {
            length_flag = 1;
            ++fmt;
            if (*fmt == 'h') { length_flag = 2; ++fmt; }
        } else if (*fmt == 'l') {
            length_flag = 3;
            ++fmt;
        }

        char temp[128];
        int i = 0;

        switch (*fmt) {
        case 'd': {
            while (i < 127 && (isdigit(*inp) || *inp == '-' || *inp == '+')) temp[i++] = *inp++;
            temp[i] = '\0';
            if (length_flag == 2) *va_arg(args, char*) = (char)atoi(temp);
            else if (length_flag == 1) *va_arg(args, short*) = (short)atoi(temp);
            else if (length_flag == 3) *va_arg(args, long*) = atol(temp);
            else *va_arg(args, int*) = atoi(temp);
            count++;
            break;
        }
        case 'f': {
            while (i < 127 && (isdigit(*inp) || *inp == '.' || *inp == '-' || *inp == '+')) temp[i++] = *inp++;
            temp[i] = '\0';
            if (length_flag == 3) *va_arg(args, double*) = strtod(temp, NULL);
            else *va_arg(args, float*) = (float)strtod(temp, NULL);
            count++;
            break;
        }
        case 's': {
            while (isspace(*inp)) ++inp;
            while (i < 127 && *inp && !isspace(*inp)) temp[i++] = *inp++;
            temp[i] = '\0';
            strcpy(va_arg(args, char*), temp);
            count++;
            break;
        }
        case 'c': {
            char* cptr = va_arg(args, char*);
            *cptr = *inp ? *inp++ : '\0';
            count++;
            break;
        }
        default:
            va_end(args);
            return -2; 
        }

        ++fmt;
    }

    while (isspace(*inp)) ++inp;
    next = (*inp) ? inp : NULL;

    va_end(args);
    return count;
}

int main() {
    char a;
    char b;
    short c;
    int d;  
    long e;
    float f;
    double g;
    char h[100];

    printf("입력: c, hhd, hd, d, ld, f, lf, string 순서\n");

    my_scanf("%c", &a);
    my_scanf("%hhd %hd", &b, &c);
    my_scanf("%d %ld", &d, &e);
    my_scanf("%f %lf", &f, &g);
    my_scanf("%s", h);

    printf("\n[입력 결과]\n");
    printf("char: %c\n", a);
    printf("hhd: %d\n", b);
    printf("hd: %d\n", c);
    printf("d: %d\n", d);
    printf("ld: %ld\n", e);
    printf("f: %f\n", f);
    printf("lf: %lf\n", g);
    printf("str: %s\n", h);

    return 0;
}
