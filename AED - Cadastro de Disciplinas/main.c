#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct disciplina{
    int periodo;
    char *nome;
    char *professor;
    char *ementa;
}disciplina;

typedef struct no{
    struct no *anterior;
    disciplina *dados;
    struct no *proximo;
}no;

typedef struct descritor{
    struct no *inicio;
    int qt;
    struct no *fim;
}descritor;

char* input(char *input){
    char *saida;
    char ent;
    int tam=0;
    do {
        printf("%s\n", input);
        ent = getchar();
    }while(ent=='\n');
    saida = (char*)malloc(sizeof(char));
    saida[tam]=ent;
    tam++;
    ent=getchar();
    while(ent!='\n'){
        saida = (char*)realloc(saida,sizeof(char)*tam+1);
        saida[tam]=ent;
        tam++;
        ent=getchar();
    }
    return saida;
}

char toUpercase(char l){
    if(l>=97 && l<=122){
        l=l-32;
    }
    return l;
}

char* StringtoUpercase(char *String){
    for(int i=0; i<strlen(String);i++){
        String[i]=toUpercase(String[i]);
    }

    return String;
}

int comparator(char* string1,char* string2){
    for(int i=0; i<strlen(string1) || i<strlen(string2) ;i++){
        if((string1[i])<(string2[i])){
            return -1;
        }else if((string1[i])>(string2[i])){
            return 1;
        }
    }

    if(strlen(string1)<strlen(string2)){
        return -1;
    }else if(strlen(string1)>strlen(string2)){
        return 1;
    }else{
        return 0;
    }
}

int insert(descritor *lista){
    no *novo=(no*)malloc(sizeof(no));
    novo->dados=(disciplina*)malloc(sizeof(disciplina));
    novo->dados->nome=StringtoUpercase(input("Digite o Nome da Disciplina:"));
    novo->dados->periodo=atoi(input("Digite o Numero do Periodo:"));
    novo->dados->professor=StringtoUpercase(input("Digite o Nome do Professor Respensavel:"));
    novo->dados->ementa=StringtoUpercase(input("Digite a Ementa da Disciplina:"));

    if(lista->qt!=0){ //Verifica se a lista possui algum elemento
        if(novo->dados->periodo<lista->inicio->dados->periodo){//Verifica se a nova disciplina esta num periodo não cadastrado ainda abaixo do periodo mais baixo;
            //Coloca na posição inicial da lista;
            novo->proximo=lista->inicio;
            novo->anterior=lista->fim;
            lista->inicio->anterior=novo;
            lista->fim->proximo=novo;
            lista->inicio=novo;
            lista->qt++;
            return 1;
        }else if(novo->dados->periodo>lista->fim->dados->periodo){//Verifica se a nova disciplina esta num periodo não cadastrado ainda acima do periodo mais acima.
            //coloca na posição final da lista
            novo->anterior=lista->fim;
            novo->proximo=lista->inicio;
            lista->fim->proximo=novo;
            lista->inicio->anterior=novo;
            lista->fim=novo;
            lista->qt++;
            return 1;
        }else if(((novo->dados->periodo)-(lista->inicio->dados->periodo))<=((lista->fim->dados->periodo)-(novo->dados->periodo))){//Verifica se compensa mais procurar o periodo do novo elemento do inicio para o fim ou do fim para o inicio
            //Procura o periodo do novo elemento do inicio para o fim;
            if(novo->dados->periodo==lista->inicio->dados->periodo){//Verifica se o novo elemento pertence ao periodo mais baixo já cadastrado.
                //procura a posição do novo elemento no periodo mais baixo já casdastrado.
                if(comparator(novo->dados->nome,lista->inicio->dados->nome)==-1){//Verifica se a nova disciplina esta na primeira posição do periodo
                    //Coloca na posição inicial da lista;
                    novo->proximo=lista->inicio;
                    novo->anterior=lista->fim;
                    lista->inicio->anterior=novo;
                    lista->fim->proximo=novo;
                    lista->inicio=novo;
                    lista->qt++;
                    return 1;
                }else if(comparator(novo->dados->nome,lista->inicio->dados->nome)==0){//Verifica se já existe está disciplina na primeira posição do periodo
                    //retorna false
                    return 0;
                }else{
                    //procura a posição da nova disciplina no periodo mais baixo
                    no *aux=lista->inicio;
                    do{
                        if(comparator(novo->dados->nome,aux->dados->nome)==-1) {//verifica se esta é a posição da nova disciplina
                            //insere novo elemento nesta posição
                            novo->proximo = aux;
                            novo->anterior = aux->anterior;
                            aux->anterior->proximo = novo;
                            aux->anterior = novo;
                            lista->qt++;
                            return 1;
                        }else if(comparator(novo->dados->nome,aux->dados->nome)==0){//verifica se esta disciplina já existe
                            //retorna false
                            return 0;
                        }else if(aux->dados->periodo!=aux->proximo->dados->periodo){//verifica se é o ultimo elemento do periodo
                            //insiere novo elemento na ultima posição do periodo
                            novo->proximo=aux->proximo;
                            novo->anterior=aux;
                            aux->proximo->anterior=novo;
                            aux->proximo=novo;
                            lista->qt++;
                            return 1;
                        }else if(aux->dados->nome==lista->fim->dados->nome){//Verifica se é o ultimo elemento da lista
                            //insere novo elemento na ultima posição da lista
                            novo->proximo=lista->inicio;
                            novo->anterior=lista->fim;
                            lista->inicio->anterior=novo;
                            lista->fim->proximo=novo;
                            lista->fim=novo;
                            lista->qt++;
                            return 1;
                        }
                        aux=aux->proximo;
                    }while(1);
                }
            }else{
                //procura em qual periodo esta o novo elemento
                no *aux = lista->inicio->proximo;
                do{
                    if(novo->dados->periodo<aux->dados->periodo){//Verifica se a nova disciplina esta em um periodo não existente.
                        //insere a nova disciplina na posição anterior a aux
                        novo->proximo = aux;
                        novo->anterior = aux->anterior;
                        aux->anterior->proximo=novo;
                        aux->anterior=novo;
                        lista->qt++;
                        return 1;
                    }else if(novo->dados->periodo==aux->dados->periodo){//Verifica se a nova disciplina esta no mesmo periodo de aux
                        //procura a posição da nova disciplina neste periodo de aux
                        if(comparator(novo->dados->nome,aux->dados->nome)==-1){//Verifica se a nova disciplina esta na primeira posição do periodo
                            //insere a nova disciplina na posição anterior a aux
                            novo->proximo = aux;
                            novo->anterior = aux->anterior;
                            aux->anterior->proximo=novo;
                            aux->anterior=novo;
                            lista->qt++;
                            return 1;
                        }else if(comparator(novo->dados->nome,aux->dados->nome)==0){//Verifica se já existe está disciplina na primeira posição do periodo
                            //retorna false
                            return 0;
                        }else{
                            //procura a posição da nova disciplina neste periodo

                            do{
                                if(comparator(novo->dados->nome,aux->dados->nome)==-1) {//verifica se esta é a posição da nova disciplina
                                    //insere novo elemento nesta posição
                                    novo->proximo = aux;
                                    novo->anterior = aux->anterior;
                                    aux->anterior->proximo = novo;
                                    aux->anterior = novo;
                                    lista->qt++;
                                    return 1;
                                }else if(comparator(novo->dados->nome,aux->dados->nome)==0){//verifica se esta disciplina já existe
                                    //retorna false
                                    return 0;
                                }else if(aux->dados->periodo!=aux->proximo->dados->periodo){//verifica se é o ultimo elemento do periodo
                                    //insiere novo elemento na ultima posição do periodo
                                    novo->proximo=aux->proximo;
                                    novo->anterior=aux;
                                    aux->proximo->anterior=novo;
                                    aux->proximo=novo;
                                    lista->qt++;
                                    return 1;
                                }
                                aux=aux->proximo;
                            }while(1);
                        }
                    }
                    aux=aux->proximo;
                }while(1);
            }
        }else{
            //Procura o periodo do novo elemento do fim para o inicio;

            if(novo->dados->periodo==lista->fim->dados->periodo){//Verifica se o novo elemento pertence ao periodo mais acima já cadastrado.
                //procura a posição do novo elemento no periodo mais acima já casdastrado.
                if(comparator(novo->dados->nome,lista->fim->dados->nome)==1){//Verifica se a nova disciplina esta na ultima posição do periodo
                    //Coloca na posição final da lista;
                    novo->proximo=lista->inicio;
                    novo->anterior=lista->fim;
                    lista->fim->proximo=novo;
                    lista->inicio->anterior=novo;
                    lista->fim=novo;
                    lista->qt++;
                    return 1;
                }else if(comparator(novo->dados->nome,lista->fim->dados->nome)==0){//Verifica se já existe está disciplina na ultima posição do periodo
                    //retorna false
                    return 0;
                }else{
                    //procura a posição da nova disciplina no periodo mais acima
                    no *aux=lista->fim;
                    do{
                        if(comparator(novo->dados->nome,aux->dados->nome)==1) {//verifica se esta é a posição da nova disciplina
                            //insere novo elemento nesta posição
                            novo->proximo = aux->proximo;
                            novo->anterior = aux;
                            aux->proximo->anterior = novo;
                            aux->proximo = novo;
                            lista->qt++;
                            return 1;
                        }else if(comparator(novo->dados->nome,aux->dados->nome)==0){//verifica se esta disciplina já existe
                            //retorna false
                            return 0;
                        }else if(aux->dados->periodo!=aux->anterior->dados->periodo){//verifica se é o primeiro elemento do periodo
                            //insiere novo elemento na primeira posição do periodo
                            novo->proximo=aux;
                            novo->anterior=aux->anterior;
                            aux->anterior->proximo=novo;
                            aux->anterior=novo;
                            lista->qt++;
                            return 1;
                        }else if(aux->dados->nome==lista->inicio->dados->nome){//verifica se a nova disciplina ficara como primeiro elemento da lista
                            //insere novo elemento na primeira posição da lista
                            novo->proximo=lista->inicio;
                            novo->anterior=lista->fim;
                            lista->inicio->anterior=novo;
                            lista->fim->proximo=novo;
                            lista->inicio=novo;
                            lista->qt++;
                        }
                        aux=aux->anterior;
                    }while(1);
                }
            }else{
                //procura em qual periodo esta o novo elemento
                no *aux = lista->fim;
                do{
                    if(novo->dados->periodo>aux->dados->periodo){//Verifica se a nova disciplina esta em um periodo não existente.
                        //insere a nova disciplina na posição posterior a aux
                        novo->proximo = aux->proximo;
                        novo->anterior = aux;
                        aux->proximo->anterior=novo;
                        aux->proximo=novo;
                        lista->qt++;
                        return 1;
                    }else if(novo->dados->periodo==aux->dados->periodo){//Verifica se a nova disciplina esta no mesmo periodo de aux
                        //procura a posição da nova disciplina neste periodo de aux
                        if(comparator(novo->dados->nome,aux->dados->nome)==1){//Verifica se a nova disciplina esta na Ultima posição do periodo
                            //insere a nova disciplina na posição posterior a aux
                            novo->proximo = aux->proximo;
                            novo->anterior = aux;
                            aux->proximo->anterior=novo;
                            aux->proximo=novo;
                            lista->qt++;
                            return 1;
                        }else if(comparator(novo->dados->nome,aux->dados->nome)==0){//Verifica se já existe está disciplina na ultima posição do periodo
                            //retorna false
                            return 0;
                        }else{
                            //procura a posição da nova disciplina neste periodo

                            do{
                                if(comparator(novo->dados->nome,aux->dados->nome)==1) {//verifica se esta é a posição da nova disciplina
                                    //insere novo elemento nesta posição
                                    novo->proximo = aux->proximo;
                                    novo->anterior = aux;
                                    aux->proximo->anterior=novo;
                                    aux->proximo=novo;
                                    lista->qt++;
                                    return 1;
                                }else if(comparator(novo->dados->nome,aux->dados->nome)==0){//verifica se esta disciplina já existe
                                    //retorna false
                                    return 0;
                                }else if(aux->dados->periodo!=aux->anterior->dados->periodo){//verifica se é o primeiro elemento do periodo
                                    //insiere novo elemento na ultima posição do periodo
                                    novo->proximo=aux;
                                    novo->anterior=aux->anterior;
                                    aux->anterior->proximo=novo;
                                    aux->anterior=novo;
                                    lista->qt++;
                                    return 1;
                                }
                                aux=aux->anterior;
                            }while(1);
                        }
                    }
                    aux=aux->anterior;
                }while(1);
            }
        }
    }else{
        //Coloca o novo no como primeiro e ultimo elemento da lista
        novo->proximo=novo;
        novo->anterior=novo;
        lista->inicio=novo;
        lista->fim=novo;
        lista->qt++;
        return 1;
    }
}

int rem(descritor *lista){
    if(lista->qt!=0){
        char* remover = StringtoUpercase(input("Digite o Nome da Disciplina que Deseja Remover:"));
        if(comparator(remover, lista->inicio->dados->nome)==0){
            no *aux=lista->inicio;
            aux->proximo->anterior=aux->anterior;
            aux->anterior->proximo=aux->proximo;
            lista->inicio=aux->proximo;
            free(aux);
            lista->qt--;
            return 1;
        }else if(comparator(remover, lista->fim->dados->nome)==0){
            no *aux=lista->fim;
            aux->proximo->anterior=aux->anterior;
            aux->anterior->proximo=aux->proximo;
            lista->fim=aux->anterior;
            free(aux);
            lista->qt--;
            return 1;
        }else{
            no *aux = lista->inicio->proximo;

            do{
                if(comparator(remover, aux->dados->nome)==0){
                    aux->proximo->anterior=aux->anterior;
                    aux->anterior->proximo=aux->proximo;
                    free(aux);
                    lista->qt--;
                    return 1;
                }else if(comparator(aux->proximo->dados->nome, lista->fim->dados->nome)==0){
                    return 0;
                }
                aux=aux->proximo;
            }while(1);
        }
    }else{
        return -1;
    }
}

void printDis(disciplina *dados){
    printf("Nome:[%s]          ",dados->nome);
    printf("[%d°Periodo]\n\n",dados->periodo);
    printf("Professor:[%s]\n\n",dados->professor);
    int cont=0;
    printf("Ementa:[");
    for(int i=0; i<strlen(dados->ementa);i++){
        printf("%c",dados->ementa[i]);
        cont++;
        if(cont>70){
            printf("%c\n",dados->ementa[i]==' ' || dados->ementa[i]==',' || dados->ementa[i]=='.'?' ':'_');
        }
    }
    printf("]\n");
}

int visDis(no *dis){
    no *aux=dis;
    char opc;
    do {

        printf("\n\n=======================  Disciplina  ===================\n");
        printf("----------------------------------------------------------\n");
        printDis(aux->dados);
        printf("----------------------------------------------------------\n");
        printf("\n| 1 Anterior |   | 2 Voltar |   | 0 Menu |   | 3 Proximo |\n");
        printf("========================================================\n");
        opc=getchar();
        getchar();

        switch (opc){
            case '1':
                aux=aux->anterior;
                break;
            case '2':
                return 0; //retornara para a função que visualiza por periodo;
            case '0':
                return 2; //retornara para o menu;
            case '3':
                aux=aux->proximo;
                break;
        }
    }while(1);
}

int printPer(no *auxIn, no *auxFn){
    int i;
    no *aux=auxIn;
    int parar=0;
    for(i=1; parar==0 ;i++,aux=aux->proximo){
        printf("%d. %s;\n",i,aux->dados->nome);

        if(comparator(aux->dados->nome,auxFn->dados->nome)==0){
            parar=1;
        }
    }
}

int pesquisarPer(descritor *lista,int pesquisar){
    no *auxIn;
    no *auxFn;
    char procurando;
    char opc;

    if(lista->qt!=0){//Verifica se a lista está vazia.
        //Procurarando o no do final do periodo ou do inicio;
        if(pesquisar==lista->inicio->dados->periodo){//Verifica se o inicio do periodo pesquisado é o inicio da lista.
            auxIn=lista->inicio;
            procurando='f';
        }else if(pesquisar==lista->fim->dados->periodo){//Verifica se o final do periodo pesquisado é o final da lista.
            auxFn=lista->fim;
            procurando='i';
        }else if((pesquisar-lista->inicio->dados->periodo)<=(lista->fim->dados->periodo-pesquisar)){ //Verifica se compensamais procurar o periodo do inicio paro o fim, ou do fim para o inicio.
            //procura a posição inicial do periodo.
            auxIn=lista->inicio->proximo;
            do{
                if(pesquisar==auxIn->dados->periodo){//Verifica se esta é a posição inicial do periodo.
                    procurando='f';//status procurando é igual a final.
                    break;
                }else if(comparator(auxIn->dados->nome,lista->fim->dados->nome)==0){//verifica se não existe nenhuma disciplina com este periodo na lista
                    return 0;
                }

                auxIn=auxIn->proximo;
            }while(1);

        }else{
            //procura a posição final do periodo.
            auxFn=lista->fim->anterior;
            do{
                if(pesquisar==auxFn->dados->periodo){//verifica se esta é a posição final do periodo.
                    procurando='i';//status procurando é igual a inicio.
                    break;
                }else if(comparator(auxFn->dados->nome,lista->inicio->dados->nome)==0){//verifica se não existe nenhuma disciplina com este periodo na lista
                    return 0;
                }
                auxFn=auxFn->anterior;
            }while(1);
        }

        do {
            if (procurando == 'f') {//Verifica se é para procurar o final ou o inicio do periodo.
                //procura o final do periodo.
                auxFn = auxIn;

                do {
                    if (auxFn->proximo->dados->periodo != auxIn->dados->periodo) {//verifica se este é o final do periodo
                        break;
                    } else if (comparator(auxFn->dados->nome,lista->fim->dados->nome)==0) {//verifica se a posição final do periodo é o final da lista.
                        break;
                    }

                    auxFn = auxFn->proximo;
                } while (1);

            } else if(procurando == 'i'){
                //procura o inicio do periodo.
                auxIn = auxFn;
                do {
                    if (auxIn->anterior->dados->periodo != auxIn->dados->periodo) {//verifica se este é o inicio do periodo
                        break;
                    } else if (comparator(auxIn->dados->nome, lista->inicio->dados->nome)==0) {//verifica se a posição final do periodo é o final da lista.
                        break;
                    }

                    auxIn = auxIn->anterior;
                } while (1);
            }

            printf("==========================================  Periodo  =========================================\n");
            printf("----------------------------------------------------------------------------------------------\n");
            printf("                                          %d° PERIODO                                         \n", auxIn->dados->periodo);
            printPer(auxIn, auxFn);
            printf("----------------------------------------------------------------------------------------------\n");
            printf("                        |1 Anterior|  |2 Detalhes|  |0 Menu|  |3 Proximo|");
            opc=(char) getchar();
            getchar();
            printf("\n==============================================================================================\n");

            switch (opc) {
                case '1':
                    auxFn = auxIn->anterior;
                    procurando = 'i';
                    break;
                case '2':
                    if((visDis(auxIn))==2){
                        return 1;
                    }
                    break;
                case '3':
                    auxIn = auxFn->proximo;
                    procurando = 'f';
                    break;
                case '0':
                    return 1;
                default:
                    procurando = 'n';
                    break;
            }
        }while(1);

    }else{
        return -1;
    }
}

int pesquisarDis(descritor *lista){
    if(lista->qt!=0){
        char* pesquisar = StringtoUpercase(input("Digite o Nome da Disciplina que Deseja Pesquisar:"));
        if(comparator(pesquisar, lista->inicio->dados->nome)==0){
            if(visDis(lista->inicio)==0){
                pesquisarPer(lista,lista->inicio->dados->periodo);
            }
            return 1;
        }else if(comparator(pesquisar, lista->fim->dados->nome)==0){
            if(visDis(lista->fim)==0){
                pesquisarPer(lista,lista->fim->dados->periodo);
            }
            return 1;
        }else{
            no *aux = lista->inicio->proximo;
            do{
                if(comparator(pesquisar, aux->dados->nome)==0){
                    if(visDis(aux)==0){
                        pesquisarPer(lista,aux->dados->periodo);
                    }
                    return 1;
                }else if(comparator(aux->proximo->dados->nome, lista->fim->dados->nome)==0){
                    return 0;
                }
                aux=aux->proximo;
            }while(1);
        }
    }else{
        return -1;
    }
}

int main() {
    //iniciando lista;
    descritor lista;
    lista.inicio = NULL;
    lista.qt = 0;
    lista.fim = NULL;
    //-----------------------------
    char opc;//variavel que guarda a escolha de ação do Usuario
    //Laço de ações;
    int saida;

    do {
        printf("\n====================MENU==================\n");
        printf("(1) Cadastrar Disciplina\n");
        printf("(2) Remover Cadastro de Disciplina\n");
        printf("(3) Pesquisar Disciplina Cadastrda\n");
        printf("(4) Pesquisar Disciplinas Cadastradas por periodo\n");
        printf("(5) Listar Disciplinas Cadastradas\n");
        printf("(0) Sair\n");
        scanf("%c",&opc);
        getchar();
        printf("\n===========================================\n");
        switch (opc) {
            case '1':
                if(insert(&lista)){
                    printf("\n[Disciplina Cadastrada com Sucesso]\n");
                }else{
                    printf("\n[Esta Disciplina já foi Cadastrada]\n");
                }
                break;
            case '2':
                saida = rem(&lista);
                if(saida==1) {
                    printf("\n[Disciplina Removida com Sucesso]\n");
                }else if(saida==0){
                    printf("\n[Esta disciplina não foi cadastrada]\n");
                }else{
                    printf("\n[Não há Disciplinas Cadastradas]\n");
                }
                break;
            case '3':
                saida = pesquisarDis(&lista);
                if(saida==0){
                    printf("\n[Esta disciplina não foi cadastrada]\n");
                }else if(saida== -1){
                    printf("\n[Não há Disciplinas Cadastradas]\n");
                }
                break;
            case '4':
                saida = pesquisarPer(&lista,atoi(input("Digite o Numero do Periodo que deseja Visualiza: ")));
                if(saida==0){
                    printf("\n[Esta disciplina não foi cadastrada]\n");
                }else if(saida==-1){
                    printf("\n[Não há Disciplinas Cadastradas]\n");
                }
                break;
            case '5':
                if(lista.qt!=0){
                    pesquisarPer(&lista,lista.inicio->dados->periodo);
                }else{
                    printf("\n[Não há Disciplinas Cadastradas]\n");
                }
                break;
            case '0':
                return 0;
            default:
                break;
        }
    }while(1);
}