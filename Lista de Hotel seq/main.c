#include <stdio.h>


void Ins(Lista **lista,int elem) {
    Lista *novo = (Lista*)malloc(sizeof(Lista));
    novo->elemento=elem;
    if((*lista)!=NULL){
        if(novo->elemento<=(*lista)->elemento){
            novo->no=(*lista);
            (*lista)=novo;
        }else{
            Lista *aux;
            Lista *aux2;
            aux2=(*lista);
            int repetir=1;
            do {
                if(aux2->no!=NULL){
                    aux=aux2;
                    aux2=aux2->no;
                    if(novo->elemento<=aux2->elemento){
                        aux->no=novo;
                        novo->no=aux2;
                        repetir=0;
                    }
                }else{
                    aux2->no=novo;
                    novo->no=NULL;
                    repetir=0;
                }
            }while(repetir);
        }
    }else{
        novo->no=NULL;
        (*lista)=novo;
    }
}

int Rem(Lista **lista, int elem) {
    if((*lista)!=NULL){
        Lista *aux;
        if((*lista)->elemento==elem){
            aux=(*lista);
            (*lista)=(*lista)->no;
            free(aux);
            return 1;
        }else{
            Lista *aux2;
            aux2=(*lista);
            do{
                if(aux2->no!=NULL) {
                    aux = aux2;
                    aux2 = aux2->no;
                    if(aux2->elemento==elem){
                        aux->no=aux2->no;
                        free(aux2);
                        return 1;
                    }
                }else{
                    return 0;
                }
            }while(1);
        }
    }else{
        return 0;
    }
}

int Find(Lista **lista, int elem){
    if((*lista)!=NULL){
        if((*lista)->elemento==elem){
            return 1;
        }else {
            Lista *aux;
            aux = (*lista);
            int cont=1;
            while (aux->no!=NULL){
                cont++;
                aux=aux->no;
                if (aux->elemento==elem) {
                    return cont;
                }
            }
        }
    }else{
        return 0;
    }
    return 0;
}

void printLista(Lista **lista){
    Lista *aux;
    aux=(*lista);
    while(aux!=NULL){
        printf("%d,",aux->elemento);
        aux=aux->no;
    }
}


int main() {
    printf("Hello, World!\n");
    return 0;
}