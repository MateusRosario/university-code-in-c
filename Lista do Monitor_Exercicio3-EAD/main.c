#include <stdio.h>
#include <stdlib.h>

typedef struct a{
    char elemento;
    struct a* no;
}Pilha;

void push(Pilha** pilha,char elemento){
    Pilha *novo=(Pilha*)malloc(sizeof(Pilha));
    if(pilha!=NULL){
        novo->elemento=elemento;
        novo->no=*pilha;
        *pilha=novo;
    }else{
        novo->elemento=elemento;
        *pilha=novo;
    }
}

char pop(Pilha** pilha){
    char auxi;
    Pilha *temp;
    if(pilha!=NULL){
        auxi=(*pilha)->elemento;
        temp=*pilha;
        *pilha=(*pilha)->no;
        free(temp);
        return auxi;
    }
}

int main() {
    char letra;
    Pilha* a=NULL;
    int i;
    for ( i = 0; i < 20; ++i) {
        scanf("%c", &letra);
        push(&a, letra);
        getchar();
    }

    for (int i = 0; i < 20; ++i) {
        printf("%c,",pop(&a));
    }
    printf("\n");
    return 0;
}