#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidade.h"
#include "svg.h"
#include "digraph.h"
#include "lerArquivos.h"



typedef struct PARAMETROS{
    char *arquivoGeo;
    char *arquivoQry;
    char *nomeGEO;
    char *nomeQRY;
    char *saida;
    char *saidaGeo;
    char *saidaQry;
    char *arquivoVIA;
} Parametros;

// typedef struct ARVORES{
//     Lista av[5];
// }Arvores;



typedef struct  city{
    Parametros par;
    Digraph graph;
    SRbTree arvore;

} cidade;


// void iniciaArvores(cidade *city, int n){
//     for(int i = 0; i < 4; i++)
//         city->arvs.av[i] = createGraph(n);
// }

// void freeArvores(cidade *city){
//     for(int i = 0; i < 4; i++)
//         killSRb(city->arvs.av[i]);

// }

char *arqNome(char path[]){
    char *aux = strrchr(path,'/');
    if(aux == NULL){
        return strtok(path,".");
    }
	return strtok(&aux[1],".");
}


void 
criarCidade(char diretorio[], char saidDiretorio[], char parGEO[], char parQRY[], char parVIA[]){
    Cidade c = calloc(1, sizeof(cidade));
    cidade *city = (cidade *)c;
    // Cidade cDot = calloc(1, sizeof(cidade));
    // cidade *cityDot = (cidade *)cDot;

    city->par.arquivoGeo = NULL; city->par.nomeGEO    = NULL;
    city->par.arquivoQry = NULL; city->par.nomeQRY    = NULL;
    city->par.saida      = NULL; city->par.arquivoVIA = NULL;
    city->par.saidaGeo   = NULL; city->par.saidaQry   = NULL;
    printf("\nDiretorio = %s\n", diretorio);
    

    if(diretorio != NULL){
        if(diretorio[strlen(diretorio) - 1] != '/'){
            city->par.arquivoGeo = (char*)malloc((strlen(parGEO)+strlen(diretorio)+2)*sizeof(char));
            sprintf(city->par.arquivoGeo, "%s/%s", diretorio, parGEO);

            if(parQRY != NULL){
                city->par.arquivoQry = (char*)malloc((strlen(parQRY)+strlen(diretorio)+2)*sizeof(char));
                sprintf(city->par.arquivoQry, "%s/%s", diretorio, parQRY);
            }
            if(parVIA != NULL){
                city->par.arquivoVIA = (char*)malloc((strlen(parVIA)+strlen(diretorio)+2)*sizeof(char));
                sprintf(city->par.arquivoVIA, "%s/%s", diretorio, parVIA);
            }
        }
        else {
            city->par.arquivoGeo = (char *)malloc((strlen(parGEO)+strlen(diretorio)+1)*sizeof(char));
            sprintf(city->par.arquivoGeo, "%s%s", diretorio, parGEO);
            if(parQRY != NULL){
                city->par.arquivoQry = (char*)malloc((strlen(parQRY)+strlen(diretorio)+1)*sizeof(char));
                sprintf(city->par.arquivoQry, "%s%s", diretorio, parQRY);
            }
            if(parVIA != NULL){
                city->par.arquivoVIA = (char*)malloc((strlen(parVIA)+strlen(diretorio)+1)*sizeof(char));
                sprintf(city->par.arquivoVIA, "%s%s", diretorio, parVIA);
            }
        }
    }
    else {
        city->par.arquivoGeo = (char *)malloc((strlen(parGEO)+1)*sizeof(char));
        strcpy(city->par.arquivoGeo, parGEO);
        if(parQRY != NULL){
            city->par.arquivoQry = (char*)malloc((strlen(parQRY)+1)*sizeof(char));
            strcpy(city->par.arquivoQry, parQRY);
        }
        if(parVIA != NULL){
            city->par.arquivoVIA = (char*)malloc((strlen(parVIA)+1)*sizeof(char));
            strcpy(city->par.arquivoVIA, parVIA);
        }
    }
    city->par.nomeGEO = arqNome(parGEO);
    if(saidDiretorio[strlen(saidDiretorio) - 1] == '/'){
        city->par.saida = (char*)malloc((strlen(city->par.nomeGEO) + strlen(saidDiretorio)+1) * sizeof(char));
        sprintf(city->par.saida, "%s%s", saidDiretorio, city->par.nomeGEO);
    }
    else{
        city->par.saida = (char*)malloc((strlen(city->par.nomeGEO) + strlen(saidDiretorio)+2) * sizeof(char));
        sprintf(city->par.saida, "%s/%s", saidDiretorio, city->par.nomeGEO);
    }
    city->par.saidaGeo = (char*)malloc((strlen(city->par.saida) + 5)*sizeof(char));
    sprintf(city->par.saidaGeo, "%s.svg", city->par.saida);

    city->arvore = createSRb(0);
    lerGEO(city->arvore, city->par.arquivoGeo, city->par.saidaGeo); // ENTRA NO GEO
    printf("GEO Finalizado\n");
    city->graph = lerVIA(city->par.arquivoVIA, city->graph); // ENTRA NO VIA
    printf("VIA Finalizado\n");
    // printGraph(city->graph);
    FILE *svg = iniciarSvg(city->par.saidaGeo);
    desenharSvg(svg, city->arvore, city->graph);
    fecharSvg(svg);

    if(parQRY != NULL){
        city->par.nomeQRY = arqNome(parQRY);
        city->par.saidaQry = (char*) malloc((strlen(city->par.nomeQRY) + strlen(city->par.saida) + 2) * sizeof(char));
        sprintf(city->par.saidaQry, "%s-%s", city->par.saida, city->par.nomeQRY);
        lerQRY(city->arvore, city->par.arquivoQry, city->par.saidaQry, city->graph); // ENTRA NO QRY
        printf("QRY Finalizado\n");
        free(city->par.saidaQry);
        free(city->par.arquivoQry);
    }
    // desenharDot(city->par.saida, cityDot->arvs.av);
    
    // freeArvores(city);

    free(city->par.arquivoGeo);

    free(city->par.saidaGeo);
    free(city->par.saida);
    free(c);

    

}