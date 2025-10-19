#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/TAD_Mapa.h"
#include "../include/TAD_Nave.h"
#include "../include/TAD_GeradorMapa.h"

void menu();
void leituraDeArquivo(Mapa * mapa, Nave * nave);

int main(){
    menu();

    return 0;
}

void menu(){
    short modoDeAnalise = 0;//flag para printar ou não a analise de recursividade
    printf("Seja bem vindo ao sistema operacional do Expresso Interestelar!\n");

    Mapa mapa;
    Nave nave;

    while(1){
        int opcao;

        printf("--------------------MENU--------------------\n");
        printf("1- Ler arquivo de entrada\n");
        printf("2- Iniciar jornada\n");
        if(modoDeAnalise){
            printf("3- Desativar modo de analise\n");
        }else{
            printf("3- Ativar modo de analise\n");
        }
        printf("4 - Gerar um novo mapa\n");
        printf("0- Sair\n");

        printf("Escolha uma opcao acima:\n");
        scanf("%d", &opcao);
        switch (opcao)
        {

        case 1:
            leituraDeArquivo(&mapa, &nave);
            break;
        case 2:
            ViagemInterestelar(&nave, &mapa, modoDeAnalise);
            break;
        case 3:
            
            if(modoDeAnalise){
                printf("Desativando modo de analise!\n");
                modoDeAnalise = 0;
            }else{
                printf("Ativando modo de analise!\n");
                modoDeAnalise = 1;
            }

            break;
        
        case 4:
            criaMapaAleatorio();
            break;
        case 0:
            printf("Fechando programa...\n");
            return;
        
        default:
            printf("Opcao invalida!\n");
            break;
        }
    }
    




}

void leituraDeArquivo(Mapa * mapa, Nave * nave){

    int durabilidade;
    int fatorDecaimento;
    int fatorAumento;
    int altura;
    int largura;

    FILE * file;

    while(1){
        char nome[256];

        printf("Digite o caminho para o arquivo (0 para sair):\n");
        scanf("%s", nome);
        
        if(strcmp(nome,"0")==0){
            printf("Saindo...\n");
            return;
        }
        
        file = fopen(nome, "r");

        if(file == NULL){
            printf("Arquivo invalido, tente novamente...\n");
            continue;
        }else{
            break;
        }

    }

    fscanf(file,"%d %d %d", &durabilidade, &fatorDecaimento, &fatorAumento); fgetc(file);
    fscanf(file, "%d %d", &altura, &largura); fgetc(file);
    
    InicializaMapaVazio(mapa, altura, largura);
    
    
    for(int i = 0; i< altura; i++){
        for(int j = 0; j < largura; j++){
            fscanf(file,"%c", &mapa->posicoes[i][j].caractere);
            mapa->posicoes[i][j].visitado = 0;
            mapa->posicoes[i][j].durabilidadeNoSetor = 0;
            mapa->posicoes[i][j].pecasRestantesNoSetor = 0;
            if(mapa->posicoes[i][j].caractere == 'X'){
                int vetorPosicaoInicialDaNave[2] = {i,j}; //A partir do momento em que acha a posicao inicial da nave, inicializa ela com todas as informaçoes
                InicializaNave(nave,durabilidade,fatorDecaimento,fatorAumento,vetorPosicaoInicialDaNave);
            }
        }
        fgetc(file);
    }

    ImprimeMapa(mapa);

}
