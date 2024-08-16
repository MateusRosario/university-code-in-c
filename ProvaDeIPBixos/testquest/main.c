#include <stdio.h>

int main() {
    int anos = 0, meses = 0, dias = 0;
    scanf("%d", &dias);
    anos = dias/365;
    dias = dias - (anos*365);
    meses = dias/30;
    dias = dias - (meses*30);
    printf("%d ano(s)\n", anos);
    printf("%d mes(es)\n", meses);
    printf("%d dia(s)\n",dias);
    return 0;
}