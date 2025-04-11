#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int array[1000][16];  // [i][0]은 각 row에 저장된 자연수의 수, [i][1~10] 자연수 저장, [i][11~15] 여분의 공간
int moveCount = 0;


// 자연수 넣어주기기
void initNum() {
    int cnt = 1;
    for (int i = 0; i < 1000; i++) {
        array[i][0] = 10;
        for (int j = 1; j <= 10; j++) {
            array[i][j] = cnt++;
        }
        for (int j = 11; j < 16; j++) {
            array[i][j] = -1;
        }
    }
}

// 공백이 아닌 진짜 수의 개수수
int totalReal() {
    int total = 0;
    for (int i = 0; i < 1000; i++) {
        total += array[i][0];
    }
    return total;
}

//값의 실제 위치 찾기
void getPosition(int index, int *row, int *col) {
    int validCount = 0;
    for (int i = 0; i < 1000; i++) {
        for (int j = 1; j <= array[i][0]; j++) {
            if (array[i][j] != -1) {
                if (validCount == index) {
                    *row = i;
                    *col = j;
                    return;
                }
                validCount++;
            }
        }
    }
}

void insert(int index, int value) {
    int row, col;
    if (totalReal() == 0){
        row = 0;
        col = 1;
    } else {
        if (index > totalReal()) index = totalReal();
        getPosition(index, &row, &col);
    }

    while (array[row][0] >= 15) {     // row가 가득 찬 경우 다음 row 첫번째 실제 원소로 이동
        row++;
        col = 1;
    }

    for (int j = array[row][0] + 1; j > col; j--) {   // 뒤에 삽입해주기
        
        if (array[row][j - 1] != -1) {
            array[row][j] = array[row][j - 1];
            moveCount++;
        }
    }

    array[row][col] = value;
    moveCount++;
    array[row][0]++;
}

void delete(int index) {
    int row, col;
    getPosition(index, &row, &col);

    int size = array[row][0];

    for (int j = col; j < size; j++) {
        array[row][j] = array[row][j + 1];  // 앞으로 땡기기기
        moveCount++;
    }

    array[row][size] = -1;  // 맨 뒷 부분 공백화
    array[row][0]--;
}

int get(int index) {
    int row, col;
    getPosition(index, &row, &col);
    return array[row][col];
}

int rangeIndex() {
    return (totalReal() == 0) ? 0 : rand() % totalReal();
}

int main() {
    srand(1);
    initNum();

    for (int i = 0; i < 10000; i++) {
        insert(rangeIndex(), 1234);
        delete(rangeIndex());

        int idx = rangeIndex();
        for (int j = 0; j < 10; j++) {
            int t = idx + j;
            if (t < totalReal()) {
                int val = get(t);
                printf("%d ", val);
            }
        }
    }

    printf("\n총 대입연산: %d\n", moveCount);
    return 0;
}
