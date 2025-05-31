#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_WORDS 50000

typedef struct WordNode {
    char word[100];
    char mean[200];
    struct WordNode* left;
    struct WordNode* right;
} WordNode;

typedef struct Word {
    char word[100];
    char mean[200];
} Word;


WordNode wordArrayByqsort[MAX_WORDS];
Word words[MAX_WORDS];
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

WordNode* insertTree(WordNode* root, WordNode* temp) {
    if (root == NULL) {
        return createNode(temp->word, temp->mean);
    }

    if (compareLoweredWord(temp->word, root->word) < 0) {
        root->left = insertTree(root->left, temp);
    } else {
        root->right = insertTree(root->right, temp);
    }

    return root;
}

int sortLoweredWord(const void* a, const void* b) {
    const Word* wa = (const Word*)a;
    const Word* wb = (const Word*)b;
    return compareLoweredWord(wa->word, wb->word);
}

WordNode* search(WordNode* root, const char* target, int* comparedCnt) {
    if (root == NULL) {
        printf("그런 단어는 존재하지 않습니다.\n");
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


void* readFile(const char* filename) {
    FILE* fp = fopen(filename, "r");

    if (!fp) {
        perror("파일 열기 실패");
        exit(1);
    }

    char line[300];
    int i = 0;

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';
        char* sep = strstr(line, " :");
        if (!sep) continue;

        *sep = '\0';
        char* word = line;
        char* mean = sep + 2;

        if (strlen(word) != 0 && strlen(mean) != 0) {
            strncpy(words[i].word, word, sizeof(words[i].word) - 1);
            strncpy(words[i].mean, mean, sizeof(words[i].mean) - 1);
            words[i].word[sizeof(words[i].word) - 2] = '\0';
            words[i].mean[sizeof(words[i].mean) - 1] = '\0';

            i++;
            wordCount++;
        }
    }
    qsort(words, i, sizeof(Word), sortLoweredWord);
    printf("파일에서 읽을 때 센 단어의 수: %d\n", wordCount);
    fclose(fp);
}

void sortedArrayToTree(WordNode* root, Word words[], int start, int end) {
    if (start > end) return;

    int mid = (start + end) / 2;

    WordNode* node = createNode(words[mid].word, words[mid].mean);
    insertTree(root, node);

    sortedArrayToTree(root, words, start, mid - 1);
    sortedArrayToTree(root, words, mid + 1, end);
}

int countNode(WordNode* root) {
    if (root == NULL) { 
        return 0;
    }
        int leftCnt = countNode(root->left); 
        int rightCnt = countNode(root->right); 
    return 1 + leftCnt + rightCnt;
}

int treeHeight(WordNode* root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int main() {
    WordNode* Sorted_BSTree = NULL;
    
    readFile("randdict_utf8.TXT");
    int index = 1;
    char target[100];

    int mid = (0 + wordCount - 1) / 2;
    Sorted_BSTree = createNode(words[mid].word, words[mid].mean);

    sortedArrayToTree(Sorted_BSTree, words, 0, mid - 1);
    sortedArrayToTree(Sorted_BSTree, words, mid + 1, wordCount - 1);

    if (!Sorted_BSTree) {
    printf("트리 생성 실패\n");
    return 1;
    }

    printf("root 단어(중앙값): %s\n", Sorted_BSTree->word);

    printf("트리의 노드 수 : %d\n", countNode(Sorted_BSTree));
    printf("트리의 높이 : %d\n", treeHeight(Sorted_BSTree));
    while (1) {
        int comparedCnt = 0;

        printf("단어 입력 : ");
        fgets(target, sizeof(target), stdin);
        target[strcspn(target, "\n")] = '\0';

        WordNode* targetWordNode = search(Sorted_BSTree, target, &comparedCnt);
        printf("(탐색 횟수:%d) %s\t%s\n", comparedCnt, targetWordNode->word, targetWordNode->mean);
    }

    return 0;
}