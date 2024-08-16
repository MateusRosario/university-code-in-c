#include <stdio.h>

int main() {
    char L, mask = 32;
    scanf("%c",&L);
    printf("'%c'", mask ^ L);
    return 0;
}