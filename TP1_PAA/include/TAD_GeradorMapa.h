#ifndef GERADORMAPA_H
#define GERADORMAPA_H

#include "../include/TAD_Nave.h"

#define largMin 6
#define largMax 10
#define altMin 6
#define altMax 10
#define duraMin 30
#define duraMax 40
#define decaiMin 3
#define decaiMax 5
#define regenMin 5
#define regenMax 10


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

#endif
