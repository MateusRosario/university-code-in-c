#include <stdio.h>

int main() {
    int n,i,j,bool = 0;
    scanf("%d",&n);
    int V[n];
    for(i = 0; i < n; i++){
        scanf("%d",&V[i]);
    }

    for(i = 0; i < n; i++){
        bool = 0;
        for(j = i + 1; j < n; j++){
            if(V[j]>V[i]){
                printf("%d ",V[j]);
                bool = 1;
                break;
            }
        }
        if(bool == 0){
            printf("*");
            if(i != n -1){
                printf(" ");
            }
        }
    }
    printf("\n");
}
