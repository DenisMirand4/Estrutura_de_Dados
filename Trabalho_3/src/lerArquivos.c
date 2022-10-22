#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "lista.h"
#include "retangulo.h"
#include "linha.h"
#include "circulo.h"
#include "texto.h"
#include "ponto.h"
#include "fila.h"
#include "svg.h"
#include "srbTree.h"
#include "cidade.h"



void lerGEO(SRbTree arvores[4], char arqGeo[], char said[], SRbTree arvoresDot[4]){
    
    printf("ArqGeo = %s\nSaida = %s\n",arqGeo, said);    
    char corBorda[20], corPren[20];
    char id[20], tex[300], anchorPoint[5];
    char instrucao[100];
    double x, y, w, h, r;
    // puts(said);

    FILE *geo = fopen(arqGeo, "r");

    if( geo == NULL){
        printf("Erro ao abrir arquivo GEO\n");
        exit(1);
    } 
    printf("Arquvio GEO aberto\n");
  
    // Faz a leitura dos comandos 
    while (1){
        if(feof(geo)) // verifica se o arquivo chegou ao final
            break;

        fscanf(geo, "%s", instrucao);
        
       if(strcmp("c", instrucao) == 0){
            fscanf(geo, "%s %lf %lf %lf %s %s", id, &x, &y, &r, corBorda, corPren);
            insertSRb(arvores[CIRCULO], x, y, x, y, x, y, criaCirculo(id, corBorda, corPren, r, x, y));
            insertSRb(arvoresDot[CIRCULO], x, y, x, y, x, y, criaCirculo(id, corBorda, corPren, r, x, y));
        }
        else if(strcmp("r", instrucao) == 0){
            fscanf(geo, "%s %lf %lf %lf %lf %s %s", id, &x, &y, &w, &h, corBorda, corPren);
            insertSRb(arvores[RETANGULO], x, y, x, y, x, y, criaRetangulo(id, corBorda, corPren, w, h, x, y));
            insertSRb(arvoresDot[RETANGULO], x, y, x, y, x, y, criaRetangulo(id, corBorda, corPren, w, h, x, y));            
        }
        else if(strcmp("l", instrucao) == 0){
            fscanf(geo, "%s %lf %lf %lf %lf %s", id, &x, &y, &w, &r, corPren);
            insertSRb(arvores[LINHA], x, y, x, y, x, y, criaLinha(id, corPren, x, y, w, r));
            insertSRb(arvoresDot[LINHA], x, y, x, y, x, y, criaLinha(id, corPren, x, y, w, r));
        }
        else if(strcmp("t", instrucao) == 0){
            fscanf(geo, "%s %lf %lf %s %s %s", id, &x, &y, corBorda, corPren, anchorPoint);
            fgets(tex, 200, geo);
            insertSRb(arvores[TEXTO], x, y, x, y, x, y, criaTexto(id, corBorda, corPren, tex, x, y, anchorPoint[0]));
            insertSRb(arvoresDot[TEXTO], x, y, x, y, x, y, criaTexto(id, corBorda, corPren, tex, x, y, anchorPoint[0]));
        }
    }    
    FILE* svg = iniciarSvg(said);
    desenharSvg(svg, arvores);
    fecharSvg(svg);
    fclose(geo);
}


void lerQRY(SRbTree arvores[4], char *diretorio, char said[]){
    char instrucao[10];

    double x, y, h, w, d, dx, dy, energia;
    char k[20];
    char lado[20];
    char* diretorioTXT = malloc((5 + strlen(said))* sizeof(char));
    char* diretorioSVG = malloc((5 + strlen(said))* sizeof(char));
    sprintf(diretorioSVG, "%s.svg", said);
    sprintf(diretorioTXT, "%s.txt", said);
    FILE* qry   = fopen(diretorio, "r");
    FILE* saida = fopen(diretorioTXT, "w");
    FILE* svg   = iniciarSvg(diretorioSVG);
    
    if(saida == NULL || qry == NULL){
        printf("erro ao abrir arquivo qry\n");
        exit(1);
    }
    printf("QRY Iniciado\n");

    while (1){

        fscanf(qry, "%s", instrucao);

        if(feof(qry))
            break;
        else if(strcmp("e", instrucao) == 0){
            fscanf(qry, "%lf", &energia);
            energiza(arvores, saida, energia);
        }
        else if(strcmp("mv", instrucao) == 0){
            fscanf(qry, "%s %lf %lf", k, &x, &y);
            printf("mv id: %s",k);
            mv(arvores, saida, x, y, k);
        }
        else if(strcmp("lr", instrucao) == 0){
            fscanf(qry, "%s %s %lf %lf %lf", k, lado, &d, &w, &h);
            lr(arvores, saida, svg, k, lado, d, w, h);
        }
        else if(strcmp("d", instrucao) == 0){
            fscanf(qry, "%s %s %lf", k, lado, &d);
            dispara(arvores, saida, svg, k, lado, d);
        }
        else if(strcmp("mc", instrucao) == 0){
            fscanf(qry, "%lf %lf %lf %lf %lf %lf", &dx, &dy, &x, &y, &w, &h);
            mc(arvores, saida, dx, dy, x, y, w, h);
        }               
    }
    desenharSvg(svg, arvores);
    fecharSvg(svg);
    fclose(saida);
    fclose(qry);
    free(diretorioTXT);
    free(diretorioSVG);
}
