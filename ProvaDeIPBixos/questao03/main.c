#include <stdio.h>

int main() {
    int ent, i, isCousin, cont = 0;
    scanf("%d", &ent);
    while(ent != 0){
        isCousin = 0;
        for(i = 2; i < ent ; i++){
            if(ent%i==0){
                isCousin = 1;
            }
        }
        if(isCousin == 1){
            cont++;
        }
        scanf("%d",&ent);
    }
    printf("%d\n",cont);
    return 0;
}