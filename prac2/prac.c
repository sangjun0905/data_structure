#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int array[500][31];  // [i][0] = 유효 데이터 수, [i][1~30] = 실제 데이터 저장 공간
int moveCount = 0;

void initialize() {
    int cnt = 1;
    for (int i = 0; i < 500; i++) {
        array[i][0] = 20;  // 블록당 20개만 초기화
        for (int j = 1; j <= 20; j++) {
            array[i][j] = cnt++;
        }
        for (int j = 21; j < 31; j++) {
            array[i][j] = -1;  // 공백 채우기
        }
    }
}

int totalValid() {
    int total = 0;
    for (int i = 0; i < 500; i++) {
        total += array[i][0];
    }
    return total;
}

void getPosition(int index, int *block, int *offset) {
    int validCount = 0;
    for (int i = 0; i < 500; i++) {
        for (int j = 1; j <= array[i][0]; j++) {
            if (array[i][j] != -1) {
                if (validCount == index) {
                    *block = i;
                    *offset = j;
                    return;
                }
                validCount++;
            }
        }
    }
    printf("getPosition(): 인덱스 초과 (%d / 총 유효 %d)\n", index, validCount);
    exit(1);
}

void insert(int index, int value) {
    int block, offset;
    if (totalValid() == 0) {
        block = 0;
        offset = 1;
    } else {
        if (index > totalValid()) index = totalValid();
        getPosition(index, &block, &offset);
    }

    // 가득 찬 블록 넘기기
    while (array[block][0] >= 30) {
        block++;
        if (block >= 500) {
            printf("삽입 실패: 모든 블록이 가득 찼습니다.\n");
            return;
        }
        offset = 1;
    }

    // 뒤에서 앞으로 밀기
    for (int j = array[block][0] + 1; j > offset; j--) {
        if (j >= 31) continue;
        if (array[block][j - 1] != -1) {
            array[block][j] = array[block][j - 1];
            moveCount++;
        }
    }

    array[block][offset] = value;
    moveCount++;
    array[block][0]++;
}

void delete(int index) {
    int block, offset;
    getPosition(index, &block, &offset);

    int size = array[block][0];
    for (int j = offset; j < size; j++) {
        if (array[block][j + 1] != -1) {
            array[block][j] = array[block][j + 1];
            moveCount++;
        }
    }

    array[block][size] = -1;
    array[block][0]--;
}

int get(int index) {
    int block, offset;
    getPosition(index, &block, &offset);
    return array[block][offset];
}

int safeIndex() {
    int valid = totalValid();
    return (valid == 0) ? 0 : rand() % valid;
}

int main() {
    srand(1);  // 랜덤 시드 고정
    initialize();

    for (int i = 0; i < 10000; i++) {
        insert(safeIndex(), 99999);
        delete(safeIndex());
    
        // 🔥 조회도 이 안에!
        int idx = safeIndex();
        for (int j = 0; j < 10; j++) {
            int t = idx + j;
            if (t < totalValid()) {
                int val = get(t);
                printf("%d ", val);
            }
        }
    }

    printf("\n총 대입연산: %d\n", moveCount);
    return 0;
}
