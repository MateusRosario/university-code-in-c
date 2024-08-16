#include <stdio.h>
#include <stdlib.h>

int main()
{
    char opcao,espera,sair,escolha;
    int num_j,fichas_ini,cont=0,j,cont2=0,i,fichas_ap,v,quant,quant_nf,quant_np,pular;
    printf("Iniciando gerenciador...\n...\n...\n...\n            version 8.4. beta\n\n");
    printf("Quantos jogadores?\n");
    scanf("%i",&num_j);
    quant_nf=num_j;
    quant_np=num_j;
    int fichas[num_j],mesa=0,ultima_ap=0;
    int ult_apj[num_j],fugiu[num_j],perdeu[num_j];
    printf("\n\nIniciar jogo com quantas fichas pra cada jogador?\n");
    sair=0;
    do{
        scanf("%i",&fichas_ini);
        if(fichas_ini<5 || fichas_ini%5!=0){
            printf("digite um valor maior que 5 e multiplo de 5.\n");
        }else{
            sair=1;
        }
    }while(sair==0);
    for(i=0;i<num_j;i++){
        fichas[i]=fichas_ini;
        printf("Jogador %i recebe %i fichas...\n",i+1,fichas_ini);
    }

    printf("\n\nvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n\niniciando partida...\n");
    j=num_j;
    for(i=0;i<num_j;i++){
        perdeu[i]=0;
    }
    do{
        ultima_ap=0;
        pular=0;
        for(i=0;i<num_j;i++){
            ult_apj[i]=0;
            fugiu[i]=0;
        }
        quant_nf=quant_np;
        opcao='n';
        if(perdeu[j-1]==0){
            printf("jogador %i embaralha as cartas...\ndistribui as cartas...\ncoloca 5 cartas na mesa...\ndigite C para continuar...\n",j);
            scanf(" %c",&espera);
            printf("\n\niniciar apostas...\n\n");
            j++;
            if(j>num_j){
                j=1;
            }
            cont2=0;
            cont=0;
            do{
                if(fichas[j-1]!=0 && fugiu[j-1]==0){
                    if(quant_nf>1){
                        printf("\n\nVez do jogador %i apostar...  ult.aposta: %i    n>0(aposta) 0(mesa) -1(foge)\n",j,ultima_ap);
                        do{
                            sair='n';
                            if(fichas[j-1]<=ultima_ap){
                                if(ult_apj[j-1]!=ultima_ap){
                                    printf("Jogador %i Deseja apostar tudo? s(sim) n(nao,quer fugir)\n",j);
                                    scanf(" %c",&escolha);
                                    if(escolha=='s'){
                                        printf("\nJogador %i apostou todas as suas %i fichas restantes em sua vitoria.",j,fichas[j-1]);
                                        mesa=mesa+fichas[j-1];
                                        fichas[j-1]=0;
                                        sair='s';
                                    }else{
                                        fugiu[j-1]=1;
                                        sair='s';
                                        quant_nf--;
                                    }
                                }else{
                                    printf("Jogador %i Deseja apostar tudo ou pedir mesa? s(sim, apostar tudo) n(nao, fugir)  m(pedir mesa)\n",j);
                                    scanf(" %c",&escolha);
                                    if(escolha=='s'){
                                        printf("\nJogador %i apostou todas as suas %i fichas restantes em sua vitoria.",j,fichas[j-1]);
                                        mesa=mesa+fichas[j-1];
                                        fichas[j-1]=0;
                                        sair='s';
                                    }else{
                                        if(escolha=='n'){
                                            fugiu[j-1]=1;
                                            sair='s';
                                            quant_nf--;
                                        }else{
                                            printf("Jogador %i pediu mesa.\n\n",j);
                                            sair='s';
                                        }
                                    }
                                }
                            }else{
                                scanf("%d",&fichas_ap);
                                switch (fichas_ap){
                                    case 0:
                                        if(ultima_ap!=0){
                                            if(ultima_ap==ult_apj[j-1]){
                                                printf("Jogador %i pediu mesa.\n\n",j);
                                                sair='s';
                                            }else{
                                                printf("vc nao pode pedir mesa.\n");
                                            }
                                        }else{
                                            printf("vc nao pode pedir mesa ainda.\n");
                                        }
                                        break;
                                    case -1:
                                        printf("\nJogador %i foge desta rodada.\n",j);
                                        fugiu[j-1]=1;
                                        quant_nf--;

                                        sair='s';

                                        break;
                                    default:
                                        if(fichas[j-1]>=fichas_ap){
                                            if(fichas_ap<ultima_ap || fichas_ap<5 || fichas_ap%5!=0){
                                                printf("Aposta invalida, vc deve manter ou aumentar a aposta, e apostar valores maiores e multiplos de 5.\n");
                                            }else{
                                                printf("Jogador %i apostou %i fichas.\n\n",j,fichas_ap);
                                                fichas[j-1]=fichas[j-1]-fichas_ap;
                                                mesa=mesa+fichas_ap;
                                                ultima_ap=fichas_ap;
                                                ult_apj[j-1]=fichas_ap;
                                                sair='s';
                                            }
                                        }else{
                                            printf("vc n eh tao rico(a), digite um valor mais para pobres...\n");
                                        }
                                }
                            }
                        }while(sair=='n');
                        cont++;
                        j++;
                        if(j>num_j){
                            j=1;
                        }
                        system("clear");
                        printf("\n----------------------------------------------------------------------------------\n\nmesa: %i fichas\n",mesa);
                        for(i=0;i<num_j;i++){
                            printf("Jogador %i : %i fichas.\n",i+1,fichas[i]);
                        }
                    }else{
                        cont++;
                        printf("o Jogador %i vence por desistencia do(s) outro(s) Jogador(es).\n\n",j);
                        fichas[j-1]=fichas[j-1]+mesa;
                        mesa=0;
                        pular=1;
                        j++;
                        if(j>num_j){
                            j=1;
                        }
                        opcao='s';
                    }
                }else{
                    cont++;
                    if(quant_nf==1 && fugiu[j-1]==0){
                        printf("o Jogador %i vence por desistencia do(s) outro(s) Jogador(es).\n\n",j);
                        fichas[j-1]=fichas[j-1]+mesa;
                        mesa=0;
                        pular=1;
                        opcao='s';
                    }
                    j++;
                    if(j>num_j){
                        j=1;
                    }
                }
                if(pular==0){
                    if(cont==num_j){
                        cont2++;
                        if(cont2<=5){
                            printf("\n^^^^^^^^^^^^^^^^^^^^^^^^\nVIRE A %i%c CARTA...\nvvvvvvvvvvvvvvvvvvvvvvvv\ndigite C para continuar...\n",cont2,248);
                            scanf(" %c",&espera);
                            system("clear");
                        }
                        cont=0;
                        if(cont2>5){
                            printf("-----------------------------------------------\nDesejam finalizar apostas?   sim(s) nao(n)\n" );
                            scanf(" %c",&opcao);
                        }
                    }
                }
            }while(opcao=='n');
            if(pular==0){
                printf("ocorreu empate? sim(s) nao(n)\n");
                scanf(" %c",&opcao);
                if(opcao=='n'){
                    printf("\nqual jogador ganhou a partida?\n");
                    do{
                        opcao='s';
                        scanf("%i", &v);
                        if(v>num_j || v<1){
                            printf("jogador inexistente\n");
                            opcao='n';
                            printf("\nqual jogador ganhou a partida?\n");
                        }

                    }while(opcao=='n');
                    fichas[v-1]=fichas[v-1]+mesa;
                    mesa=0;
                }else{
                    if(num_j==2){
                        mesa=mesa/2;
                        for(i=0;i<2;i++){
                            fichas[i]=fichas[i]+mesa;
                        }
                    }else{
                        printf("\nquantos jogadores empataram?");
                        scanf("%i",&quant);
                        mesa=mesa/quant;
                        printf("\nquais sao os jogadores:\n");
                        for(i=0;i<quant;i++){
                            do{
                                opcao='s';
                                scanf("%i", &v);
                                if(v>num_j || v<1){
                                    printf("jogador inexistente\n");
                                    opcao='n';
                                    printf("\nquais sao os jogadores:\n");
                                }

                            }while(opcao=='n');
                            fichas[v-1]=fichas[v-1]+mesa;
                        }
                    }
                    mesa=0;
                }
            }
            for(i=0;i<num_j;i++){
                if(fichas[i]<5){
                    printf("Jogador %i perdeu todas as suas fichas.\n",i+1);
                    fichas[i]=0;
                    perdeu[i]=1;
                    quant_np--;
                }else{
                    printf("Jogador %i possui %i fichas\n",i+1,fichas[i]);
                }
            }
            if(quant_np>1){
                printf("\n\nDeseja comecar outra rodada? sim(s) nao(n) \n");
                scanf(" %c",&opcao);
            }else{
                opcao='n';
            }
        }else{
            j++;
            if(j>num_j){
                j=1;
            }
            opcao='s';
        }
    }while(opcao=='s');
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\nStatus final dos jogadortes:\n\n");
    for(i=0;i<num_j;i++){
        if(fichas[i]<5){
            printf("Jogador %i perdeu todas as suas fichas.\n",i+1);
        }else{
            printf("Jogador %i possui %i fichas\n",i+1,fichas[i]);
        }
    }
    return 0;
}
