#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct classe{
    int FrequenciaAbsoluta;
    double FrequenciaRelativa;
    int FrequenciaAcumulada;
}classe;

int main() {
    //Pegar número de elementos utilizado.
    int variaveis;

    printf("\n-----------Estatistica-----------\n");
    printf("\nDigite o numero de Variaveis a ser geradas: ");
    scanf("%d", &variaveis);

    int Vetor[variaveis];

    srand((unsigned)time(NULL));

    //Pegar intervalo de números que serão utilizados

    int Max=10;

    printf("\nDigite o intervalo númerico para geração dos elementos: de 0 até: ");
    scanf("%d", &Max);
    Max+=1;

    //Gerar Matriz com numeros aleatorios-----------------------------------------------------

    int Media=0;

    for (int i = 0; i < variaveis ; ++i) {

        Vetor[i]=rand() % Max;

        Media = Media + Vetor[i];
    }

    int indiceMenor, aux, proximoIndice;


    //Ordenar a Matriz-------------------------------------------------------------------------------

    Media = Media/variaveis;

    for (int indice = 0; indice < variaveis; ++indice) {

        indiceMenor=indice;

        for (proximoIndice = indice+1; proximoIndice < variaveis ; ++proximoIndice) {

            if(Vetor[proximoIndice]<Vetor[indiceMenor]){

                indiceMenor=proximoIndice;
            }

        }

        aux=Vetor[indice];
        Vetor[indice]=Vetor[indiceMenor];
        Vetor[indiceMenor]=aux;
    }

    //Calcula Numero de classes------------------------------------------------------
    double NumClasses = sqrt(variaveis);
    int numClasseInt=(int) NumClasses;
    int decimal = NumClasses-numClasseInt;
    if(decimal>0.5){
        numClasseInt+=1;
    }

    //Calcula intervalo das classes---------------------------------------------------
    int intervalo=(int)(Vetor[variaveis-1]-Vetor[0])/numClasseInt;
    intervalo+=(Vetor[0]+1);

    //Calcula Frequencia absoluta---------------------------------------------------
    classe VetorClasses[numClasseInt];

    int Fa;
    int MaiorFa=0;

    for (int j = 1; j <= numClasseInt; ++j) {
        Fa=0;
        for(int i = 0; i < variaveis; ++i) {
            if(Vetor[i]>=((j-1)*(intervalo)) && Vetor[i]<j*intervalo) {
                Fa++;
            }
        }
        if(Fa>MaiorFa){
            MaiorFa=Fa;
        }
        VetorClasses[j-1].FrequenciaAbsoluta=Fa;
    }


    //Calcula Frequencia Acumulada e Relativa.
    int FA=0;
    double MaiorFR=0;

    for (int k = 0; k < numClasseInt; ++k) {
        VetorClasses[k].FrequenciaRelativa = ((double) VetorClasses[k].FrequenciaAbsoluta)/variaveis;
        if(VetorClasses[k].FrequenciaRelativa>MaiorFR){
            MaiorFR=VetorClasses[k].FrequenciaRelativa;
        }
        FA+=VetorClasses[k].FrequenciaAbsoluta;
        VetorClasses[k].FrequenciaAcumulada=FA;
    }



    //IMPRIMIR elementos, tabela e gráficos.-----------------------------------------------------------
    int opcao;
    int altura;

    do {

        printf("\n(1) Imprimir Elementos\n(2) Imprimir tabela;\n(3) Imprimir Histograma da fa;\n(4) Imprimir Histograma da FA\n(5) Imprimir Histograma da FR\n(0) Sair;\n--> ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:

                //IMPRIMIR ELEMENTOS
                printf("\n");

                printf("\n=================== Elementos ======================\n");
                int ant=0;
                for (int m = 0; m < variaveis; ++m) {
                    if(Vetor[m]/100!=ant){
                        printf("\n[%d]", Vetor[m]);
                    }else{
                        printf("[%d]", Vetor[m]);
                    };
                    ant = Vetor[m]/100;
                }

                printf("\n=============================================\n");

                printf("Digite Enter para voltar ao MENU-->");
                getchar();
                getchar();
                break;

            case 2:
                //IMPRIMIR TABELA

                printf("\n");

                printf("\n=======================TABELA========================\n\n");
                printf("________________________________________________________\n");
                printf("|      classes       |    fa    |    FA    |     fr     |\n");
                for (int l = 0; l < numClasseInt; ++l) {
                    printf("________________________________________________________\n");
                    printf("| Classe %.4d -- %.4d|   %.3d    |   %.4d   |   %.4f   |\n", (l) * intervalo,
                           (l + 1) * intervalo,
                           VetorClasses[l].FrequenciaAbsoluta, VetorClasses[l].FrequenciaAcumulada,
                           VetorClasses[l].FrequenciaRelativa);
                }
                printf("________________________________________________________\n");
                printf("\n=====================================================\n");

                printf("Digite Enter para voltar ao MENU-->");
                getchar();
                getchar();
                break;

            case 3:

                //IMPRIMIR GRÁFICO HISTOGRAMA DA FREQUENCIA ABSOLUTA
                printf("\n=====================Histograma da fa===========================\n");

                altura = MaiorFa;
                printf("\n  U |");
                while (altura !=0){
                    printf("\n%.3d |  ",altura);
                    for (int i = 0; i < numClasseInt; ++i) {
                        printf("%c     ",VetorClasses[i].FrequenciaAbsoluta>=altura?219:' ');
                    }
                    altura--;
                }
                printf("\n");

                printf("___");
                for (int j = 0; j < numClasseInt; ++j) {
                    printf("________");

                }

                printf("\n      C1");
                for (int k = 0; k <numClasseInt-1; ++k) {
                    printf("    C%d", k+2);
                }
                printf("    Classes");

                printf("\n\n=======================================================================\n");

                printf("Digite Enter para voltar ao MENU-->");
                getchar();
                getchar();

                break;
            case 4:

                //IMPRIMIR GRÁFICO HISTOGRAMA DA FREQUENCIA ACUMULADA
                printf("\n=====================Histograma da FA===========================\n");

                altura = FA;
                printf("\n  U |");
                while (altura !=0){
                    printf("\n%.3d |  ",altura);
                    for (int i = 0; i < numClasseInt; ++i) {
                        printf("%c     ",VetorClasses[i].FrequenciaAcumulada>=altura?219:' ');
                    }
                    altura--;
                }
                printf("\n");

                printf("___");
                for (int j = 0; j < numClasseInt; ++j) {
                    printf("________");

                }

                printf("\n      C1");
                for (int k = 0; k <numClasseInt-1; ++k) {
                    printf("    C%d", k+2);
                }
                printf("    Classes");

                printf("\n\n=======================================================================\n");

                printf("Digite Enter para voltar ao MENU-->");
                getchar();
                getchar();

                break;
            case 5:

                //IMPRIMIR GRÁFICO HISTOGRAMA DA FREQUENCIA Relativa
                printf("\n=====================Histograma da FR===========================\n");

                altura = MaiorFR*100;
                printf("\n  %% |");
                while (altura !=0){
                    printf("\n%.3d |  ",altura);
                    for (int i = 0; i < numClasseInt; ++i) {
                        printf("%c     ",VetorClasses[i].FrequenciaRelativa*100>=altura?219:' ');
                    }
                    altura--;
                }
                printf("\n");

                printf("___");
                for (int j = 0; j < numClasseInt; ++j) {
                    printf("________");

                }

                printf("\n      C1");
                for (int k = 0; k <numClasseInt-1; ++k) {
                    printf("    C%d", k+2);
                }
                printf("    Classes");


                printf("\n\n=======================================================================\n");

                printf("Digite Enter para voltar ao MENU-->");
                getchar();
                getchar();

                break;
            case 0:
                return 0;
        }
    }while (1);


}