#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_WORDS 50000

typedef struct {
    char word[100];
    char mean[200];
} WordEntry;

WordEntry wordArrayByInsert[MAX_WORDS];
WordEntry wordArrayByQuick[MAX_WORDS];
WordEntry wordArrayByHeap[MAX_WORDS];
WordEntry wordArrayByqsort[MAX_WORDS];
WordEntry wordArrayByBetterQsort[MAX_WORDS];
int wordCount = 0;

int compareLoweredWord(const char* a, const char* b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b))
            return tolower((unsigned char)*a) - tolower((unsigned char)*b);
        a++; b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

void swap(WordEntry* a, WordEntry* b) {
    WordEntry temp = *a;
    *a = *b;
    *b = temp;
}

void readFile(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("파일 열기 실패");
        exit(1);
    }

    char line[300];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';
        char* sep = strstr(line, " : ");
        if (!sep) continue;

        *sep = '\0';
        char* word = line;
        char* mean = sep + 3;

        if (strlen(word) > 0 && strlen(mean) > 0) {
            WordEntry temp;
            strncpy(temp.word, word, sizeof(temp.word) - 1);
            strncpy(temp.mean, mean, sizeof(temp.mean) - 1);
            temp.word[sizeof(temp.word) - 1] = '\0';
            temp.mean[sizeof(temp.mean) - 1] = '\0';

            wordArrayByInsert[wordCount] = temp;
            wordArrayByQuick[wordCount] = temp;
            wordArrayByHeap[wordCount] = temp;
            wordArrayByqsort[wordCount] = temp;
            wordArrayByBetterQsort[wordCount] = temp;
            wordCount++;
        }
    }

    fclose(fp);
}

void insertSort(WordEntry arr[], int n) {
    for (int i = 1; i < n; i++) {
        WordEntry key = arr[i];
        int j = i - 1;
        while (j >= 0 && compareLoweredWord(arr[j].word, key.word) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void qsortNotRecursive(WordEntry arr[], int n) {
    int* stack = (int*)malloc(sizeof(int) * n * 2);
    int top = -1;

    stack[++top] = 0;
    stack[++top] = n - 1;

    while (top >= 0) {
        int right = stack[top--];
        int left = stack[top--];

        WordEntry pivot = arr[right];
        int i = left - 1;
        for (int j = left; j < right; j++) {
            if (compareLoweredWord(arr[j].word, pivot.word) <= 0) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[right]);
        int p = i + 1;

        if (p - 1 > left) {
            stack[++top] = left;
            stack[++top] = p - 1;
        }
        if (p + 1 < right) {
            stack[++top] = p + 1;
            stack[++top] = right;
        }
    }

    free(stack);
}

void makeHeap(WordEntry arr[], int n, int i) {
    int root = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compareLoweredWord(arr[left].word, arr[root].word) > 0)
        root = left;
    if (right < n && compareLoweredWord(arr[right].word, arr[root].word) > 0)
        root = right;

    if (root != i) {
        swap(&arr[i], &arr[root]);
        makeHeap(arr, n, root);
    }
}

void heapSort(WordEntry arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        makeHeap(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        makeHeap(arr, i, 0);
    }
}

int middleOfThree(WordEntry arr[], int left, int mid, int right) {
    const char* a = arr[left].word;
    const char* b = arr[mid].word;
    const char* c = arr[right].word;

    if (compareLoweredWord(a, b) < 0) {
        if (compareLoweredWord(b, c) < 0) return mid;
        else if (compareLoweredWord(a, c) < 0) return right;
        else return left;
    } else {
        if (compareLoweredWord(a, c) < 0) return left;
        else if (compareLoweredWord(b, c) < 0) return right;
        else return mid;
    }
}

void betterQsortNotRecursive(WordEntry arr[], int n) {  // 동일한 퀵정렬 함수, 인자로 중간값으로 선별된 피봇이 들어감
     int* stack = (int*)malloc(sizeof(int) * n * 2);
    int top = -1;

    stack[++top] = 0;
    stack[++top] = n - 1;

    while (top >= 0) {
        int right = stack[top--];
        int left = stack[top--];

        if (left >= right) continue;

        int mid = (left + right) / 2;
        int pivotIdx = middleOfThree(arr, left, mid, right);
        swap(&arr[pivotIdx], &arr[right]);

        WordEntry pivot = arr[right];
        int i = left - 1;

        for (int j = left; j < right; j++) {
            if (compareLoweredWord(arr[j].word, pivot.word) <= 0) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[right]);
        int p = i + 1;

        if (p - 1 > left) {
            stack[++top] = left;
            stack[++top] = p - 1;
        }
        if (p + 1 < right) {
            stack[++top] = p + 1;
            stack[++top] = right;
        }
    }

    free(stack);
}

int binarySearch(const char* target, WordEntry arr[], int n, int* comparedCnt) {
    int left = 0, right = n - 1;
    int mid;
    int cmp;
    *comparedCnt = 0;

    while (left <= right) {
        mid = (left + right) / 2;
        (*comparedCnt)++;
        cmp = compareLoweredWord(target, arr[mid].word);

        if (cmp == 0) return mid;
        else if (cmp < 0) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}

int compareWordEntry(const void* a, const void* b) {    // 내장 qsort 인자 전달
    const WordEntry* wa = (const WordEntry*)a;
    const WordEntry* wb = (const WordEntry*)b;
    return compareLoweredWord(wa->word, wb->word);
}

int main() {
    readFile("randdict_utf8.TXT");

    clock_t t1 = clock();
    insertSort(wordArrayByInsert, wordCount);
    clock_t t2 = clock();
    printf("삽입 정렬: %.4f초\n", (double)(t2 - t1) / CLOCKS_PER_SEC);

    t1 = clock();
    qsortNotRecursive(wordArrayByQuick, wordCount);
    t2 = clock();
    printf("퀵 정렬: %f초\n", (double)(t2 - t1) / CLOCKS_PER_SEC);

    t1 = clock();
    heapSort(wordArrayByHeap, wordCount);
    t2 = clock();
    printf("힙 정렬: %f초\n", (double)(t2 - t1) / CLOCKS_PER_SEC);

    t1 = clock();
    qsort(wordArrayByqsort, wordCount, sizeof(WordEntry), compareWordEntry);
    t2 = clock();
    printf("qsort 정렬: %f초\n", (double)(t2 - t1) / CLOCKS_PER_SEC);

    t1 = clock();
    betterQsortNotRecursive(wordArrayByBetterQsort, wordCount);
    t2 = clock();
    printf("중간값을 피봇으로 한 퀵 정렬 시간: %f초\n", (double)(t2 - t1) / CLOCKS_PER_SEC);

    char query[100];
    while (1) {
        printf("단어 입력 : ");
        fgets(query, sizeof(query), stdin);
        query[strcspn(query, "\n")] = '\0';

        int comparedCnt = 0;
        int idx = binarySearch(query, wordArrayByQuick, wordCount, &comparedCnt);
        if (idx >= 0)
            printf("(%d:%d) %s\t%s\n", idx + 1, comparedCnt, wordArrayByQuick[idx].word, wordArrayByQuick[idx].mean);
        else
            printf("단어를 찾을 수 없습니다.\n");
    }

    return 0;
}