#include <stdio.h>

int main() {
    int N1, N2,sumN1,sumN2, tempN1, tempN2;
    scanf("%d %d", &tempN1, &tempN2);
    while(tempN1 != 0 && tempN2 != 0){
        sumN1 = 0;
        sumN2 = 0;
        N1 = tempN1*tempN1;
        N2 = tempN2*tempN2;
        while(N1 != 0){
            sumN1 += N1%10;
            N1 = N1/10;
        }
        while(N2 != 0){
            sumN2 += N2%10;
            N2 = N2/10;
        }
        if(sumN1 == tempN2 && sumN2 == tempN1){
            printf("%d\n",1);
        }else{
            printf("%d\n",0);
        }
        scanf("%d %d", &tempN1, &tempN2);
    }
    return 0;
}