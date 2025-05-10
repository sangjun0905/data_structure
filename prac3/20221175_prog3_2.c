#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node{
    int index;
    char word[100];
    char mean[200];
    struct Node* link;
} Node;

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
}

void assignIndex(Node* head) {
    int idx = 1;
    while (head) {
        head->index = idx++;
        head = head->link;
    }
}

void searchWord(Node* head, char* object){
    Node* curr = head;
    while(curr){
        if(compareLoweredWord(curr->word, object) == 0){
            printf("탐색 결과: (%d) %s : %s\n", curr->index, curr->word, curr->mean);
            return;
        }
        curr = curr->link;
    }
    printf("대상이 존재하지 않음.");
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

int main(){
    Node* head = NULL;

    readFile("randdict_utf8.TXT", &head);

    assignIndex(head);

    char input[100];
    while (1) {
        printf("탐색 단어 입력: ");
        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = '\0';

        searchWord(head, input);
    }
    
    freeList(head);

    return 0;
}