#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct frete{
  int *CityA;
  int *CityB;
  int *Custo;
  int M;
  int N;
  int *pular;
}f;

int addInPular(f *x,int i){
    int a;
    for(a = 0; a < x->M; a++){
        if(x->pular[a]==-1){
            x->pular[a] = i;
            break;
        }
    }
}

int verificaPular(int i, f *x){
    int a;
   for(a = 0; a < x->M; a++){
       if(i == x->pular[a]){
           return 0;
       }
   }
    return 1;
}

int melhorFrete(f *x, int origem, int destino) {
    int i;
    int iniciou = 0;
    int melhor = (1000*(x->N));
    int possibilidade;
    for (i = 0; i < x->M; i++) {
        if (verificaPular(i, x)) {
            if (x->CityA[i] == origem) {
                if (x->CityB[i] == destino) {
                    possibilidade = x->Custo[i];
                    //Verifica
                    if (iniciou == 1) {
                        if (melhor > possibilidade) {
                            melhor = possibilidade;
                        }
                    } else {
                        melhor = possibilidade;
                        iniciou = 1;
                    }
                } else {
                    addInPular(x, i);
                    possibilidade = melhorFrete(x, x->CityB[i], destino) + x->Custo[i];
                    //Verifica
                    if (iniciou == 1) {
                        if (melhor > possibilidade) {
                            melhor = possibilidade;
                        }
                    } else {
                        melhor = possibilidade;
                        iniciou = 1;
                    }
                }
            } else if (x->CityB[i] == origem) {
                if (x->CityA[i] == destino) {
                    possibilidade = x->Custo[i];
                    //Verifica
                    if (iniciou == 1) {
                        if (melhor > possibilidade) {
                            melhor = possibilidade;
                        }
                    } else {
                        melhor = possibilidade;
                        iniciou = 1;
                    }
                } else {
                    addInPular(x, i);
                    possibilidade = melhorFrete(x, x->CityA[i], destino) + x->Custo[i];
                    //Verifica
                    if (iniciou == 1) {
                        if (melhor > possibilidade) {
                            melhor = possibilidade;
                        }
                    } else {
                        melhor = possibilidade;
                        iniciou = 1;
                    }
                }
            }
        }
    }
    return melhor;
}

int main() {
    int i;
    f x;

    scanf("%d %d",&x.N, &x.M);

    x.CityA =(int*)malloc(sizeof(int)*x.M);
    x.CityB =(int*)malloc(sizeof(int)*x.M);
    x.Custo =(int*)malloc(sizeof(int)*x.M);
    x.pular =(int*)malloc(sizeof(int)*x.M);

    for(i = 0; i < x.M; i++){
        scanf("%d %d %d",&x.CityA[i],&x.CityB[i],&x.Custo[i]);
        x.pular[i] = -1;
    }

    int melhor = melhorFrete(&x, 1, x.N);

    printf("%d\n",melhor);

    return 0;
}