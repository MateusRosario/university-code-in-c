#include <stdio.h>

int main() {
    int M[4] = {10,6, 3, 2};
    int n = 4, i, a;
    int soma = 0;

    for(i=0 ; i<n; i++){
        for(a=0; a<n-1; a++){
            if(M[a] > M[a+1]){
                int temp = M[a+1];
                M[a+1] = M[a];
                M[a] = temp;
            }
            soma = soma + 4;
        }
    }

    for(i=0 ; i < n; i++){
        printf("%d,", M[i]);
    }

    printf("\n");
    printf("Número de operações: %d\n",soma);
    return 0;
}