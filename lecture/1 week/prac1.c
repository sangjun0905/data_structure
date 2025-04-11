#include <stdio.h>
#include <stdlib.h>

/*
// 실습 1

// sum all of score in class
int sum(int s[10])
{
    int i;
    int total = 0;

    for (i = 0; i < 10; i++)
        total += s[i];
    return total;
}

int  main(void)
{
    // 10명으로 구성된 반이 3개 있다. 
    int score1[10], score2[10], score3[10];
    int i;

    for (i = 0; i < 10; i++)
        score1[i] = i;

    for (i = 0; i < 10; i++)
        score2[i] = i*2;

    for (i = 0; i < 10; i++)
        score3[i] = i*3;

    printf("class 1 %d\n", sum(score1));
    printf("class 2 %d\n", sum(score2));
    printf("class 3 %d\n", sum(score3));
}
*/

/*
// 실습 2

// sum all of score in class
int sum(int s[10])
{
    int i;
    int total = 0;

    for (i = 0; i < 10; i++)
        total += s[i];
    return total;
}

int  main(void)
{
    // 10명으로 구성된 반이 3개 있다. 
    int score1[10], score2[7], score3[5];
    int i;

    for (i = 0; i < 10; i++)
        score1[i] = i;

    for (i = 0; i < 7; i++)
        score2[i] = i * 2;

    for (i = 0; i < 5; i++)
        score3[i] = i * 3;

    printf("class 1 %d\n", sum(score1));
    printf("class 2 %d\n", sum(score2));
    printf("class 3 %d\n", sum(score3));
}
*/


/*
// 실습 3

// sum all of score in class
int sum(int s[10][4])       // int sum(int (*s)[4])
{
    int i,j;
    int total = 0;

    for (i = 0; i < 10; i++)
        for(j=0;j<4;j++)
            total += s[i][j];
    return total;
}

int  main(void)
{
    // 10명으로 구성된 반이 3개 있다.
    int score1[10][4], score2[10][4], score3[10][4];
    int i,j;

    for (i = 0; i < 10; i++)
        for(j=0;j<4;j++)
            score1[i][j] = i;

    for (i = 0; i < 10; i++)
        for(j=0;j<4;j++)
            score2[i][j] = i*2;

    for (i = 0; i < 10; i++)
        for(j=0;j<4;j++)
            score3[i][j] = i*3;

    printf("class 1 %d\n", sum(score1));
    printf("class 2 %d\n", sum(score2));
    printf("class 3 %d\n", sum(score3));
}
*/


/*
// 실습 4

// sum all of score in class
int sum(int s[10][4])       // int sum(int (*s)[4])
{
    int i,j;
    int total = 0;

    for (i = 0; i < 10; i++)
        for(j=0;j<4;j++)
            total += s[i][j];
    return total;
}

int  main(void)
{
    // 10명으로 구성된 반이 3개 있다.
    int score1[10][4], score2[7][4], score3[5][4];
    int i,j;

    for (i = 0; i < 10; i++)
        for(j=0;j<4;j++)
            score1[i][j] = i;

    for (i = 0; i < 7; i++)
        for(j=0;j<4;j++)
            score2[i][j] = i*2;

    for (i = 0; i < 5; i++)
        for(j=0;j<4;j++)
            score3[i][j] = i*3;

    printf("class 1 %d\n", sum(score1));
    printf("class 2 %d\n", sum(score2));
    printf("class 3 %d\n", sum(score3));
}
*/

/*
// 실습 5

// sum all of score in class
int sum(int *s, int x, int y) 
{
    int i, j;
    int total = 0;

    for (i = 0; i < x; i++)
        for (j = 0; j < y; j++)
            total += s[i*y+j];
    return total;
}

int  main(void)
{
    // 5~10명으로 구성된 반 3개가 2~4과목 점수가 있다.
    int score1[10][4], score2[7][3], score3[5][2];
    int i, j;

    for (i = 0; i < 10; i++)
        for (j = 0; j < 4; j++)
            score1[i][j] = i;

    for (i = 0; i < 7; i++)
        for (j = 0; j < 3; j++)
            score2[i][j] = i * 2;

    for (i = 0; i < 5; i++)
        for (j = 0; j < 2; j++)
            score3[i][j] = i * 3;

    printf("class 1 %d\n", sum(score1, 10, 4));
    printf("class 2 %d\n", sum(score2, 7, 3));
    printf("class 3 %d\n", sum(score3, 5, 2));
}
*/


// 실습 6

// sum all of score in class
int sum(int** s, int x, int y)
{
    int i, j;
    int total = 0;

    for (i = 0; i < x; i++)
        for (j = 0; j < y; j++) {
            total += s[i][j];
        }
    return total;
}

int  main(void)
{
    int **score[3];
    int size[3][2] = { {10,4}, {7, 3}, {5, 2} };
    int i, j,k;

    for (i = 0; i < 3; i++) {
        score[i] = malloc(sizeof(int*) * size[i][0]);
        for (j = 0; j < size[i][0]; j++) {
            score[i][j] = malloc(sizeof(int) * size[i][1]);
            for (k = 0; k < size[i][1]; k++)
                score[i][j][k] = (i + 1);
        }
    }

    for(i=0;i<3;i++)
        printf("class %d %d\n", i+1, sum(score[i], size[i][0], size[i][1]));
}


