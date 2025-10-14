#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/TAD_GeradorMapa.h"

char fig[4] = {'P', '-', '|', '+'};

int gerarNmrAleatorio(int min, int max){
    return (rand() % (max - min + 1)) + min;
}

int setorValido(Mapa *mapa, int y, int x) {
    if (y < 0 || y >= mapa->altura || x < 0 || x >= mapa->largura)
        return 0;

    char c = mapa->posicoes[y][x].caractere;

    return (c == '.');
}

void adicionaCruzamento(Mapa *mapa, int y, int x) {
    if(mapa->posicoes[y][x].caractere == 'F'){
        return;
    }else
    mapa->posicoes[y][x].caractere = fig[3];
}

void criaNovaRota(Mapa *mapa,int *pecas, int yFim, int xFim){
    int y = 0;
    int x = 0;

   do {
        y = gerarNmrAleatorio(0, mapa->altura - 1);
        x = gerarNmrAleatorio(0, mapa->largura - 1);
        
    }while ((abs(yFim - y) <= 1 || abs(xFim - x) <= 1)|| !setorValido(mapa, y, x) 
    || mapa->posicoes[y][x].caractere == 'F');

    //mapa->posicoes[y][x].caractere = 'G'; //debugs

    fazCaminhoEntrePontos(mapa,pecas, y, x, yFim, xFim);
    fazCaminhoEntrePontos(mapa,pecas,yFim,xFim,y,x);
}

void adicionaPeca(Mapa *mapa,int *pecas, int y, int x, int yFim, int xFim){
    if(pecas == NULL || *pecas <= 0 || mapa->posicoes[y][x].caractere == 'F'){
        return;
    }else{
        int distanciaFim = abs(yFim - y) + abs(xFim - x);
        if (gerarNmrAleatorio(0,10) % 2 == 0 && distanciaFim > 1) {
            mapa->posicoes[y][x].caractere = 'P';
            (*pecas)--;
        }
    }
}

void fazCaminhoEntrePontos(Mapa *mapa, int *pecas, int y, int x, int yFim, int xFim) {
    int direcao = -1;

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
        adicionaPeca(mapa,pecas,y,x,yFim,xFim);
        
    }
}

void criaPercursoMapa(Mapa *mapa, int *pecas, int posXIni, int posYIni, int posXfim, int posYfim) {
    printf(" inicio: %d %d", posYIni, posXIni);
    printf(" fim: %d %d\n", posYfim, posXfim);
    fazCaminhoEntrePontos(mapa,pecas, posYIni, posXIni, posYfim, posXfim);
    criaNovaRota(mapa,pecas,posYIni, posXIni);
}


void preencheMapa(Mapa *mapa, int *pecas){
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
    criaPercursoMapa(mapa, pecas, posX, posY, fposX, fposY);
}

void criaMapaAleatorio(){
    srand(time(NULL));
    
    Mapa mapa;
    int pecas = 1;
    int caso = 0;

    int largura = gerarNmrAleatorio(largMin, largMax);
    int altura = gerarNmrAleatorio(altMin, altMax);
    int durabilidade = gerarNmrAleatorio(duraMin, duraMax);
    int decaimento = gerarNmrAleatorio(decaiMin, decaiMax);
    int regeneracao = gerarNmrAleatorio(regenMin, regenMax);
    
    InicializaMapaVazio(&mapa, altura, largura);
    limparMapa(&mapa);

    for (int i = 0; i < altura; i++)
    { // preencher com . para retirar lixo mem
        for (int j = 0; j < largura; j++)
        {
            mapa.posicoes[i][j].caractere = '.';
            mapa.posicoes[i][j].visitado = 0;
        }
    }

    FILE *fp;
    char *caminho = "input/entrada_criada.txt";
    fp = fopen(caminho, "w");
    if (fp == NULL)
    {
        printf("Erro ao criar arquivo\n");
        return;
    }

    printf("Selecione a Dificuldade:\n");
    printf("1 - Facil: (+ pecas, + durabilidade, - decaimento)\n");
    printf("2 - Medio: (pecas limitadas, + decaimento)\n");
    printf("3 - Dificil: (limitado de 4 a 5 pecas, - durabilidade, + decaimento)\n");
    printf("Digite a dificuldade escolhida:");
    scanf("%d", &caso); //quebra se nao for int
    printf("\n");

    switch (caso)
    {
    case 1:
        durabilidade = gerarNmrAleatorio(duraMax - 10, duraMax);
        decaimento = gerarNmrAleatorio(decaiMin, decaiMin + 2);
        regeneracao = gerarNmrAleatorio(regenMax - 2, regenMax);
        pecas = (altura + largura) / 3 + 2;
        break;
    case 2:
        durabilidade = gerarNmrAleatorio((duraMin + duraMax) / 2, duraMax - 5);
        decaimento = gerarNmrAleatorio((decaiMin + decaiMax) / 2, decaiMax);
        regeneracao = gerarNmrAleatorio(regenMin + 2, regenMax - 2);
        pecas = (altura + largura) / 4 + 1;
        break;
    case 3:
        durabilidade = gerarNmrAleatorio(duraMin, duraMin + 10);
        decaimento = gerarNmrAleatorio(decaiMax - 2, decaiMax);
        regeneracao = gerarNmrAleatorio(regenMin, regenMin + 3);
        pecas = 4;
        break;
    default:
        printf("Opcao Invalida! Dificuldade MEDIA escolhida!\n");
        durabilidade = gerarNmrAleatorio(duraMin + 5, duraMax - 5);
        decaimento = gerarNmrAleatorio(decaiMin + 1, decaiMax - 1);
        regeneracao = gerarNmrAleatorio(regenMin + 1, regenMax - 1);
        pecas = (altura + largura) / 4;
        break;
    }
    
    preencheMapa(&mapa,&pecas);
    
    fprintf(fp, "%d %d %d\n", durabilidade, decaimento, regeneracao);
    fprintf(fp, "%d %d\n", altura, largura);

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
