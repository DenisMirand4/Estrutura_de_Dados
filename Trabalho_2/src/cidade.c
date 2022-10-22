#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidade.h"
#include "svg.h"
#include "xyytree.h"
#include "lerArquivos.h"



typedef struct PARAMETROS{
    char *arquivoGeo;
    char *arquivoQry;
    char *nomeGEO;
    char *nomeQRY;
    char *saida;
    char *saidaGeo;
    char *saidaQry;
} Parametros;

typedef struct ARVORES{
    Lista av[5];
}Arvores;



typedef struct  city{
    Parametros par;
    Arvores arvs;

} cidade;


void iniciaArvores(cidade *city){
    for(int i = 0; i < 5; i++)
        city->arvs.av[i] = newXyyTree(100);
}


char *arqNome(char path[]){
    char *aux = strrchr(path,'/');
    if(aux == NULL){
        return strtok(path,".");
    }
	return strtok(&aux[1],".");
}


void criarCidade(char diretorio[], char saidDiretorio[], char parGEO[], char parQRY[]){
    Cidade c = calloc(1, sizeof(cidade));
    cidade *city = (cidade *)c;

    city->par.arquivoGeo = NULL; city->par.nomeGEO    = NULL;
    city->par.arquivoQry = NULL; city->par.nomeQRY    = NULL;
    city->par.saida      = NULL;
    city->par.saidaGeo   = NULL; city->par.saidaQry   = NULL;
    

    if(diretorio != NULL){
        if(diretorio[strlen(diretorio) - 1] != '/'){
            city->par.arquivoGeo = (char*)malloc((strlen(parGEO)+strlen(diretorio)+5)*sizeof(char));
            sprintf(city->par.arquivoGeo, "%s/%s", diretorio, parGEO);

            if(parQRY != NULL){
                city->par.arquivoQry = (char*)malloc((strlen(parQRY)+strlen(diretorio)+5)*sizeof(char));
                sprintf(city->par.arquivoQry, "%s/%s", diretorio, parQRY);
            }
        }
        else {
            city->par.arquivoGeo = (char *)malloc((strlen(parGEO)+strlen(diretorio)+5)*sizeof(char));
            sprintf(city->par.arquivoGeo, "%s%s", diretorio, parGEO);
            if(parQRY != NULL){
                city->par.arquivoQry = (char*)malloc((strlen(parQRY)+strlen(diretorio)+5)*sizeof(char));
                sprintf(city->par.arquivoQry, "%s%s", diretorio, parQRY);
            }
        }
    }
    else {
        city->par.arquivoGeo = (char *)malloc((strlen(parGEO)+5)*sizeof(char));
        strcpy(city->par.arquivoGeo, parGEO);
        if(parQRY != NULL){
            city->par.arquivoQry = (char*)malloc((strlen(parQRY)+5)*sizeof(char));
            strcpy(city->par.arquivoQry, parQRY);
        }
    }
    city->par.nomeGEO = arqNome(parGEO);
    if(saidDiretorio[strlen(saidDiretorio) - 1] == '/'){
        city->par.saida = (char*)malloc((strlen(city->par.nomeGEO) + strlen(saidDiretorio)+5) * sizeof(char));
        sprintf(city->par.saida, "%s%s", saidDiretorio, city->par.nomeGEO);
    }
    else{
        city->par.saida = (char*)malloc((strlen(city->par.nomeGEO) + strlen(saidDiretorio)+5) * sizeof(char));
        sprintf(city->par.saida, "%s/%s", saidDiretorio, city->par.nomeGEO);
    }
    city->par.saidaGeo = (char*)malloc((strlen(city->par.saida) + 5)*sizeof(char));
    sprintf(city->par.saidaGeo, "%s.svg", city->par.saida);

    iniciaArvores(city);


    lerGEO(city->arvs.av, city->par.arquivoGeo, city->par.saidaGeo); // ENTRA NO GEO

    printf("GEO Finalizado\n");

    if(parQRY != NULL){
        city->par.nomeQRY = arqNome(parQRY);
        city->par.saidaQry = (char*) malloc((strlen(city->par.nomeQRY) + strlen(city->par.saida) + 2) * sizeof(char));
        sprintf(city->par.saidaQry, "%s-%s", city->par.saida, city->par.nomeQRY);
        lerQRY(city->arvs.av, city->par.arquivoQry, city->par.saidaQry); // ENTRA NO QRY
        printf("QRY Finalizado\n");
        free(city->par.saidaQry);
        free(city->par.arquivoQry);
    }

    free(city->par.arquivoGeo);
    free(city->par.saidaGeo);
    free(city->par.saida);

    

}