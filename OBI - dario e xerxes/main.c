#include <stdio.h>

int main() {
    int N, i, a, act, darioPT = 0, xerxesPT = 0;
    scanf("%d",&N);
    int dario;
    int xerxes;

    for(i = 0; i < N; i++){
        act = 0;
        scanf("%d %d",&dario,&xerxes);
        for(a = dario + 1; a>-1; a++){
            if(a > 4){
                a = 0;
            }
            if(a == xerxes){
                darioPT++;
                break;
            }
            act++;
            if(act >= 2){
                xerxesPT++;
                break;
            }
        }
    }

    if(darioPT > xerxesPT){
        printf("dario\n");
    }else{
        printf("xerxes\n");
    }
    return 0;
}