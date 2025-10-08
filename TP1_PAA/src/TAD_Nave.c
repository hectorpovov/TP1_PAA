#include <stdio.h>
#include <stdlib.h>

#include "../include/TAD_Nave.h"

void InicializaNave(Nave * nave, int durabilidade, int fatorDecaimento, int fatorAumento, int * coordenadasPosicao){

    nave->durabilidade = durabilidade;
    nave->fatorAumento = fatorAumento;
    nave->fatorDecaimento = fatorDecaimento;
    nave->coordenadasPosicao[0] = coordenadasPosicao[0];
    nave->coordenadasPosicao[1] = coordenadasPosicao[1];

}