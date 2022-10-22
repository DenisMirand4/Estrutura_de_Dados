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
#include "xyytree.h"
#include "cidade.h"



void lerGEO(XyyTree arvores[5], char arqGeo[], char said[]){
    
    printf("ArqGeo = %s\nSaida = %s\n",arqGeo, said);
    
    char corBorda[20], corPren[20];
    char id[20], tex[300], anchorPoint[5];
    char instrucao[100];
    double x, y, w, h, r;
    

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
            insertXyyT(arvores[CIRCULO], x, y, criaCirculo(id, corBorda, corPren, r, x, y));
        }
        else if(strcmp("r", instrucao) == 0){
            fscanf(geo, "%s %lf %lf %lf %lf %s %s", id, &x, &y, &w, &h, corBorda, corPren);
            insertXyyT(arvores[RETANGULO], x, y, criaRetangulo(id, corBorda, corPren, w, h, x, y));
            
        }
        else if(strcmp("l", instrucao) == 0){
            fscanf(geo, "%s %lf %lf %lf %lf %s", id, &x, &y, &w, &r, corPren);
            insertXyyT(arvores[LINHA], x, y, criaLinha(id, corPren, x, y, w, r));
        }
        else if(strcmp("t", instrucao) == 0){
            fscanf(geo, "%s %lf %lf %s %s %s", id, &x, &y, corBorda, corPren, anchorPoint);
            fgets(tex, 200, geo);
            insertXyyT(arvores[TEXTO], x, y, criaTexto(id, corBorda, corPren, tex, x, y, anchorPoint[0]));
        }
        
    }    
    
    FILE* svg = iniciarSvg(said);
    desenharSvg(svg, arvores);
    fecharSvg(svg);
    fclose(geo);

}


void lerQRY(XyyTree arvores[5], char *diretorio, char said[]){
    char instrucao[10];

    double x, y, h, w, agressividade;
    int k;
    double pontuacao = 0;
    double pontuacaoInativacao = 0;
    double pontuacaoInativacaoTotal = 0;
    
    char* diretorioTXT = malloc((5 + strlen(said))* sizeof(char));
    char* diretorioSVG = malloc((5 + strlen(said))* sizeof(char));
    sprintf(diretorioSVG, "%s.svg", said);
    sprintf(diretorioTXT, "%s.txt", said);
    
    FILE* qry   = fopen(diretorio, "r");
    FILE* saida = fopen(diretorioTXT, "w");
    FILE* svg   = iniciarSvg(diretorioSVG);


    if(saida == NULL || qry == NULL){
        printf("erro ao abrir arquivo qry");
        exit(1);
    }
    printf("QRY Iniciado\n");

    while (1){

        fscanf(qry, "%s", instrucao);
        pontuacaoInativacao = 0;
        //printf("DEBUG - instrução %s\n", instrucao);

        if(feof(qry))
            break;
        else if(strcmp("na", instrucao) == 0){
            fscanf(qry, "%lf", &agressividade);
        }
        else if(strcmp("tp", instrucao) == 0){
            fscanf(qry, "%lf %lf", &x, &y);
            tp(arvores, saida, x, y, &pontuacao);
        }
        else if(strcmp("tr", instrucao) == 0){
            fscanf(qry, "%lf %lf %lf %lf %d", &x, &y, &w, &h, &k);
            tr(arvores, saida, x, y, w, h, k);
        }
        else if(strcmp("be", instrucao) == 0){
            fscanf(qry, "%lf %lf %lf %lf", &x, &y, &w, &h);
            be(arvores, saida, x, y, w, h, &pontuacaoInativacao, agressividade);
            pontuacaoInativacaoTotal += pontuacaoInativacao;
            pontuacao += pontuacaoInativacao;
        }
                       
    }
    fprintf(saida, "Pontuacao TOTAL = %lf\n", pontuacao);
    fprintf(saida, "Pontuacao INATIVACAO = %lf\n", pontuacaoInativacaoTotal);
    desenharSvg(svg, arvores);
    fecharSvg(svg);
    fclose(saida);
    fclose(qry);
}
