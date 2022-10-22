#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainAux.h"

int main(int argc, char *argv[]){
    
    char *pathArquivo     = NULL;
    char *pathGEO        = NULL;
    char *pathQRY        = NULL; 
    char *pathSaida = NULL;    
    int i = 1;
    
    while (i < argc)
    {
        if(strcmp("-e", argv[i]) == 0){
            i++;
            if(argv[i] == NULL){
                printf("\nErro! Nada passado apos -e\n");
                exit(1);
            }
            pathArquivo = (char*) malloc((strlen(argv[i]+1))*sizeof(char));
            strcpy(pathArquivo, argv[i]);
        }        
        else if(strcmp("-f", argv[i]) == 0){
            i++;
            if (argv[i] == NULL){
                printf("\nErro! Nada passado apos -f\n");
                exit(1);
            }
            pathGEO = (char*)malloc((strlen(argv[i])+1)*sizeof(char));
            strcpy(pathGEO, argv[i]);
        }
        else if(strcmp("-q", argv[i]) == 0){
            i++;
            if(argv[i] == NULL){
                printf("\nErro! Nada passado apos -q\n");
                exit(1);
            }
            pathQRY = (char*) malloc((strlen(argv[i]+1))*sizeof(char));
            puts(argv[i]);
            strcpy(pathQRY, argv[i]);
        }
        else if(strcmp("-o", argv[i]) == 0){
            i++;
            if(argv[i] == NULL){
                printf("\nErro! Nada passado apos -o\n");
                exit(1);
            }
            pathSaida = (char*) malloc((strlen(argv[i]+1))*sizeof(char));
            strcpy(pathSaida, argv[i]);
        }
        i++;
    }
    if(pathGEO == NULL || pathSaida == NULL){
        printf("Erro! faltando parametro -f ou -o\n");
        exit(1);
    }
    criarBase(pathArquivo, pathSaida, pathGEO, pathQRY);

    free(pathQRY);
    free(pathGEO);
    free(pathArquivo);
    free(pathSaida);
    printf("Memoria desalocada\n");
    return 0;
}