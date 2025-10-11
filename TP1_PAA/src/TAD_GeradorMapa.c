#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/TAD_Mapa.h"

#define largMin 5
#define largMax 10

#define altMin 5
#define altMax 10

#define duraMin 5
#define duraMax 10

#define decaiMin 5
#define decaiMax 10

#define regenMin 5
#define regenMax 10

int gerarNmrAleatorio(int min, int max){
    return (rand() % (max - min + 1)) + min; 
}

void criaMapaAleatorio(){

    srand(time(NULL));
    
    FILE *fp;

    char *caminho = "input/mapa1.txt";
    fp = fopen(caminho, "w");

    if(fp == NULL){
        printf("Erro ao criar arquivo\n");
        return;
    }

    int largura = gerarNmrAleatorio(largMin, largMax);
    int altura = gerarNmrAleatorio(altMin, altMax);

    int durabilidade = gerarNmrAleatorio(duraMin, duraMax);
    int decaimento = gerarNmrAleatorio(decaiMin, decaiMax);
    int regeneracao = gerarNmrAleatorio(regenMin, regenMax);

    fprintf(fp, "%d %d %d\n", durabilidade, decaimento, regeneracao);
    fprintf(fp, "%d %d\n", largura, altura);
    
    char mapaGer[largura][altura];

    for(int i = 0; i < largura; i++){
        for(int j = 0; j < altura; j++){

            mapaGer[i][j] = '.';
        }
    }

    for(int i = 0; i < largura; i++){ //teste impressão mapa
        for(int j = 0; j < altura; j++){
           printf("%c ",mapaGer[i][j]);
        }
        printf("\n");
    }

    fclose(fp);
    printf("CRIADO\n");

    return;
}