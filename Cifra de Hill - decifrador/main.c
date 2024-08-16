#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct decifra {
    char* textoEnt;  //ponteiro da mémoria do texto de entrada.
    int key[3][3]; //Matriz que guarda a key.
    char* textoSai; //ponteiro da mémoria do texto de saida.
    int keyInv[3][3]; //Matriz inversa da matriz key.
}decifra;

int entradaTexto(decifra* matriz) { //Função para ler entrada (támbem aloca memoria para o texto de saida);
    char ent;
    int start=0;
    int tam=0;
    int controle=1;
    printf("Digite o texto a ser decifrado: \n");
    getchar();
    ent=getchar(); //le o primeiro char.
    while (ent!='\n'){
        if(ent<32 || ent>126){ //testa se o char é valido para fazer a cifra.
            controle=0;
            ent=32; //substitui o char invalido pelo char ' '(espaço).
        }
        if(start==0) {
            matriz->textoEnt = (char *) malloc(sizeof(char)); //aloca o primeiro espaço para o texto.
            start++;
        }else{
            matriz->textoEnt = (char*)realloc(matriz->textoEnt, sizeof(char)*tam); //Vai realocando a memoria para guardar o texto.
        }
        matriz->textoEnt[tam]=ent; //O ponteiro recebe a entrada.
        tam++;
        ent=getchar(); //Pega os char de entrada.
    }

    return controle;
}

void entradaMatriz(decifra *matriz) {//Lê do usuario a matriz key.
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

int calculaDeterminante(decifra *matriz){//Calcula o determinante da matriz key;
    int Diagonalprinc=0;
    int Diagonalsec=0;
    int temp;
    int l,c,k;

    for(k = 0; k < 3 ; k++ ) {
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
    for(k = 0; k < 3 ; k++ ) {
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

int verificarFatorCoprimo(decifra *matriz, int d) {//Verifica se a variavel d é Cofator de 95.
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

int verificarKey(decifra *matriz){//Calcula o determinante e verifica se é diferente de zero e cofator de 95.
    int determinante;
    determinante = calculaDeterminante(matriz);
    if(determinante == 0){
        return 0;
    }else if(verificarFatorCoprimo(matriz, determinante)==0){
        return 0;
    }else{
        return 1;
    }
}

int inverteDetModular(int det) {//Inverte o determinante modular.
    int mod=95;
    int invDet;
    int continuar=1;
    int i=1;
    do {//Continua até achar o inverso do determinante modular da metriz key.
        invDet=(mod*i+1);
        if(invDet%det==0){
            invDet=invDet/det;
            continuar=0;
        }
        i++;
    }while(continuar);
    return invDet;
}

void calculaMatrizesAuxi(decifra *matriz) {//Calcula os determinantes da matrizes 2x2 resultantes da remoção da coluna e da linha de cada elemento.
    int l,c,kl,kc,dl,dc;
    int Det[2][2]={0,0,0,0};
    for(l = 0; l < 3 ; l++){ //controle da linha da matriz Key.
        for(c = 0; c < 3 ; c++) { //controle da coluna da matriz key.
            dl=0;
            dc=0;
            for(kl = 0; kl < 3 ; kl++) { //controle da linha da matriz key rodando internamente.
                for(kc = 0; kc < 3; kc++){ //controle da coluna da matriz key rodando internamente.
                    if((l!=kl && c!=kc) && dl<2){
                        Det[dl][dc]=matriz->key[kl][kc]; //preenche a matriz de cada termo da matriz inversa;
                        dc++;
                        if(dc>1){
                            dc=0;
                            dl++;
                        }
                    }
                }
            }
            matriz->keyInv[l][c] =(Det[0][0]*Det[1][1])-(Det[0][1]*Det[1][0]); //calcula e preenche os termos da matriz inversa.
        }
    }
}

void transporMatriz(decifra *matriz) {//Transpoe a matriz.
    int matrizTemp[3][3];
    int l,c;
    for(l = 0 ; l < 3 ; l++) {//muda as colunas pelas linhas
        for(c = 0 ; c < 3 ; c++) {
            matrizTemp[c][l] = matriz->keyInv[l][c];
        }
    }

    for(l = 0 ; l < 3 ; l++) {
        for(c = 0 ; c < 3 ; c++) {
            matriz->keyInv[l][c] = matrizTemp[l][c];//copia da matriz temporaria devolta para a matriz key.
        }
    }
}

void cofatorMatriz(decifra *matriz) {//Calcula a Matriz cofator.
    int l,c;
    int coFatores[3][3]={1,-1,1,-1,1,-1,1,-1,1};
    for(l = 0 ; l < 3 ; l++) {
        for(c = 0 ; c < 3 ; c++) {
            matriz->keyInv[l][c]=matriz->keyInv[l][c] * coFatores[l][c];
        }
    }
}

int modulo(int temp) {//Calcula o modulo do numero temp.
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
    return temp;
}

void modularMatriz(decifra *matriz) {//modula a matriz.
    int i,j;
    for ( i = 0; i < 3; ++i) {
        for ( j = 0; j < 3 ; ++j) {
                matriz->keyInv[i][j]=modulo(matriz->keyInv[i][j]);
        }
    }
}

void inverterMatrizMod(decifra *matriz) {//Encontro o inverso modular da matriz key.
    int l,c;
    int determinante;
    int invDeterminante;
    determinante=calculaDeterminante(matriz);
    invDeterminante=inverteDetModular(determinante);
    calculaMatrizesAuxi(matriz);
    cofatorMatriz(matriz);
    transporMatriz(matriz);

    for( l = 0; l < 3 ; l++ ) {
        for (c = 0; c < 3; c++) {
            matriz->keyInv[l][c] = invDeterminante * matriz->keyInv[l][c];
        }
    }

    modularMatriz(matriz);
}

void mostrarMatrizKey(decifra *matriz) {//Imprime a matriz key na tela.
    int l,c;
    for( l = 0; l < 3 ; l++ ) {
        printf("|");
        for (c = 0; c < 3; c++) {
            printf("%d%c",matriz->key[l][c],c!=2?',':'|');
        }
        printf("\n");
    }
}

int multiplicarMatrizes(decifra *matriz, int a, int b, int c, int inserir_pos) {//Multiplica a matriz key, pela matriz de caracteres, obtem  os resultados e coloca no texto de saida.
    int i;
    int temp;
    for( i = 0 ; i<3 ; i++ ){
        temp= (matriz->keyInv[i][0]*a) + (matriz->keyInv[i][1]*b) + (matriz->keyInv[i][2]*c);

        temp=modulo(temp);

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

void codificarMensagem(decifra *matriz) {//Produz a matriz de caracteres que é multiplicada pela matriz key.
    int i;
    int a,b,c;
    int posi=0;
    int tam = strlen(matriz->textoEnt);
    for(i = 0 ; i < tam ; i=i+3 ){

        a=matriz->textoEnt[i]-32;
        if(i+1>tam) {
            b=0;
        }else{
            b = matriz->textoEnt[i + 1] - 32;
        }

        if(i+2>tam) {
            c=0;
        }else {
            c = ((int) matriz->textoEnt[i + 2]) - 32;
        }

        posi=multiplicarMatrizes(matriz, a, b, c, posi);
    }
}

int main() {
    decifra matriz;
    int repetir=0;
    char opcao;
    do {//recebe a matriz key. Repete de o usuario quiser mudar.
        entradaMatriz(&matriz);
        if(verificarKey(&matriz)){
            mostrarMatrizKey(&matriz);
            getchar();
            printf("\nDeseja decifrar uma mensagem com esta Key? s(sim) n(nao)\n");
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
            printf("Deseja decifrar este texto? s(sim) n(nao)");
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
            printf("OBS: pode ocorrer erros na mensagem, verifique a sua entrada.");
            scanf("%c",&opcao);
            if(opcao=='s' || opcao=='S'){
                repetir=0;
            }else{
                repetir=1;
            }
        }
    }while(repetir);

    inverterMatrizMod(&matriz);//Chama a função para inverter a matriz.
    codificarMensagem(&matriz);//Chama a função codificar mensagem.

    printf("\nMensagem Decifrada:\n");// Emprime o texto de Saida.
    int i;
    for(i=0 ; i<strlen(matriz.textoSai);i++){
        printf("%c",matriz.textoSai[i]);
    }
}