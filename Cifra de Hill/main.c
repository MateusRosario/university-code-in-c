#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cifra{ //Struct que contem a matriz chave, o endereço da mémoria dos textos de saida e entrada.
    int key[3][3];
    char* textoEnt;
    char* textoSai;
    int tamsai;
}cifra;

int entradaTexto(cifra* matriz) {//Lê a entrada de texto.
    char ent;
    int start=0;
    int tam=0;
    int controle=1;
    printf("Digite o texto a ser cifrado: \n");
    getchar();
    ent=getchar();
    while (ent!='\n'){
        if(ent<32 || ent>126){
            controle=0;
            ent=32;
        }
        if(start==0) {
            matriz->textoEnt = (char *) malloc(sizeof(char));
            start++;
        }else{
            matriz->textoEnt = (char*)realloc(matriz->textoEnt, sizeof(char)*tam);
        }
        matriz->textoEnt[tam]=ent;
        tam++;
        ent=getchar();
    }

    return controle;
}

void entradaMatriz(cifra *matriz) {//Lê do usuario a matriz key.
    int l,c,k,i;
    int entrada;
    char modelo[3][3]={'-','-','-','-','-','-','-','-','-'};
    printf("Digite os termos da matriz chave: \n");


    for( l = 0; l < 3 ; l++ ){
        for( c = 0 ; c < 3 ; c++ ){

            printf("\n");
            for( k = 0; k < 3 ; k++ ){
                printf("|");
                for( i = 0 ; i < 3 ; i++ ){
                    if(k==l && i==c) {
                        modelo[k][i] = '_';
                    }
                    printf("%c%c",modelo[k][i],i!=2?',':'|');
                    if(k==l && i==c) {
                        modelo[k][i] = '+';
                    }
                }
                printf("\n");
            }

            printf("\nDigite o termo:\n");
            scanf("%d",&matriz->key[l][c]);
        }
    }
}

void mostrarMatriz(cifra *matriz) { //Imprime a matriz key na tela.
    int l,c;
    for( l = 0; l < 3 ; l++ ) {
        printf("|");
        for (c = 0; c < 3; c++) {
            printf("%d%c",matriz->key[l][c],c!=2?',':'|');
        }
        printf("\n");
    }
}

int calculaDeterminante(cifra *matriz){ //Calcula o determinante da matriz key;
    int Diagonalprinc=0;
    int Diagonalsec=0;
    int temp;
    int l,c,k;

    for(k = 0; k < 3 ; k++ ) {//Calcula a diagonal principal.
        c=k;
        temp=1;
        for (l = 0; l < 3; l++) {

            if(c>2){
                c -= 3;
            }

            temp = temp * matriz->key[l][c];
            c++;
        }
        Diagonalprinc += temp;
    }

    c=2;
    for(k = 0; k < 3 ; k++ ) {//Calcula a diagonal secundaria.
        temp=1;
        for (l = 0; l < 3; l++) {

            if(c<0){
                c += 3;
            }
            temp = temp * matriz->key[l][c];
            c--;
        }
        c++;
        Diagonalsec += temp;
    }


    return (Diagonalprinc - Diagonalsec);

}

int verificarFatorCoprimo( int d) {//Verifica se a variavel d é Cofator de 95.
    int i;
    int a;
    if(d<95){
        a=d;
    }else{
        a=95;
    }
    for(i = 2; i <=a  ; i++){
        if(95%i==0 && d%i==0){
            return 0;
        }
    }
    return 1;
}

int verificarKey(cifra *matriz){ //Calcula o determinante e verifica se é diferente de zero e cofator de 95.
    int determinante;
    determinante = calculaDeterminante(matriz);
    if(determinante == 0){
        return 0;
    }else if(verificarFatorCoprimo( determinante)==0){
        return 0;
    }else{
        return 1;
    }
}

int multiplicarMatrizes(cifra *matriz, int a, int b, int c, int inserir_pos) {//Multiplica a matriz key, pela matriz de caracteres, obtem  os resultados e coloca no texto de saida.
    int i;
    int temp;
    for( i = 0 ; i<3 ; i++ ){
        temp= (matriz->key[i][0]*a) + (matriz->key[i][1]*b) + (matriz->key[i][2]*c);

        if(temp>=0) {
            temp = temp % 95;
        }else{
            if(temp%95==0){
                temp=0;
            }else{
                if(temp%95<0){
                    temp=95-((-1)*(temp%95));
                }else{
                    temp=95-(temp%95);
                }

            }
        }


        if(inserir_pos==0){
            matriz->textoSai=(char*)malloc(sizeof(char));
        }else{
            matriz->textoSai=(char*)realloc(matriz->textoSai,sizeof(char)*(inserir_pos+1));
        }

        matriz->textoSai[inserir_pos]=(char)(temp+32);
        inserir_pos++;
    }
    return inserir_pos;
}

void codificarMensagem(cifra *matriz) {//Produz a matriz de caracteres que é multiplicada pela matriz key.
    int i;
    int a,b,c;
    int posi=0;
    int tam = strlen(matriz->textoEnt);
    for(i = 0 ; i < tam ; i=i+3 ){

        a=matriz->textoEnt[i]-32;

        if(i+1>=tam) {
            b=0;
        }else{
            b = matriz->textoEnt[i + 1] - 32;
        }

        if(i+2>=tam) {
            c=0;
        }else {
            c = ((int) matriz->textoEnt[i + 2]) - 32;
        }

        posi=multiplicarMatrizes(matriz, a, b, c, posi);
    }
}

void main() {
    cifra matriz;
    int repetir=0;
    char opcao;

    do {//recebe a matriz key. Repete de o usuario quiser mudar.
        entradaMatriz(&matriz);
        if(verificarKey(&matriz)){
            mostrarMatriz(&matriz);
            getchar();
            printf("\nDeseja cifrar uma mensagem com esta Key? s(sim) n(nao)\n");
            scanf("%c",&opcao);
            if(opcao=='s' || opcao=='S'){
                repetir=0;
            }else{
                repetir=1;
            }
        }else{
            repetir=1;
            printf("Matriz Key invalida para esta cifra.\n\n");
        }
    }while(repetir);

    do{//recebe a matriz key. Repete de o usuario quiser mudar.
        if(entradaTexto(&matriz)){
            printf("%s\n",matriz.textoEnt);
            printf("Deseja cifrar este texto? s(sim) n(nao)");
            scanf("%c",&opcao);
            if(opcao=='s' || opcao=='S'){
                repetir=0;
            }else{
                repetir=1;
                free(matriz.textoEnt);
                free(matriz.textoSai);
            }
        }else{
            getchar();
            printf("Voce digitou algum caracter invalido. Continuar mesmo assim? s(sim) n(nao)\n");
            printf("OBS: os caracteres invalidos serão substituidos por ' '(espaço) ");
            scanf("%c",&opcao);
            if(opcao=='s' || opcao=='S'){
                repetir=0;
            }else{
                repetir=1;
            }
        }
    }while(repetir);

    codificarMensagem(&matriz);//Chama a função codificar mensagem.

    printf("Mensagem Cifrada:\n");// Emprime o texto de Saida.
    int i;
    for ( i = 0; i <strlen(matriz.textoSai); ++i) {
        printf("%c",matriz.textoSai[i]);
    }
}