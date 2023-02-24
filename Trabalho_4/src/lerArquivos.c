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
#include "digraph.h"
#include "cidade.h"
#include "extras.h"
#define limites 100000
#define BUFFER_SIZE 4096
int numeroVertices = 0;

void lerGEO(SRbTree arvore, char arqGeo[], char said[]){
    printf("ArqGeo = %s\nSaida = %s\n",arqGeo, said);    
    char corBorda[20] = "black", corPren[20] = "black";
    char id[50], px[20] = "1.0px";
    char instrucao[100];
    int tamanho = 0;
    double x, y, w, h;
    FILE *geo = fopen(arqGeo, "r");
    if( geo == NULL){
        printf("Erro ao abrir arquivo GEO\n");
        exit(1);
    } 
    printf("Arquvio GEO aberto\n");
    while (1){
        if(feof(geo)) // verifica se o arquivo chegou ao final
            break;
        fscanf(geo, "%s", instrucao);
        
       if(strcmp("nx", instrucao) == 0){
            fscanf(geo, "%d", &tamanho);
        }
        else if(strcmp("q", instrucao) == 0){
            fscanf(geo, "%s %lf %lf %lf %lf", id, &x, &y, &w, &h);
            insertSRb(arvore, x, y, x, y, x, y, criaRetangulo(id, corBorda, corPren, px, w, h, x, y));
        }
        else if(strcmp("cq", instrucao) == 0){
            fscanf(geo, "%s %s %s",px, corPren, corBorda);
        }
    }    
    fclose(geo);
}

Digraph lerVIA(char *arqVia, Digraph dg){
    printf("ArqVia = %s\n",arqVia);    
    char corPren[50] = "blue";
    char id[50];
    char instrucao[100];
    char from[50], to[50], nome[50], ldir[50], lesq[50];
    int tamanho = 0, i = 1;
    double x, y;
    double cmp,vm;
    FILE *via = fopen(arqVia, "r");
    if( via == NULL){
        printf("Erro ao abrir arquivo VIA\n");
        exit(1);
    } 
    printf("Arquvio VIA aberto\n");
    fscanf(via, "%s", instrucao);
    tamanho = stringToInt(instrucao);
    dg = createGraph(tamanho);
    numeroVertices = tamanho;
    while (1){
        if(feof(via)) // verifica se o arquivo chegou ao final
            break;
        fscanf(via, "%s", instrucao);
        if(strcmp("v", instrucao) == 0){
            fscanf(via, "%s %lf %lf", id, &x, &y);
            setNodeInfo(dg,i,criaCirculo(id, x, y,i));
            setNodeName(dg,i,id);
            i++;
            continue;
        }
        else if(strcmp("e", instrucao) == 0){
            fscanf(via, "%s %s %s %s %lf %lf %s",from,to,ldir,lesq,&cmp,&vm,nome);  
            addEdge(dg, getNode(dg,from), getNode(dg,to), criaLinha(nome,corPren,from, to, ldir, lesq, cmp, vm, getCirculoX(getNodeInfo(dg, getNode(dg,from))), getCirculoY(getNodeInfo(dg, getNode(dg,from))), getCirculoX(getNodeInfo(dg, getNode(dg,to))), getCirculoY(getNodeInfo(dg, getNode(dg,to))), getNode(dg,from), getNode(dg,to)));
        }
    }    
    fclose(via);
    return dg;
}

void lerQRY(SRbTree arvore, char *diretorio, char said[], Digraph dg){
    char instrucao[10];
    double x, y, h, w,num, fator;
    char cep[20],face[20],cfill[20],cstrk[20], newName[50];
    char sentido[10], cmc[20],cmr[20],buffer[BUFFER_SIZE];
    char* diretorioTXT = malloc((5 + strlen(said))* sizeof(char));
    char* diretorioSVG = malloc((5 + strlen(said))* sizeof(char));
    char** testeNome;
    testeNome = malloc(50 * sizeof(char*));
    int iterator = 0, buffer_length=0;
    geoPosicao posInicial, posFinal;
    sprintf(diretorioSVG, "%s.svg", said);
    sprintf(diretorioTXT, "%s.txt", said);
    puts(diretorio);
    FILE* qry   = fopen(diretorio, "r");
    FILE* saida = fopen(diretorioTXT, "w");
    FILE* svg   = iniciarSvg(diretorioSVG);
    if(saida == NULL || qry == NULL){
        printf("erro ao abrir arquivo qry\n");
        exit(1);
    }
    printf("QRY Iniciado\n");
    Lista *lista = malloc(sizeof(Lista) * 50);
    for(int i = 0; i < 50; i++){
        lista[i] = createList();
    }
    while (1){
        fscanf(qry, "%s", instrucao);
        if(feof(qry))
            break;
        else if(strcmp("@o?", instrucao) == 0){
            fscanf(qry, "%s %s %lf", cep, face, &num);
            posInicial = armazenaEndereco(arvore,svg, cep, face, num);
        }
        else if(strcmp("catac", instrucao) == 0){
            fscanf(qry, "%lf %lf %lf %lf", &x, &y, &w, &h);
            catac(arvore, dg, saida, svg, x, y, w, h);
        }
        else if(strcmp("pnt", instrucao) == 0){
            fscanf(qry, "%s %s %s", cep, cfill, cstrk);
            pnt(arvore, saida, cep, cfill, cstrk);
        }
        else if(strcmp("blq", instrucao) == 0){

            fscanf(qry, "%s %s %lf %lf %lf %lf", buffer,sentido, &x, &y, &w, &h);
            buffer_length = strlen(buffer);
            testeNome[iterator] = malloc((buffer_length + 1) * sizeof(char));
            strcpy(testeNome[iterator], buffer);
            blq(dg, saida, sentido, x, y, w, h, lista[iterator]);
            iterator++;
        }


        else if(strcmp("rbl", instrucao) == 0){
            fscanf(qry, "%s", newName);
            for(int i = 0; i < iterator; i++){
                if(strcmp(testeNome[i], newName) == 0){
                    for (Lista no = getFirst(lista[i]); no != NULL;no = getNext(lista[i],no)){
                        if(no !=NULL){
                            enableEdge(dg, getEdge(dg, getNode(dg, getLinhaFrom(getInfos(no))), getNode(dg, getLinhaTo(getInfos(no)))));
                            fprintf(saida, "rbl - nome:%s - from:%s to:%s - x1:%lf y1:%lf x2:%lf y2:%lf cmp:%lf vm:%lf\n", getLinhaID(getInfos(no)), getLinhaFrom(getInfos(no)), getLinhaTo(getInfos(no)), getLinhaX1(getInfos(no)), getLinhaY1(getInfos(no)), getLinhaX2(getInfos(no)), getLinhaY2(getInfos(no)), getLinhaCmp(getInfos(no)), getLinhaVm(getInfos(no)));
                        }
                    }       
                }
            }
        }

        else if(strcmp("rf", instrucao) == 0){
            fscanf(qry, "%s %s %lf", cep, face, &fator);
            rf(arvore, dg, saida, svg, cep, face, fator);
        }  
        else if(strcmp("b", instrucao) == 0){
            fscanf(qry, "%lf %lf %lf", &x, &y, &fator);
            b(dg, saida, svg, x, y, fator);
        }
        else if(strcmp("p?", instrucao) == 0){
            fscanf(qry, "%s %s %lf %s %s", cep, face, &num, cmc, cmr);
            posFinal = p(arvore, dg, saida, svg, cep, face, num, cmc, cmr, posInicial, numeroVertices);
        }
    }
    desenharSvg(svg, arvore, dg);
    desenharPos(svg, posInicial);
    desenharPosF(svg, posFinal);

    fecharSvg(svg);
    fclose(saida);
    fclose(qry);
    free(diretorioTXT);
    free(diretorioSVG);
}

