#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "lista.h"
#include "fila.h"
#include "svg.h"
#include "mainAux.h"
#include "formasGeometricas.h"

void leituraGEO(Lista listas[5], char pathGEO[], char pathSaida[]){
    
    printf("ArqGeo = %s\nSaida = %s\n",pathGEO, pathSaida);
    
    char corb[20], corp[20];
    char id[20], txto[300], ancora[5];
    char comando[100];
    double x, y, w, h, r;
    

    FILE *geo = fopen(pathGEO, "r");//abre o arquivo

    if( geo == NULL){
        printf("Erro ao abrir arquivo GEO\n");
        exit(1);
    }else(printf("Arquvio GEO aberto\n"));
    
  
    while (1){//le o arquivo
        if(feof(geo))//fim do arquivo
            break;

        fscanf(geo, "%s", comando);
        
       if(strcmp("c", comando) == 0){
            fscanf(geo, "%s %lf %lf %lf %s %s", id, &x, &y, &r, corb, corp); 
            InserirFinalLista(listas[CIRCULO], criar_circulo(id, corb, corp, r, x, y));
        }
        else if(strcmp("r", comando) == 0){
            fscanf(geo, "%s %lf %lf %lf %lf %s %s", id, &x, &y, &w, &h, corb, corp);
            InserirFinalLista(listas[RETANGULO], cria_retangulo(id, corb, corp, w, h, x, y));
            
        }
        else if(strcmp("l", comando) == 0){
            fscanf(geo, "%s %lf %lf %lf %lf %s", id, &x, &y, &w, &r, corp);
            InserirFinalLista(listas[LINHA], cria_linha(id, corp, x, y, w, r));
        }
        else if(strcmp("t", comando) == 0){
            fscanf(geo, "%s %lf %lf %s %s %s", id, &x, &y, corb, corp, ancora);
            fgets(txto, 200, geo);
            InserirFinalLista(listas[TEXTO], cria_texto(id, corb, corp, txto, x, y, ancora[0]));
        }
        
    }    
    
    FILE* svg = iniciarSvg(pathSaida);
    desenharSvg(svg, listas);
    fecharSvg(svg);
    fclose(geo);

}
