#include <stdio.h>

int main() {
    int n,i;
    float H = 0;
    scanf("%d", &n);
    for(i = 1; i <=n; i++){
        if(i%2==0){
            H += 1/((float)i);
        }else{
            H += (-1)/((float)i);
        }
    }
    printf("%f", H);
    return 0;
}