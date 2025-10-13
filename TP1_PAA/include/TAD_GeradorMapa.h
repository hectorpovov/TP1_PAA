#ifndef GERADORMAPA_H
#define GERADORMAPA_H

#include "../include/TAD_Nave.h"

// Constantes para geração aleatória
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

// Array de caracteres para elementos do mapa
extern char fig[4];

void criaMapaAleatorio();
int gerarNmrAleatorio(int min, int max);
void adicionaElementosMapa(Mapa *mapa);

int setorValido(Mapa *mapa, int y, int x);
void adicionaCruzamento(Mapa *mapa, int y, int x);
void criaNovaRota(Mapa *mapa,int yFim, int xFim);
void adicionaPeca(Mapa *mapa, int *pecas, int y, int x, int yFim, int xFim);
void adicionaElementos(Mapa *mapa, int y, int x, int yFim, int xFim);
void criaPercursoMapa(Mapa *mapa, int posXIni, int posYIni, int posXfim, int posYfim);

#endif