#ifndef MAPA_H
#define MAPA_H

typedef struct Mapa{
    
    int altura;
    int largura;
    int pontoInicio[2];
    char * * posicoes;

}Mapa;

void InicializaMapaVazio(Mapa * mapa, int altura, int largura);

void ImprimeMapa(Mapa * mapa);


#endif