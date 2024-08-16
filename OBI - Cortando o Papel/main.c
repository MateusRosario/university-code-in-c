#include <stdio.h>

int main() {
    int N, i, a;


    scanf("%d",&N);

    int papel[N];
    int max = 0;

    for(i = 0; i < N; i++){
        scanf("%d",&papel[i]);
        if(papel[i] > max){
            max = papel[i];
        }
    }

    int NumCortes[max];
    for( i = 0; i < max; i++){
        NumCortes[i] = 0;
    }

    int antAbaixo = 1;

    for(i = 0; i<max;i++){
        for(a = 0; a < N; a++){
            if(papel[a] <= i){
                if(antAbaixo == 0){
                    NumCortes[i]++;
                    antAbaixo = 1;
                }
            }else{
                if(a == N-1){
                    NumCortes[i]++;
                }
                antAbaixo = 0;
            }
        }
    }

    int maior = 0;
    for (i = 0; i < max;i++){
        if(NumCortes[i] > maior){
            maior = NumCortes[i];
        }
    }
    maior++;
    printf("%d\n",maior);


    return 0;
}