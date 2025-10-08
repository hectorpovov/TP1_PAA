#ifndef NAVE_H
#define NAVE_H


typedef struct Nave{

    int durabilidade;
    int fatorDecaimento;
    int fatorAumento;
    int coordenadasPosicao[2];

}Nave;

void InicializaNave(Nave * nave, int durabilidade, int fatorDecaimento, int fatorAumento, int * coordenadasPosicao);


#endif