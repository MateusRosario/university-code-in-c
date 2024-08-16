#include <stdio.h>
#include <string.h>

int main() {
    char entrada[8];
    while(scanf("%[^\n]s", &entrada) != EOF){
        if(strcmp("esquerda", entrada) == 0){
            printf("Ingles\n");
        }else if(strcmp(entrada, "direita") == 0){
            printf("frances\n");
        }else if(strcmp(entrada, "nenhuma") == 0){
            printf("portugues\n");
        }else if(strcmp(entrada, "as duas") == 0){
            printf("caiu\n");
        }
    }
}