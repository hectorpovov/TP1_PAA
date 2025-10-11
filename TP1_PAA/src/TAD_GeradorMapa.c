#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/TAD_Mapa.h"

#define largMin 5
#define largMax 10
#define altMin 5
#define altMax 10
#define duraMin 5
#define duraMax 10
#define decaiMin 5
#define decaiMax 10
#define regenMin 5
#define regenMax 10

int gerarNmrAleatorio(int min, int max){
    return (rand() % (max - min + 1)) + min; 
}

void adicionaElementosMapa(Mapa *mapa){
    int posY = gerarNmrAleatorio(0, mapa->altura - 1);
    int posX = gerarNmrAleatorio(0, mapa->largura - 1);
    mapa->posicoes[posY][posX].caractere = 'X';

    posY = gerarNmrAleatorio(0, mapa->altura - 1);
    posX = gerarNmrAleatorio(0, mapa->largura - 1);
    mapa->posicoes[posY][posX].caractere = 'F';
}

void criaMapaAleatorio(){
    srand(time(NULL));

    FILE *fp;
    char *caminho = "input/entrada_criada.txt";
    fp = fopen(caminho, "w");
    if(fp == NULL){
        printf("Erro ao criar arquivo\n");
        return;
    }

    int largura = gerarNmrAleatorio(largMin, largMax);
    int altura = gerarNmrAleatorio(altMin, altMax);
    int durabilidade = gerarNmrAleatorio(duraMin, duraMax);
    int decaimento = gerarNmrAleatorio(decaiMin, decaiMax);
    int regeneracao = gerarNmrAleatorio(regenMin, regenMax);

    fprintf(fp, "%d %d %d\n", durabilidade, decaimento, regeneracao);
    fprintf(fp, "%d %d\n", altura, largura);

    Mapa mapa;

    InicializaMapaVazio(&mapa, altura, largura);

    for(int i = 0; i < altura; i++){ //preencher com . para retirar lixo mem
        for(int j = 0; j < largura; j++){
            mapa.posicoes[i][j].caractere = '.';
            mapa.posicoes[i][j].visitado = 0;
        }
    }

    adicionaElementosMapa(&mapa);

    for(int i = 0; i < altura; i++){ //escreve no txt
        for(int j = 0; j < largura; j++){
            fprintf(fp, "%c", mapa.posicoes[i][j].caractere);
            printf("%c ", mapa.posicoes[i][j].caractere);
        }
        fprintf(fp, "\n");
        printf("\n");
    }

    fclose(fp);
    printf("CRIADO\n");
}
