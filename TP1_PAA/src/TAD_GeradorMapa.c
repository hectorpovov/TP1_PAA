#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/TAD_GeradorMapa.h"

#define largMin 6
#define largMax 10
#define altMin 6
#define altMax 10
#define duraMin 40
#define duraMax 50
#define decaiMin 3
#define decaiMax 5
#define regenMin 5
#define regenMax 10

char fig[4] = {'P', '-', '|', '+'};

int gerarNmrAleatorio(int min, int max){
    return (rand() % (max - min + 1)) + min;
}

int setorValido(Mapa *mapa, int y, int x) {
    return y >= 0 && y < mapa->altura && x >= 0 && x < mapa->largura
           && mapa->posicoes[y][x].caractere == '.';
}

void adicionaCruzamento(Mapa *mapa, int y, int x) {
    mapa->posicoes[y][x].caractere = fig[3];
}

void criaNovaRota(Mapa *mapa, int yFim, int xFim){
    int y = 0;
    int x = 0;

    do {
    y = gerarNmrAleatorio(0, mapa->altura - 1);
    x = gerarNmrAleatorio(0, mapa->largura - 1);
    } while (setorEhValido(mapa,y,x));

    adicionaElementos(mapa, y, x, yFim, xFim);
    adicionaElementos(mapa,yFim,xFim,y,x);
}

void adicionaPeca(Mapa *mapa,int *pecas, int y, int x, int yFim, int xFim){
    if(pecas == NULL || *pecas == 0){
        return;
    }else{
        int distanciaFim = abs(yFim - y) + abs(xFim - x);
        if (gerarNmrAleatorio(0,10) % 2 == 0 && distanciaFim > 1) {
            mapa->posicoes[y][x].caractere = 'P';
            (*pecas)--;
        }
    }
}

void adicionaElementos(Mapa *mapa, int y, int x, int yFim, int xFim) {
    int direcao = -1;
    int pecas = 1; //depois mudar para de acordo com a dificuldade

    while (y != yFim || x != xFim) {
        if (setorValido(mapa, y, x)) {
            if (direcao == 1)
                mapa->posicoes[y][x].caractere = fig[1];
            else if (direcao == 2)
                mapa->posicoes[y][x].caractere = fig[2];
            else
                mapa->posicoes[y][x].caractere = fig[0];
        }

        if (y != yFim) {
            if (direcao != 2 && direcao != -1)
                adicionaCruzamento(mapa, y, x);
            if (y < yFim)
                y = y + 1;
            else
                y = y - 1;
            direcao = 2;
        } else if (x != xFim) {
            if (direcao != 1 && direcao != -1)
                adicionaCruzamento(mapa, y, x);
            if (x < xFim)
                x = x + 1;
            else
                x = x - 1;
            direcao = 1;
        }
        adicionaPeca(mapa,&pecas,y,x,yFim,xFim);
        
    }
}

void criaPercursoMapa(Mapa *mapa, int posXIni, int posYIni, int posXfim, int posYfim) {
    printf(" inicio: %d %d", posYIni, posXIni);
    printf(" fim: %d %d\n", posYfim, posXfim);
    adicionaElementos(mapa, posYIni, posXIni, posYfim, posXfim);
    criaNovaRota(mapa,posYfim, posXfim);
}


void adicionaElementosMapa(Mapa *mapa){
    int posY = gerarNmrAleatorio(0, mapa->altura - 1); 
    int posX = gerarNmrAleatorio(0, mapa->largura - 1);
    mapa->posicoes[posY][posX].caractere = 'X';

    int fposY = 0;
    int fposX = 0;
    int distancia = 0;
    do {
        fposY = gerarNmrAleatorio(0, mapa->altura - 1);
        fposX = gerarNmrAleatorio(0, mapa->largura - 1);
        distancia = abs(fposY - posY) + abs(fposX - posX);
    } while (distancia < 2); // garantir 2 de distancia entre X e F pra n dar BO

    mapa->posicoes[fposY][fposX].caractere = 'F';
    criaPercursoMapa(mapa, posX, posY, fposX, fposY);
}

void criaMapaAleatorio(){
    srand(time(NULL));

    FILE *fp;
    char *caminho = "input/entrada_criada.txt";
    fp = fopen(caminho, "w");
    if (fp == NULL)
    {
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

    for (int i = 0; i < altura; i++)
    { // preencher com . para retirar lixo mem
        for (int j = 0; j < largura; j++)
        {
            mapa.posicoes[i][j].caractere = '.';
            mapa.posicoes[i][j].visitado = 0;
        }
    }

    limparMapa(&mapa);

    adicionaElementosMapa(&mapa);

    for (int i = 0; i < altura; i++)
    { // escreve no txt
        for (int j = 0; j < largura; j++)
        {
            fprintf(fp, "%c", mapa.posicoes[i][j].caractere);
            printf("%c ", mapa.posicoes[i][j].caractere);
        }
        fprintf(fp, "\n");
        printf("\n");
    }

    fclose(fp);
    printf("CRIADO\n");
}
