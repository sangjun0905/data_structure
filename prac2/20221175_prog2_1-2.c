#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 방식 2: 0이 아닌 항들의 계수와 차수를 받아 작성

typedef struct {
    int coeff;
    int degree;
} Term;

typedef struct {
    Term *terms;
    int numTerms;  
} Poly;

Poly scanPoly() {
    Term *temp = (Term *)malloc(sizeof(Term) * 50); // 미리 넉넉히 동적 할당한 배열 생성성
    int count = 0;

    printf("수식을 입력하세요 (계수가 0이 아닌 항을 입력받는 방식 2): ");

    while (1) {
        int coeff, degree;
        if (scanf("%d %d", &coeff, &degree) != 2) break;

        temp[count].coeff = coeff;
        temp[count].degree = degree;
        count++;

        if (getchar() == '\n') break;
    }

    // 알맞은 크기로 새 메모리 할당
    Term *exact = (Term *)malloc(sizeof(Term) * count);
    for (int i = 0; i < count; i++) {
        exact[i] = temp[i];
    }

    free(temp);  // 넉넉한 배열은 해제

    Poly p;
    p.terms = exact;
    p.numTerms = count;

    return p;
}


void printPoly(Poly p) {
    for (int i = 0; i < p.numTerms; i++) {
        int coef = p.terms[i].coeff;
        int deg = p.terms[i].degree;

        if (coef == 0) continue;
        if (i != 0 && coef > 0) printf(" + ");
        if (deg == 0) printf("%d", coef);
            else if (deg == 1) printf("%dx", coef);
            else printf("%dx^%d", coef, deg);
    }
    printf("\n");
}


Poly addPoly(Poly a, Poly b) {
    Poly result;
    result.terms = (Term *)malloc(sizeof(Term) * (a.numTerms + b.numTerms));
    result.numTerms = 0;

    int i = 0, j = 0;
    while (i < a.numTerms && j < b.numTerms) {         //차수 비교에 따른 합 또는 순서 지정
        if (a.terms[i].degree == b.terms[j].degree) {
            int sum = a.terms[i].coeff + b.terms[j].coeff;
            if (sum != 0) {
                result.terms[result.numTerms].coeff = sum;
                result.terms[result.numTerms].degree = a.terms[i].degree;
                result.numTerms++;
            }
            i++; j++;
        }
        else if (a.terms[i].degree > b.terms[j].degree) {
            result.terms[result.numTerms++] = a.terms[i++];
        }
        else {
            result.terms[result.numTerms++] = b.terms[j++];
        }
    }

    while (i < a.numTerms) result.terms[result.numTerms++] = a.terms[i++];        // 나머지 복사 넣기
    while (j < b.numTerms) result.terms[result.numTerms++] = b.terms[j++];

    return result;
}

Poly multiplyPoly(Poly a, Poly b) {
    int temp[200] = {0};          // 곱하며 변하는 차수를 일일이 비교하며 더하기 번거로우므로 배열화 시킨 후 인덱스를 통해 차수 표현

    for (int i = 0; i < a.numTerms; i++) {
        for (int j = 0; j < b.numTerms; j++) {
            int deg = a.terms[i].degree + b.terms[j].degree;
            int coef = a.terms[i].coeff * b.terms[j].coeff;
            temp[deg] += coef;
        }
    }

    Poly result;
    result.terms = (Term *)malloc(sizeof(Term) * 200);
    result.numTerms = 0;

    for (int d = 199; d >= 0; d--) {
        if (temp[d] != 0) {
            result.terms[result.numTerms].coeff = temp[d];  //계수
            result.terms[result.numTerms].degree = d;       //차수
            result.numTerms++;
        }
    }

    return result;
}

int polyFunction(Poly p, int x) {
    int result = 0;
    for (int i = 0; i < p.numTerms; i++) {
        result += p.terms[i].coeff * pow(x, p.terms[i].degree);
    }
    return result;
}

void freePoly(Poly *p) {
    free(p->terms);
    p->terms = NULL;
}

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
        printf("x 값을 입력하세요: ");
        scanf("%d", &x);

        printf("수식1 = %d     수식2 = %d     합 = %d     곱 = %d\n",
               polyFunction(p1, x),
               polyFunction(p2, x),
               polyFunction(sum, x),
               polyFunction(prod, x));
    }

    freePoly(&p1);
    freePoly(&p2);
    freePoly(&sum);
    freePoly(&prod);

    return 0;
}