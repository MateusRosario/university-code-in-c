#include <stdio.h>

long fibonacci(long long n){
    long long a=0;
    long long b=1;
    long long aux;
    if(n==1){
        return a;
    }else if(n==2){
        return b;
    }else{
        int cont=2;
        do{
            cont++;
            aux=b;
            b=b+a;
            a=aux;
        }while(cont!=n);
        return b;
    }
}

int mainn() {
    int N;
    long long r;
    scanf("%d",&N);

    if(N%2==0){
        r=fibonacci(N)*N;
    }else{
        r=(fibonacci(N)*N)+1;
    }
    printf("%llu",r);
    return 0;

}