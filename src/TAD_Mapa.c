#include <stdio.h>
#include <stdlib.h>

#include "../include/TAD_Mapa.h"

void InicializaMapaVazio(Mapa * mapa, int altura, int largura){
    mapa->altura = altura;
    mapa->largura = largura;
    
    //aloca dinamicamente a memoria para a matriz 
    mapa->posicoes = (Setor **)malloc(sizeof(Setor)*altura);

    for(int i = 0; i<altura ; i++){
        mapa->posicoes[i] = (Setor *)malloc(sizeof(Setor)*largura);

    }

}

void limparMapa(Mapa*mapa){//passa por todas as posicoes deixando tudo como não visitado para caso o usuário faça o percurso repetidas vezes
    for(int i = 0; i< mapa->altura; i++){
        for(int j = 0; j< mapa->largura; j++){
            mapa->posicoes[i][j].visitado = 0;
            mapa->posicoes[i][j].durabilidadeNoSetor = 0;
            mapa->posicoes[i][j].pecasRestantesNoSetor = 0;
        }
    }
}

void ImprimeMapa(Mapa * mapa){
    for(int i = 0; i< mapa->altura; i++){
        for(int j = 0; j<mapa->largura; j++){
            printf("%c", mapa->posicoes[i][j].caractere);
        }
        printf("\n");
    }

}