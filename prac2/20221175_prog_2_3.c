#include <stdio.h>
#include <stdlib.h>

int array[100][150];  // array[i][0]은 블록 i의 유효한 데이터 수
int moveCount = 0;

// 인덱스를 블록과 블록 내 위치로 변환 (유효한 값 기준)
void getPosition(int index, int *block, int *offset) {
    int validCount = 0;
    for (int i = 0; i < 100; i++) {
        int countInBlock = array[i][0];
        for (int j = 1; j < 150; j++) {
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
    printf("인덱스 초과\n");
    exit(1);
}

// 삽입 함수 (삭제된 자리 먼저 찾고, 없으면 뒤로 밀기)
void insert(int index, int value) {
    int block, offset;
    getPosition(index, &block, &offset);

    // 1단계: 삭제된 자리 있는지 확인
    for (int i = 0; i < 100; i++) {
        for (int j = 1; j < 150; j++) {
            if (array[i][j] == -1) {
                array[i][j] = value;
                moveCount++;
                array[i][0]++;  // 개수 증가
                return;
            }
        }
    }

    // 2단계: 삭제된 자리 없음 → 해당 블록 뒤로 밀기
    int size = array[block][0];
    if (size >= 149) {
        printf("블록 %d 가 꽉 찼습니다.\n", block);
        return;
    }

    // 뒤에서 앞으로 밀기
    for (int j = size + 1; j > offset; j--) {
        array[block][j] = array[block][j - 1];
        moveCount++;
    }

    array[block][offset] = value;
    array[block][0]++;
    moveCount++;
}

// 삭제 함수 (데이터 이동 없이 -1로 마킹)
void delete(int index) {
    int block, offset;
    getPosition(index, &block, &offset);

    if (array[block][offset] != -1) {
        array[block][offset] = -1;
        // array[block][0]은 줄이지 않음 (삭제 표시만)
    }
}

// 조회 함수
int get(int index) {
    int block, offset;
    getPosition(index, &block, &offset);
    return array[block][offset];
}

// 전체 유효 데이터 개수
int totalValid() {
    int total = 0;
    for (int i = 0; i < 100; i++) {
        total += array[i][0];
    }
    return total;
}

// 초기화
void initialize() {
    for (int i = 0; i < 100; i++) {
        array[i][0] = 0;
        for (int j = 1; j < 150; j++) {
            array[i][j] = -1;  // 빈 자리 초기화
        }
    }
}

int getRandomValidIndex() {
    int total = totalValid();
    if (total == 0) return 0;
    return rand() % total;
}

int main() {
    srand(1);  // 랜덤 seed 고정 (테스트 재현 가능)

    initialize();

    // 1. 1만 개 초기 삽입
    for (int i = 0; i < 10000; i++) {
        insert(i, i + 1);
    }

    // 2. 삽입/삭제/조회 1만 회 반복
    for (int i = 0; i < 10000; i++) {
        int index = getRandomValidIndex();
        insert(index, 99999);

        index = getRandomValidIndex();
        delete(index);

        index = getRandomValidIndex();
        for (int j = 0; j < 10; j++) {
            int idx = index + j;
            if (idx < totalValid()) {
                int val = get(idx);
                // printf("%d ", val);  // 확인용
            }
        }
    }

    // 3. 결과 출력
    printf("총 대입 연산 횟수: %d\n", moveCount);
    printf("최종 유효 데이터 개수: %d\n", totalValid());

    return 0;
}
