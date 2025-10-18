#include <stdio.h>
#include <stdlib.h>

#include "../include/TAD_Nave.h"

int v[4] = {1,-1,0,0};
int h[4] = {0,0,1,-1};

void InicializaNave(Nave * nave, int durabilidade, int fatorDecaimento, int fatorAumento, int * posicaoInicial){

    nave->pecasRestantes = 4;
    nave->durabilidade = durabilidade;
    nave->fatorAumento = fatorAumento;
    nave->fatorDecaimento = fatorDecaimento;
    nave->posicaoInicial[0] = posicaoInicial[0];
    nave->posicaoInicial[1] = posicaoInicial[1];

}

void ViagemInterestelar(Nave * nave, Mapa * mapa, short modoDeAnalise){
    limparMapa(mapa);
    int durabilidadeInicial = nave->durabilidade;

    short finalizouJornada = 0;
    int chamadas = 0;
    int nivelMaximoRecursao = 0;
    int iterador = 1;
    mapa->posicoes[nave->posicaoInicial[0]][nave->posicaoInicial[1]].visitado = iterador;

    Movimentar(nave,mapa, &finalizouJornada, nave->posicaoInicial[0], nave->posicaoInicial[1], &chamadas, iterador, &nivelMaximoRecursao);

    if(modoDeAnalise){
        printf("Foram feitas %d chamadas recursivas!\n", chamadas);
        printf("O nivel maximo de recursao foi : %d\n", nivelMaximoRecursao);
    }

    if(finalizouJornada){
        if(nave->pecasRestantes == 0){
            printf("A jornada sera finalizada sem mais desafios\n");
        }else{
            printf("A tripulacao finalizou sua jornada\n");
        }
    }else{
        printf("Apesar da bravura a tripulacao falhou em sua jornada\n");
    }


    nave->durabilidade = durabilidadeInicial;
}

void Movimentar(Nave * nave, Mapa * mapa, short * finalizouJornada, int linha, int coluna, int *chamadas, int iterador, int * nivelMaximoRecursao){

    printf("durabilidade: %d  || linha: %d  ||  coluna: %d  || caractere: %c\n", nave->durabilidade, linha, coluna, mapa->posicoes[linha][coluna].caractere); //TODO:print so pra debug, fazer o print certo depois

    *chamadas = *chamadas +1; 
    if(*nivelMaximoRecursao<iterador){
        *nivelMaximoRecursao = iterador;
    }

    nave->durabilidade -= nave->fatorDecaimento;
    if(nave->durabilidade <= 0 && mapa->posicoes[linha][coluna].caractere != 'P'){
        *finalizouJornada = 0;
        return;
    }

    //variaveis auxiliares
    int novaLinha = 0, novaColuna = 0;
    int direcao = 0;
    short tempFinalizouJornada = 0;


    /*Tratamento para cada tipo de caractere diferente.
    Feito para a nave saber para onde pode caminhar, e no caso do 
    P, fazer as devidas operacoes.
    */
    if(mapa->posicoes[linha][coluna].caractere == '-'){
        direcao = 2;
        while(!tempFinalizouJornada && direcao < 4){
            tempFinalizouJornada = 0;
            novaLinha = linha + v[direcao];
            novaColuna = coluna + h[direcao];
            
            tentaMovimentar(nave, mapa, &tempFinalizouJornada, novaLinha, novaColuna, iterador,chamadas,nivelMaximoRecursao);

            direcao++;
        }
    }else if(mapa->posicoes[linha][coluna].caractere == '|'){
        direcao = 0;
        while(!tempFinalizouJornada && direcao < 2){
            tempFinalizouJornada = 0;
            novaLinha = linha + v[direcao];
            novaColuna = coluna + h[direcao];

            tentaMovimentar(nave, mapa, &tempFinalizouJornada, novaLinha, novaColuna, iterador,chamadas,nivelMaximoRecursao);

            direcao++;
        }

    }else if(mapa->posicoes[linha][coluna].caractere == '+' || mapa->posicoes[linha][coluna].caractere == 'X'){
        direcao = 0;
        while(!tempFinalizouJornada && direcao < 4){
            tempFinalizouJornada = 0;
            novaLinha = linha + v[direcao];
            novaColuna = coluna + h[direcao];
            
            tentaMovimentar(nave, mapa, &tempFinalizouJornada, novaLinha, novaColuna, iterador,chamadas,nivelMaximoRecursao);

            direcao++;
        }
    }else if(mapa->posicoes[linha][coluna].caractere == 'P'){
        nave->pecasRestantes--;
        if(nave->pecasRestantes == 0){
            tempFinalizouJornada = 1;
        }
        nave->durabilidade += nave->fatorAumento;

        direcao = 0;
        while(!tempFinalizouJornada && direcao < 4){
            tempFinalizouJornada = 0;
            novaLinha = linha + v[direcao];
            novaColuna = coluna + h[direcao];
            
            tentaMovimentar(nave, mapa, &tempFinalizouJornada, novaLinha, novaColuna, iterador,chamadas,nivelMaximoRecursao);
            direcao++;
        }
    }else if (mapa->posicoes[linha][coluna].caractere == 'E'){
        if(nave->pecasRestantes > 2){
            printf("Voce nao tem pecas suficientes para passar pelo inimigo\n");
            return;
        }

        // Se tiver pecas suficientes, perde 3 de durabilidade e segue
        nave->durabilidade -= 3;
        printf("A nave perdeu 3 de durabilidade ao passar pelo inimigo\n");
        if(nave->durabilidade <= 0){
            printf("A nave foi destruida pelo inimigo");
            *finalizouJornada = 0;
            return;
        }

        direcao = 0;
        while(!tempFinalizouJornada && direcao < 4){
            tempFinalizouJornada = 0;
            novaLinha = linha + v[direcao];
            novaColuna = coluna + h[direcao];
            
            tentaMovimentar(nave, mapa, &tempFinalizouJornada, novaLinha, novaColuna, iterador, chamadas, nivelMaximoRecursao);
            direcao++;
        }
    }else{
        printf("ERRO: NAVE SE MOVEU PARA O LUGAR ERRADO\n");
    }
    *finalizouJornada = tempFinalizouJornada;

}

//funcao para evitar repeticao desnecessaria de codigo
void tentaMovimentar(Nave* nave, Mapa *mapa,short * tempFinalizouJornada, int novaLinha, int novaColuna, int iterador, int*chamadas, int *nivelMaximoRecursao ){
        if(setorEhValido(mapa,novaLinha,novaColuna)){
            mapa->posicoes[novaLinha][novaColuna].visitado = iterador;
            if(mapa->posicoes[novaLinha][novaColuna].caractere == 'F'){
                *tempFinalizouJornada = 1;
            }else{
                Movimentar(nave,mapa,tempFinalizouJornada,novaLinha,novaColuna,chamadas,iterador+1,nivelMaximoRecursao);
                
                if(!*tempFinalizouJornada){
                    nave->durabilidade += nave->fatorDecaimento;
                    mapa->posicoes[novaLinha][novaColuna].visitado = 0;
                    if(mapa->posicoes[novaLinha][novaColuna].caractere == 'P'){
                        nave->durabilidade -= nave->fatorAumento;
                        nave->pecasRestantes++;
                    }
                }
            }
        }
}

//funcao que verifica se da pra nave ir para esse setor
int setorEhValido(Mapa * mapa, int novaLinha, int novaColuna){
    return ( novaColuna >= 0 && novaColuna < mapa->largura)
            &&(novaLinha >= 0 && novaLinha < mapa->altura)
            &&(mapa->posicoes[novaLinha][novaColuna].visitado == 0)
            &&(mapa->posicoes[novaLinha][novaColuna].caractere != '.');
}