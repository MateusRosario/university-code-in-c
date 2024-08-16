#include <stdio.h>

int mainn(){


    int k, n, i, temp=0, max = 0, min = 0,outra=0;

    scanf("%d %d", &k, &n);
    char printar[2];
    char printarN[2];

    int sequencia[k];

    for(i = 0; i < k; i++){
        sequencia[i] = 0;
    }



    for(i = 0; i < n; i++){

       scanf("%d", &temp);


       sequencia[temp-1]++;

    }

    temp=0;
    for (i = 0; i < k ; ++i) {

        if(sequencia[i]==1){
            if(n==1){
                printf("+%d",i+1);
                return 0;
            }
            printar[max]='+';
            max++;
            printarN[min]=i+1;
            min++;
            temp++;


        }

        if (sequencia[i]==3){
            printar[max]='-';
            max++;
            printarN[min]=i+1;
            min++;
            outra++;
        }
        if(outra >1 || temp>1){
            printf("*");
            return 0;
        }

    }
    printf("%c%d%c%d\n",printar[0],printarN[0],printar[1],printarN[1]);
    return 0;

}