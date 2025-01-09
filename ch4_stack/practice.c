#include <stdio.h>

int re(int n){
    printf("fib(%d) 호출\n", n);
    if(n==0) return 0;
    if(n==1) return 1;
    return re(n-1) + re(n-2);
}

void ast(int i){
    if(i>1){
        ast(i/2);
        ast(i/2);
    }
    printf("*");
}

int sum(int n){
    if(n==1) return 1;
    return n+sum(n-1);
}
int fib(int n){
    if(n==1) return 0;
    if(n==2) return 1;
    return fib(n-1)+fib(n-2);
}

int fib2(int n){
    if(n==1) return 0;
    if(n==2) return 1;
    int f1=0; int f2=1;
    int result=0;
    for(int j=2;j<n;j++){
        result=f1+f2;
        f1=f2;
        f2=result;
    }
    return result;
}



int ackermann(int m, int n){
    if(m==0) return n+1;
    if(n==0) return ackermann(m-1,1);
    return ackermann(m-1,ackermann(m,n-1));
}


int main(){

    return 0;
}


