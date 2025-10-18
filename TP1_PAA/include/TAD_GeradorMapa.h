#ifndef GERADORMAPA_H
#define GERADORMAPA_H

#include "../include/TAD_Nave.h"

#define largMin 8
#define largMax 15
#define altMin 8
#define altMax 15
#define duraMin 25
#define duraMax 50
#define decaiMin 2
#define decaiMax 8
#define regenMin 2
#define regenMax 16


extern char fig[4];

void criaMapaAleatorio();
int gerarNmrAleatorio(int min, int max);

void preencheMapa(Mapa *mapa, int *pecas);

int setorValido(Mapa *mapa, int y, int x);
void adicionaCruzamento(Mapa *mapa, int y, int x);

void criaNovaRota(Mapa *mapa, int *pecas, int yFim, int xFim);
void adicionaPeca(Mapa *mapa, int *pecas, int y, int x, int yFim, int xFim);
void fazCaminhoEntrePontos(Mapa *mapa, int *pecas, int y, int x, int yFim, int xFim);
void criaPercursoMapa(Mapa *mapa, int *pecas, int posXIni, int posYIni, int posXfim, int posYfim);
int verificaColisoes(Mapa *mapa, int y, int x, int yFim, int xFim);

#endif
