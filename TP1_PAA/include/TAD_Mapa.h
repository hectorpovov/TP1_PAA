#ifndef MAPA_H
#define MAPA_H

typedef struct Setor{

    char caractere;
    int visitado;

}Setor;

typedef struct Mapa{
    
    int altura;
    int largura;
    Setor * * posicoes; //matriz do mapa, cada posicao tem o caractere e o passo em que foi visitado

}Mapa;

void InicializaMapaVazio(Mapa * mapa, int altura, int largura);

void limparMapa(Mapa*mapa);

void ImprimeMapa(Mapa * mapa);


#endif