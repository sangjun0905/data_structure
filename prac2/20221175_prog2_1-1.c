#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

// 방식 1: 모든 차수의 계수를 배열로 저장 (역순 저장)
typedef struct {
    int degree;
    int *coeffArray;  // 동적 메모리 할당
} Poly;

// 다항식 입력 (계수만 입력, 역순 저장)
Poly scanPoly() {
    int input[100];
    int cnt = 0;

    printf("수식을 입력하세요 (계수만 입력하는 방식1): ");
    while (1) {
        int realCoeff;
        if (scanf("%d", &realCoeff) != 1) break;
        input[cnt++] = realCoeff;
        if (getchar() == '\n') break;
    }

    Poly p;
    p.degree = cnt - 1;
    p.coeffArray = (int *)malloc(cnt * sizeof(int));

    // 역순 저장
    for (int i = 0; i < cnt; i++) {
        p.coeffArray[i] = input[i];
    }

    return p;
}


void printPoly(Poly p) {
    for (int i = 0; i <= p.degree; i++) {
        int coef = p.coeffArray[i];
        int deg = p.degree - i;
        if (coef == 0) continue;

        if (i > 0 && coef > 0) printf(" + ");

        if (deg == 0) printf("%d", coef);
        else if (deg == 1) printf("%dx", coef);
        else printf("%dx^%d", coef, deg);
    }
    printf("\n");
}


Poly addPoly(Poly a, Poly b) {
    int maxDeg = (a.degree > b.degree) ? a.degree : b.degree;
    int size = maxDeg + 1;

    Poly result;
    result.degree = maxDeg;
    result.coeffArray = (int *)calloc(size, sizeof(int));

    for (int i = 0; i <= a.degree; i++) {
        int ai = size - a.degree - 1 + i;
        result.coeffArray[ai] += a.coeffArray[i];
    }

    for (int i = 0; i <= b.degree; i++) {
        int bi = size - b.degree - 1 + i;
        result.coeffArray[bi] += b.coeffArray[i];
    }

    return result;
}


Poly multiplyPoly(Poly a, Poly b) {
    int degA = a.degree;
    int degB = b.degree;
    int degR = degA + degB;

    Poly result;
    result.degree = degR;
    result.coeffArray = (int *)calloc(degR + 1, sizeof(int));

    for (int i = 0; i <= degA; i++) {
        for (int j = 0; j <= degB; j++) {
            int coefA = a.coeffArray[i];
            int coefB = b.coeffArray[j];
            int degA_i = degA - i;
            int degB_j = degB - j;
            int degTemp = degA_i + degB_j;
            result.coeffArray[degR - degTemp] += coefA * coefB;
        }
    }

    return result;
}

// 다항식 평가
int polyFunction(Poly p, int x) {
    int result = 0;
    for (int i = 0; i <= p.degree; i++) {
        int deg = p.degree - i;
        result += p.coeffArray[i] * pow(x, deg);
    }
    return result;
}

// 동적 메모리 해제
void freePoly(Poly *p) {
    free(p->coeffArray);
    p->coeffArray = NULL;
}

// 메인 함수
int main() {
    Poly p1 = scanPoly();
    Poly p2 = scanPoly();

    Poly sum = addPoly(p1, p2);
    Poly prod = multiplyPoly(p1, p2);

    printf("수식 1: "); printPoly(p1);
    printf("수식 2: "); printPoly(p2);
    printf("수식 1 + 2 = "); printPoly(sum);
    printf("수식 1 * 2 = "); printPoly(prod);

    int x;
    while (1) {
        printf("수식에 대입할 x 값 입력: ");
        scanf("%d", &x);

        printf("수식1 = %d     수식2 = %d     수식1+2 = %d     수식1*2 = %d\n",
               polyFunction(p1, x),
               polyFunction(p2, x),
               polyFunction(sum, x),
               polyFunction(prod, x));
    }

    // 메모리 해제
    freePoly(&p1);
    freePoly(&p2);
    freePoly(&sum);
    freePoly(&prod);

    return 0;
}
