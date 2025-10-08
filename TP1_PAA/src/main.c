#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/TAD_Mapa.h"
#include "../include/TAD_Nave.h"


void menu();
void leituraDeArquivo(Mapa * mapa, Nave * nave);

int main(){
    
    menu();

    return 0;
}

void menu(){
    int modoDeAnalise = 0;
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
        printf("0- Sair\n");

        printf("Escolha uma opcao acima:\n");
        scanf("%d", &opcao);
        switch (opcao)
        {

        case 1:
            leituraDeArquivo(&mapa, &nave);
            break;
        case 2:
            //Iniciar jornada
            
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
            fscanf(file,"%c", &mapa->posicoes[i][j]);
            if(mapa->posicoes[i][j] == 'X'){
                nave->coordenadasPosicao[0] = j;
                nave->coordenadasPosicao[1] = i;
            }
        }
        fgetc(file);
    }

    ImprimeMapa(mapa);

}
