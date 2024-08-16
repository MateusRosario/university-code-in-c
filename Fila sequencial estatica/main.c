#include <stdio.h>


typedef struct fila {
    int inicio;
    int fim;
    int ocupados;
    char fila[50];
}Fila;

void enqueue(Fila *fila,char elemento){
    if(fila->ocupados<50) {
        fila->fila[fila->fim] = elemento;
        fila->fim++;
        fila->ocupados++;
        if (fila->fim > 49){
            fila->fim = 0;
        }
    }
}

char dequeue(Fila *fila){
    char aux;
    if(fila->ocupados>0){
        aux=fila->fila[fila->inicio];
        fila->inicio++;
        fila->ocupados--;
        if(fila->inicio>49){
            fila->inicio=0;
        }
        return aux;
    }
}

int main() {
    Fila fila;
    fila.inicio=0;
    fila.fim=0;
    fila.ocupados=0;
    char letra;
    int i;

    scanf("%c", &letra);
    do{
        enqueue(&fila, letra);
        scanf("%c", &letra);
    }while(letra!='\n');

    while(fila.ocupados>0){
        printf("%c",dequeue(&fila));
    }

    printf("\n");
    return 0;
}