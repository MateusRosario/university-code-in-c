#include <stdio.h>
#include <stdlib.h>


typedef struct inf{
    char* nome;
    char* descricao;
}Info;

typedef struct lista{
    int num;
    Info* info;
    struct lista* proximo;
    struct lista* anterior;
}Quarto;

int Ins(Quarto** quarto, int num, Info info) {
    Quarto *novo = (Quarto *) malloc(sizeof(Quarto));
    novo->num = num;
    novo->info = &info;
    if(num==(*quarto)->num) {
        return 0;
    }else {
        if (*quarto != NULL) {
            if ((*quarto)->num == (*quarto)->proximo->num) {
                novo->anterior = *quarto;
                novo->proximo = *quarto;
                (*quarto)->proximo = novo;
                (*quarto)->anterior = novo;
                return 1;
            } else {
                Quarto *auxi;
                if ((*quarto)->num < novo->num) {
                    auxi = (*quarto)->proximo;
                    do {
                        if((auxi->num>novo->num)){ //verifica se entre *quarto e auxi é o local de novo.
                            novo->anterior=*quarto;
                            novo->proximo=auxi;
                            (*quarto)->proximo=novo;
                            auxi->anterior=novo;
                            return (1);
                        }
                        if(auxi->num<(*quarto)->num){ //verifica se chegou ao fim da lista no sentido proximo(aumentando).
                            novo->anterior=*quarto;
                            novo->proximo=auxi;
                            (*quarto)->proximo=novo;
                            auxi->anterior=novo;
                            return (1);
                        }
                        *quarto=auxi;
                        auxi=auxi->proximo;
                    } while (1);
                } else {
                    auxi = (*quarto)->anterior;
                    do {
                        if((auxi->num<novo->num)){ //verifica se entre *quarto e auxi é o local de novo.
                            novo->proximo=*quarto;
                            novo->anterior=auxi;
                            (*quarto)->anterior=novo;
                            auxi->proximo=novo;
                            return (1);
                        }
                        if(auxi->num>(*quarto)->num){ //verifica se chegou ao fim da lista no sentido anterior(diminuindo).
                            novo->proximo=*quarto;
                            novo->anterior=auxi;
                            (*quarto)->anterior=novo;
                            auxi->proximo=novo;
                            return (1);
                        }
                        *quarto=auxi;
                        auxi=auxi->anterior;
                    } while (1);
                }
            }
        } else {
            novo->anterior = novo;
            novo->proximo = novo;
            *quarto = novo;
            return 1;
        }
    }

}

void Rem(Quarto quarto, int num){

}

void Find(Quarto quarto, int num){

}

int main(){
    return 0;
}