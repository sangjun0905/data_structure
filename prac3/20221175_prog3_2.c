#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 노드 구조체
typedef struct Node {
    char word[100];
    char meaning[300];
    struct Node* next;
} Node;

// 노드 생성
Node* createNode(const char* word, const char* meaning) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    strncpy(newNode->word, word, 99);
    newNode->word[99] = '\0';
    strncpy(newNode->meaning, meaning, 299);
    newNode->meaning[299] = '\0';
    newNode->next = NULL;
    return newNode;
}

// 연결 리스트 삽입 (맨 앞 삽입 방식)
void insertFront(Node** head, const char* word, const char* meaning) {
    Node* newNode = createNode(word, meaning);
    newNode->next = *head;
    *head = newNode;
}

// 파일 읽고 리스트 생성
void loadFile(const char* filename, Node** head) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("파일 열기 실패");
        exit(1);
    }

    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        char* delim = strchr(line, ':');
        if (!delim) continue;

        *delim = '\0'; // ':' → '\0'
        char* word = line;
        char* meaning = delim + 1;

        // 줄바꿈 제거
        word[strcspn(word, "\n")] = '\0';
        meaning[strcspn(meaning, "\n")] = '\0';

        insertFront(head, word, meaning);
    }

    fclose(fp);
}

// 리스트를 두 개로 나누는 함수 (pivot 기준)
void partition(Node* head, const char* pivot,
               Node** less, Node** equal, Node** greater) {
    while (head) {
        Node* next = head->next;
        if (strcmp(head->word, pivot) < 0) {
            head->next = *less;
            *less = head;
        } else if (strcmp(head->word, pivot) > 0) {
            head->next = *greater;
            *greater = head;
        } else {
            head->next = *equal;
            *equal = head;
        }
        head = next;
    }
}

// 리스트 병합
Node* concatenate(Node* a, Node* b) {
    if (!a) return b;
    Node* temp = a;
    while (temp->next) temp = temp->next;
    temp->next = b;
    return a;
}

// 연결 리스트 퀵 정렬
Node* quickSort(Node* head) {
    if (!head || !head->next) return head;

    Node* less = NULL;
    Node* equal = NULL;
    Node* greater = NULL;

    partition(head, head->word, &less, &equal, &greater);

    less = quickSort(less);
    greater = quickSort(greater);

    return concatenate(concatenate(less, equal), greater);
}

void searchWord(Node* head, const char* target) {
    int index = 1;
    while (head) {
        if (strcmp(head->word, target) == 0) {
            printf("찾음: %d. %s : %s\n", index, head->word, head->meaning);
            return;
        }
        head = head->next;
        index++;
    }
    printf("단어 '%s' 을(를) 찾을 수 없습니다.\n", target);
}

// 리스트 출력 (노드 번호 포함)
void printList(Node* head) {
    int index = 1;
    while (head) {
        printf("%d. %s : %s\n", index++, head->word, head->meaning);
        head = head->next;
    }
}

// 메모리 해제
void freeList(Node* head) {
    while (head) {
        Node* next = head->next;
        free(head);
        head = next;
    }
}

// 메인 함수
int main() {
    Node* head = NULL;

    loadFile("randdict_utf8.TXT", &head);
    head = quickSort(head);

    char input[100];
    while (1) {
        printf("찾고 싶은 단어를 입력하세요 (종료는 'exit'): ");
        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = '\0'; // 개행 제거

        if (strcmp(input, "exit") == 0) break;

        searchWord(head, input);
    }

    freeList(head);
    return 0;
}
