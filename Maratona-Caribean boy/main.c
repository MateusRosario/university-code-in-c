#include <stdio.h>

int main() {

    int i, n, k, temp, opSoma = 0, opSub = 0, opSS = 0, varSoma, varSub;

    scanf("%d %d", &k, &n);

    int min = n;
    int sequencia[k];

    for(i = 0; i < k; i++){
        sequencia[i] = 0;
    }

    for(i = 0; i < n; i++){


        scanf("%d", &temp);

        sequencia[temp-1] = sequencia[temp-1] + 1;


    }

    for(i = 0; i < k; i++){
        if(min > sequencia[i])
            min = sequencia[i];
    }

    int zeros = 0;
    for(i = 0; i < k; i++){

        sequencia[i] = sequencia[i] - min;
        if(sequencia[i] > 2){
            printf("*\n");
            return 0;
        }
        if(sequencia[i] == 0){
            zeros++;
        }
    }

    if(zeros > k/2){
        for( i = 0; i < k; i++){
            sequencia[i] +=1;
        }
    }

    for(i = 0; i < k; i++){

        if(sequencia[i] == 0){
            opSoma++;
            varSoma = i + 1;
        }
        else if(sequencia[i] == 2){
            opSub++;
            varSub = i + 1;
        }

    }

    if(opSoma+opSub>2){
        printf("*\n");
    }else if(opSoma!=0 && opSub!=0){
        printf("-%d +%d\n",varSub,varSoma);
    }else if(opSoma!=0){
        printf("+%d\n",varSoma);
    }else if(opSub!=0){
        printf("-%d\n",varSub);
    }
    return 0;
}