#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainAux.h"
#include "svg.h"
#include "leituraGEO.h"
#include "leituraQRY.h"
#include "formasGeometricas.h"

typedef struct paramEntrada{
    char *pathGeo;
    char *pathQry;
    char *nomeGEO;
    char *nomeQRY;
    char *saida;
    char *pathSaidaGeo;
    char *pathSaidaQry;
}Param;

typedef struct listas{
    Lista lista[5];
}Listas;

typedef struct  baseStr{
    Param param;
    Listas listaBase;

}BaseStr;

void iniciaListas(BaseStr *base){
    for(int i = 0; i < 5; i++)
        base->listaBase.lista[i] = CriarLista();
}

char *nomeArquivo(char path[]){
    char *aux = strrchr(path,'/');
    if(aux == NULL){
        return strtok(path,".");
    }
	return strtok(&aux[1],".");
}

void criarBase(char pathArquivo[], char pathSaida[], char pathGEO[], char pathQRY[]){
    Base c = calloc(1, sizeof(BaseStr));
    BaseStr *base = (BaseStr *)c;

    base->param.pathGeo = NULL; 
    base->param.nomeGEO    = NULL;
    base->param.pathQry = NULL; 
    base->param.nomeQRY    = NULL;
    base->param.saida      = NULL;
    base->param.pathSaidaGeo   = NULL; 
    base->param.pathSaidaQry   = NULL;
    

    if(pathArquivo != NULL){
        if(pathArquivo[strlen(pathArquivo) - 1] != '/'){
            base->param.pathGeo = (char*)malloc((strlen(pathGEO)+strlen(pathArquivo)+5)*sizeof(char));
            sprintf(base->param.pathGeo, "%s/%s", pathArquivo, pathGEO);

            if(pathQRY != NULL){
                base->param.pathQry = (char*)malloc((strlen(pathQRY)+strlen(pathArquivo)+5)*sizeof(char));
                sprintf(base->param.pathQry, "%s/%s", pathArquivo, pathQRY);
            }
        }
        else {
            base->param.pathGeo = (char *)malloc((strlen(pathGEO)+strlen(pathArquivo)+5)*sizeof(char));
            sprintf(base->param.pathGeo, "%s%s", pathArquivo, pathGEO);
            if(pathQRY != NULL){
                base->param.pathQry = (char*)malloc((strlen(pathQRY)+strlen(pathArquivo)+5)*sizeof(char));
                sprintf(base->param.pathQry, "%s%s", pathArquivo, pathQRY);
            }
        }
    }
    else {
        base->param.pathGeo = (char *)malloc((strlen(pathGEO)+5)*sizeof(char));
        strcpy(base->param.pathGeo, pathGEO);
        if(pathQRY != NULL){
            base->param.pathQry = (char*)malloc((strlen(pathQRY)+5)*sizeof(char));
            strcpy(base->param.pathQry, pathQRY);
        }
    }
    base->param.nomeGEO = nomeArquivo(pathGEO);
    if(pathSaida[strlen(pathSaida) - 1] == '/'){
        base->param.saida = (char*)malloc((strlen(base->param.nomeGEO) + strlen(pathSaida)+5) * sizeof(char));
        sprintf(base->param.saida, "%s%s", pathSaida, base->param.nomeGEO);
    }
    else{
        base->param.saida = (char*)malloc((strlen(base->param.nomeGEO) + strlen(pathSaida)+5) * sizeof(char));
        sprintf(base->param.saida, "%s/%s", pathSaida, base->param.nomeGEO);
    }
    base->param.pathSaidaGeo = (char*)malloc((strlen(base->param.saida) + 5)*sizeof(char));
    sprintf(base->param.pathSaidaGeo, "%s.svg", base->param.saida);

    iniciaListas(base);


    leituraGEO(base->listaBase.lista, base->param.pathGeo, base->param.pathSaidaGeo);


    if(pathQRY != NULL){
        base->param.nomeQRY = nomeArquivo(pathQRY);
        base->param.pathSaidaQry = (char*) malloc((strlen(base->param.nomeQRY) + strlen(base->param.saida) + 2) * sizeof(char));
        sprintf(base->param.pathSaidaQry, "%s-%s", base->param.saida, base->param.nomeQRY);

        leituraQRY(base->listaBase.lista, base->param.pathQry, base->param.pathSaidaQry);
        
        free(base->param.pathSaidaQry);
        free(base->param.pathQry);
    }

    free(base->param.pathGeo);
    free(base->param.pathSaidaGeo);
    free(base->param.saida);
    for(int i = 0; i < 4; i ++)
        DesalocarLista(base->listaBase.lista[i]);    

}