#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_WORDS 50000

typedef struct {
    char word[100];
    char mean[200];
    struct WordNode* left;
    struct WordNode* right;
} WordNode;


WordNode wordArrayByqsort[MAX_WORDS];
int wordCount = 0;

WordNode* createNode(char tempWord[], char tempMean[]) {
    WordNode* temp = (WordNode*)malloc(sizeof(WordNode));
    if (!temp) {
        perror("메모리 할당 실패");
        exit(1);
    }
    strncpy(temp->word, tempWord, sizeof(temp->word) - 1);
    strncpy(temp->mean, tempMean, sizeof(temp->mean) - 1);
    temp->word[sizeof(temp->word) - 1] = '\0';
    temp->mean[sizeof(temp->mean) - 1] = '\0';
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

int compareLoweredWord(const char* a, const char* b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b))
            return tolower((unsigned char)*a) - tolower((unsigned char)*b);
        a++; b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

WordNode* insertTree(WordNode* root, WordNode temp) {
    if (root == NULL) {
        return createNode(temp.word, temp.mean);
    }

    if (compareLoweredWord(temp.word, root->word) < 0) {
        root->left = insertTree(root->left, temp);
    } else {
        root->right = insertTree(root->right, temp);
    }
    return root;
}

WordNode* search(WordNode* root, const char* target, int* comparedCnt) {
    if (root == NULL) {
        printf("그런 단어는 존재하지 않습니다.\n");
        exit(1);
        return NULL;
    }
    (*comparedCnt)++;

    if (!compareLoweredWord(target, root->word)) { // 두 단어의 차이가 0인 경우 탐색 완료
        return root;
    } else if (compareLoweredWord(target, root->word) < 0) {
        return search(root->left, target, comparedCnt);
    } else if (compareLoweredWord(target, root->word) > 0) {
        return search(root->right, target, comparedCnt);
    }
}


WordNode* readFile(const char* filename) {
    FILE* fp = fopen(filename, "r");
    WordNode* NotSorted_BSTree = NULL;

    if (!fp) {
        perror("파일 열기 실패");
        exit(1);
    }

    char line[300];

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';
        char* sep = strstr(line, " :");
        if (!sep) continue;

        *sep = '\0';
        char* word = line;
        char* mean = sep + 2;

        if (strlen(word) != 0 && strlen(mean) != 0) {
            WordNode temp;
            strncpy(temp.word, word, sizeof(temp.word) - 1);
            strncpy(temp.mean, mean, sizeof(temp.mean) - 1);
            temp.word[sizeof(temp.word) - 2] = '\0';
            temp.mean[sizeof(temp.mean) - 1] = '\0';
            

            if(NotSorted_BSTree == NULL) {
                NotSorted_BSTree = createNode(temp.word, temp.mean);
            } else{
                insertTree(NotSorted_BSTree, temp);
            }
            wordCount++;
        }
    }
    printf("파일에서 읽을 때 센 단어의 수: %d\n", wordCount);
    fclose(fp);

    return NotSorted_BSTree;
}

int countNode(WordNode* root) {
    if (root == NULL) return 0;

    return 1 + countNode(root->left) + countNode(root->right);
}

int treeHeight(WordNode* root) {
    if (root == NULL) return 0;

    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int main() {
    WordNode* NotSorted_BSTree = (WordNode*)malloc(sizeof(WordNode*));
    NotSorted_BSTree = readFile("randdict_utf8.TXT");
    int index = 1;
    char target[100];

    printf("트리의 노드 수 : %d\n", countNode(NotSorted_BSTree));
    printf("트리의 높이 : %d\n", treeHeight(NotSorted_BSTree));
    while (1) {
        printf("단어 입력 : ");
        fgets(target, sizeof(target), stdin);
        target[strcspn(target, "\n")] = '\0';

        int comparedCnt = 0;

        WordNode* targetWordNode = search(NotSorted_BSTree, target, &comparedCnt);
        printf("(탐색 횟수:%d) %s\t%s\n", comparedCnt, targetWordNode->word, targetWordNode->mean);
    }

    return 0;
}

//트리 노드 수, 높이 구하기