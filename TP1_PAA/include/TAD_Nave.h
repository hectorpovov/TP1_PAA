#ifndef NAVE_H
#define NAVE_H

#include "../include/TAD_Mapa.h"

typedef struct Nave{

    int pecasRestantes;
    int durabilidade;
    int fatorDecaimento;
    int fatorAumento;
    int posicaoInicial[2];

}Nave;

void InicializaNave(Nave * nave, int durabilidade, int fatorDecaimento, int fatorAumento, int * posicaoInicial);

void ViagemInterestelar(Nave * nave, Mapa * mapa, short modoDeAnalise);

void Movimentar(Nave * nave, Mapa * mapa, short * finalizouJornada, int linha, int coluna, int *chamadas, int iterador, int * nivelMaximoRecursao);

void tentaMovimentar(Nave* nave, Mapa *mapa,short * tempFinalizouJornada, int novaLinha, int novaColuna, int iterador, int*chamadas, int *nivelMaximoRecursao );

int setorEhValido(Mapa * mapa, int novaLinha, int novaColuna);
#endif