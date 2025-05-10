#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_WORDS 50000
#define INDEX_SIZE 221  // 48380의 제곱근 = 219.XX

typedef struct Node{
    int index;
    char word[100];
    char mean[200];
    struct Node* link;
} Node;

// 전역 변수 설정
Node* dividedSection[INDEX_SIZE];   // 분할 탐색용 대표 노드
char* wordArray[MAX_WORDS];      // 단어 랜덤 생성을 위해 단어 배열화
int wordCount = 0;               // 총 단어 수

int compareLoweredWord(char* a, char* b){
    while(*a && *b){
        if(tolower((unsigned char)*a) < tolower((unsigned char)*b)) return -1;
        else if(tolower((unsigned char)*a) > tolower((unsigned char)*b)) return 1;
        a++; b++;
    }
    
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

Node* createNode(char* word, char* mean) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(1);
    }
    strncpy(newNode->word, word, sizeof(newNode->word) - 1);
    strncpy(newNode->mean, mean, sizeof(newNode->mean) - 1);
    newNode->word[sizeof(newNode->word) - 1] = '\0';
    newNode->mean[sizeof(newNode->mean) - 1] = '\0';
    newNode->index = 0;
    newNode->link = NULL;
    return newNode;
}

void insertSortedNode(Node** phead, char* word, char* mean){
    Node* newNode = createNode(word, mean);
    if (*phead == NULL || compareLoweredWord(word, (*phead)->word) < 0) {
        newNode->link = *phead;
        *phead = newNode;
        return;
    }

    Node* curr = *phead;
    while (curr->link && compareLoweredWord(word, curr->link->word) > 0) { //head를 타며 위치 탐색, curr의 다음 노드와 비교했을 때 word가 앞이면 삽입
        curr = curr->link;
    }
    newNode->link = curr->link;
    curr->link = newNode;

    wordArray[wordCount++] = newNode->word;
}

void assignIndex(Node* head) {
    int idx = 1;
    while (head) {
        head->index = idx++;
        head = head->link;
    }
}

void divideIndex(Node* head) {
    Node* curr = head;
    int count = 1;   
    int idx = 0;

    while (curr && idx < INDEX_SIZE) {
        if ((count - 1) % 220 == 0) {
            dividedSection[idx++] = curr;
        }
        curr = curr->link;
        count++;
    }

    while (idx < INDEX_SIZE) {  // 남는 공간 초기화
        dividedSection[idx++] = NULL;
    }
}

Node* sequentialSearch(Node* head, char* object) {
    while (head) {
        if (compareLoweredWord(head->word, object) == 0)
            return head;
        head = head->link;
    }
    return NULL;
}

Node* fastSearch(char* object) {
    for (int i = 0; i < INDEX_SIZE - 1; i++) {
        Node* startingPoint = dividedSection[i];
        Node* nextStartingPoint = dividedSection[i + 1];

        if (nextStartingPoint == NULL)
            break;

        if (compareLoweredWord(object, nextStartingPoint->word) < 0) {
            Node* curr = startingPoint;
            while (curr && curr != nextStartingPoint) {
                if (compareLoweredWord(curr->word, object) == 0)
                    return curr;
                curr = curr->link;
            }
            return NULL;
        }
    }

    // 마지막 분할 범위 탐색 추가
    Node* curr = dividedSection[INDEX_SIZE - 1];
    while (curr) {
        if (compareLoweredWord(curr->word, object) == 0)
            return curr;
        curr = curr->link;
    }

    return NULL;
}

void freeList(Node* head) {
    while (head) {
        Node* next = head->link;
        free(head);
        head = next;
    }
}

void readFile(char* fileName, Node **phead){ //파일을 줄별로 읽고, 줄을 단어와 뜻으로 분리
    char line[300];
    FILE* fp = fopen(fileName, "r");

    if (!fp) {
        perror("파일 열기 실패");
        exit(1);
    }

    printf("파일 읽는중\n");
    while (fgets(line, sizeof(line), fp)) {
       
        line[strcspn(line, "\n")] = '\0';

        char* sep = strstr(line, " : "); // 분리되는 부분 주소 저장

        *sep = '\0';    // 분리지점 기준으로 단어와 뜻 분리
        char* word = line;
        char* mean = sep + 3; 

        if (strlen(word) > 0 && strlen(mean) > 0) {
            insertSortedNode(phead, word, mean);
        }   
    }

    fclose(fp);    
}

void testSearchPerformance(Node* head) {
    printf("test 진입\n");
    char* objectArray[10000];
    for (int i = 0; i < 10000; i++) {
        int r = rand() % wordCount;
        objectArray[i] = wordArray[r];
    }

    clock_t start1 = clock();
    printf("순차 탐색중\n");
    for (int i = 0; i < 10000; i++)
        sequentialSearch(head, objectArray[i]);
    clock_t end1 = clock();
    double seqTime = (double)(end1 - start1) / CLOCKS_PER_SEC;

    clock_t start2 = clock();
    printf("분할 탐색중\n");
    for (int i = 0; i < 10000; i++)
        fastSearch(objectArray[i]);
    clock_t end2 = clock();
    double fastTime = (double)(end2 - start2) / CLOCKS_PER_SEC;

    printf("\n[탐색 성능 비교 - 10,000회]\n");
    printf("순차 탐색 시간: %.4f초\n", seqTime);
    printf("빠른 탐색 시간: %.4f초\n", fastTime);
}

int main() {
    Node* head = NULL;
    srand((unsigned int)time(NULL));  

    readFile("randdict_utf8.TXT", &head);
    assignIndex(head);
    divideIndex(head);

    testSearchPerformance(head);

    freeList(head);
    return 0;
}