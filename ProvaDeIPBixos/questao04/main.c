#include <stdio.h>

int main() {
    int i, k,tn_1=0,tn_2=0,tn_3=0,temp;
    scanf("%d",&k);
    while(k != 0) {
        for (i = 1; i <= k; i++) {
            if (i == 1) {
                printf("%d,", 1);
                tn_3 = tn_2;
                tn_2 = tn_1;
                tn_1 = 1;
            } else if (i == 2) {
                printf("%d,", 2);
                tn_3 = tn_2;
                tn_2 = tn_1;
                tn_1 = 2;
            } else if (i == 3) {
                printf("%d,", 3);
                tn_3 = tn_2;
                tn_2 = tn_1;
                tn_1 = 3;
            } else {
                temp = -tn_1 + tn_2 + tn_3;
                printf("%d,", temp);
                tn_3 = tn_2;
                tn_2 = tn_1;
                tn_1 = temp;
            }
        }
        printf("\n");
        scanf("%d",&k);
    }
    return 0;
}