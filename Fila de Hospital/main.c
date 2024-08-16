#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no_char{
    char *elemento;
    struct no_char *proximo;
}no;

typedef struct fila_h{
    no *final;
    no *inicio;
}fila;

void enqueue(fila *f_color,char *nome){
    no *novo=(no*)malloc(sizeof(no));
    novo->elemento=(char*)malloc(sizeof(char)*strlen(nome));
    strcpy(novo->elemento,nome);
    novo->proximo=NULL;
    if(f_color->inicio==NULL){
        f_color->inicio=novo;
        f_color->final=novo;
    }else{
        f_color->final->proximo = novo;
    }
    f_color->final=novo;
}

char* dequeue(fila *f_color,char *nome){
    no *auxi;
    auxi=f_color->inicio;
    nome=(char*)malloc(sizeof(char)*strlen(f_color->inicio->elemento));
    strcpy(nome,f_color->inicio->elemento);
    f_color->inicio=f_color->inicio->proximo;
    free(auxi);
    return nome;
}

char* scanString(){
    char tecla;
    char *retorno=NULL;
    int tam=0;
    do{
        tecla=getchar();
        if(retorno==NULL)
            retorno=(char*)malloc(sizeof(char));
        else
            retorno=(char*)realloc(retorno,tam+1);
        retorno[tam]=tecla;
        tam++;
    }while(tecla!='\n');
    retorno[tam-1]='\0';
    return retorno;
}

int main() {
    fila red;
    fila yellow;
    fila green;
    red.inicio=NULL;
    red.final=NULL;
    yellow.inicio=NULL;
    yellow.final=NULL;
    green.inicio=NULL;
    green.final=NULL;
    char* nome;
    char ch;
    int sair=0;
    int i;


    do {
        printf(">>>> Fila Hospitalar <<<<\n");
        printf("\n\n        (Opções)\n\n");
        printf("(1)Adicionar Paciente.\n");
        printf(" (2)Chamar  Paciente.\n");
        if(green.inicio==NULL && yellow.inicio==NULL && red.inicio==NULL){
            printf("  (3)Fechar Progama.\n");
        }
        printf("\n\nDigite-> ");
        scanf("%c", &ch);
        getchar();
        switch (ch) {
            case '1':
                printf("Nome:");

                nome = scanString();

                printf("Estado:\n");
                printf("(1)Vermelho.\n");
                printf("(2)Amarelo.\n");
                printf("(3)Verde.\n");
                scanf("%c", &ch);
                getchar();
                switch (ch) {
                    case '1':
                        enqueue(&red, nome);
                        break;
                    case '2':
                        enqueue(&yellow, nome);
                        break;
                    case '3':
                        enqueue(&green, nome);
                        break;
                }
                free(nome);
                break;
            case '2':
                if(red.inicio==NULL){
                    if(yellow.inicio==NULL){
                        if(green.inicio==NULL){

                        }else{
                            printf("\n\n\n||Chamando paciente --> %s||\n",dequeue(&green,nome));
                            printf("||Estado de urgencia: VERDE||\n\n\n");
                        }
                    }else{
                        printf("\n\n\n||Chamando paciente --> %s||\n",dequeue(&yellow,nome));
                        printf("||Estado de urgencia: !AMARELO!||\n\n\n");
                    }
                }else{
                    printf("\n\n\n||Chamando paciente --> %s||\n",dequeue(&red,nome));
                    printf("||Estado de urgencia: !!VERMELHO!!||\n\n\n");
                }
                break;
            case '3':
                sair=1;
                break;
            default:
                printf("Opcao Invalida\n");
                break;
        }
    }while(sair!=1);
    return 0;
}