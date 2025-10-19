#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/TAD_GeradorMapa.h"

char fig[4] = {'P', '-', '|', '+'};

int gerarNmrAleatorio(int min, int max){
    return (rand() % (max - min + 1)) + min;
}

int setorValido(Mapa *mapa, int y, int x) { //modificado com - e |
    char c = mapa->posicoes[y][x].caractere;
    if (y < 0 || y >= mapa->altura || x < 0 || x >= mapa->largura)
        return 0;
    else if(c == '.' || c == '|' || c == '-'){
        return 1;
    }else{
        return 0;
    }
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
    // if(verificaColisoes(mapa,y,x,yFim,xFim) || verificaColisoes(mapa,yFim,xFim,y,x)){//mod
    //     return;
    // }
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

int verificaColisoes(Mapa *mapa, int y, int x, int yFim, int xFim) { //modificado
    int colisoes = 0;

    while (y != yFim || x != xFim) {
        if (mapa->posicoes[y][x].caractere == '-' || mapa->posicoes[y][x].caractere == '|') {
            colisoes++;
            if (colisoes > 1) {
                return 1; // caminho colide mais de 1 veze
            }
        }
        // vertical primeirp q nem fazCaminhoEntrePontos()
        if (y != yFim) {
            if (y < yFim)
                y++;
            else
                y--;
        }
        else if (x != xFim) {
            if (x < xFim)
                x++;
            else
                x--;
        }
    }
    return 0;
}

void detectaCruzamentosMapa(Mapa *mapa) {
    for (int y = 0; y < mapa->altura; y++) {
        for (int x = 0; x < mapa->largura; x++) {
            char atual = mapa->posicoes[y][x].caractere;

            if (atual == 'X' || atual == 'F' || atual == 'P')
                continue;

            if (atual != '-' && atual != '|' && atual != '+')
                continue;

            int tem_horizontal = 0;
            int tem_vertical = 0;

            if (x > 0) {
                char c = mapa->posicoes[y][x - 1].caractere;
                if (c == '-' || c == '+' || c == 'P' || c == 'F' || c == 'X')
                    tem_horizontal = 1;
            }
            if (x < mapa->largura - 1) {
                char c = mapa->posicoes[y][x + 1].caractere;
                if (c == '-' || c == '+' || c == 'P' || c == 'F' || c == 'X')
                    tem_horizontal = 1;
            }

            if (y > 0) {
                char c = mapa->posicoes[y - 1][x].caractere;
                if (c == '|' || c == '+' || c == 'P' || c == 'F' || c == 'X')
                    tem_vertical = 1;
            }
            if (y < mapa->altura - 1) {
                char c = mapa->posicoes[y + 1][x].caractere;
                if (c == '|' || c == '+' || c == 'P' || c == 'F' || c == 'X')
                    tem_vertical = 1;
            }

            if (tem_horizontal && tem_vertical)
                mapa->posicoes[y][x].caractere = '+';
        }
    }
}


void fazCaminhoEntrePontos(Mapa *mapa, int *pecas, int y, int x, int yFim, int xFim) {
    int direcao = -1;

    while (y != yFim || x != xFim) {
        if (setorValido(mapa, y, x)) {
            if(mapa->posicoes[y][x].caractere == '-' || mapa->posicoes[y][x].caractere == '|'){
                //adicionaCruzamento(mapa,y,x);
                //return;//modificado pra voltar pro antigo e so retirar o if
            }
            else if (direcao == 1)
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

void preencheMapa(Mapa *mapa, int *pecas){
    int y = gerarNmrAleatorio(0, mapa->altura - 1); 
    int x = gerarNmrAleatorio(0, mapa->largura/2);
    mapa->posicoes[y][x].caractere = 'X';

    int yFim = 0;
    int xFim = 0;
    int distancia = 0;
    do {
        yFim = gerarNmrAleatorio(0, mapa->altura - 1);
        xFim = gerarNmrAleatorio(mapa->largura/2, mapa->largura - 1);
        distancia = abs(yFim - y) + abs(xFim - x);
    } while (distancia < 2); // garantir 2 de distancia entre X e F pra n dar BO

    mapa->posicoes[yFim][xFim].caractere = 'F';
    fazCaminhoEntrePontos(mapa,pecas, y, x, yFim, xFim);
    criaNovaRota(mapa,pecas,y, x);
    criaNovaRota(mapa,pecas,yFim, xFim);
    detectaCruzamentosMapa(mapa);
}

void criaMapaAleatorio(){
    srand(time(NULL));
    
    Mapa mapa;
    int pecas = 1;
    int caso = 0;

    int largura = gerarNmrAleatorio(largMin, largMax);
    int altura = gerarNmrAleatorio(altMin, altMax);
    int durabilidade = 0;
    int decaimento = 0;
    int regeneracao = 0;
    
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
