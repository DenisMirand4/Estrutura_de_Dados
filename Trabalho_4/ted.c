#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "digraph.h"
#include "cidade.h"

int main(int argc, char *argv[]){
    
    char *parGEO = NULL; char *diretorio     = NULL;
    char *parQRY = NULL; char *saidDiretorio = NULL;
    char *parVIA = NULL;

    
    int i =1;

    while (i < argc)
    {
        if(strcmp("-f", argv[i]) == 0){
            i++;
            if (argv[i] == NULL){
                printf("\nFALHA! NENHUM Parametro foi adicionado parametros apos o -F\n");
                exit(1);
            }
            parGEO = (char*)malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(parGEO, argv[i]);
        }
        else if(strcmp("-e", argv[i]) == 0){
            i++;
            if(argv[i] == NULL){
                printf("\nFALHA! NENHUM Parametro foi adicionado parametros apos o -e\n");
                exit(1);
            }
            diretorio = (char*) malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(diretorio, argv[i]);
        }
        else if(strcmp("-q", argv[i]) == 0){
            i++;
            if(argv[i] == NULL){
                printf("\nFALHA! NENHUM Parametro foi adicionado parametros apos o -q\n");
                exit(1);
            }
            parQRY = (char*) malloc((strlen(argv[i])+1)*sizeof(char));
            printf("Arquivo QRY: %s\n", parQRY);
            strcpy(parQRY, argv[i]);


        }
        else if(strcmp("-o", argv[i]) == 0){
            i++;
            if(argv[i] == NULL){
                printf("\nFALHA! NENHUM Parametro foi adicionado parametros apos o -o\n");
                exit(1);
            }
            saidDiretorio = (char*) malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(saidDiretorio, argv[i]);
        }
        else if(strcmp("-v", argv[i]) == 0){
            i++;
            parVIA = (char*) malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(parVIA, argv[i]);
        }
        i++;
    }
    if(parGEO == NULL || saidDiretorio == NULL){
        printf("FALHA! faltando argumento -f ou -o\n");
        exit(1);
    }
    criarCidade(diretorio, saidDiretorio, parGEO, parQRY, parVIA);

    free(parQRY);
    free(parGEO);
    free(diretorio);
    free(saidDiretorio);
    printf("Memoria desalocada\n");
    return 0;
}