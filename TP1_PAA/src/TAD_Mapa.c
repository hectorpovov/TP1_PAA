#include <stdio.h>
#include <stdlib.h>

#include "../include/TAD_Mapa.h"

void InicializaMapaVazio(Mapa * mapa, int altura, int largura){

    mapa->altura = altura;
    mapa->largura = largura;

    *mapa->posicoes = (char *)malloc(sizeof(char)*altura);

    for(int i = 0; i<altura ; i++){
        mapa->posicoes[i] = (char *)malloc(sizeof(char)*largura);
    }

}

void ImprimeMapa(Mapa * mapa){
    for(int i = 0; i< mapa->altura; i++){
        for(int j = 0; j<mapa->largura; j++){
            printf("%c", mapa->posicoes[i][j]);
        }
        printf("\n");
    }

}