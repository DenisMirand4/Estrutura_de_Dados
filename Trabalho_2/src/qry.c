#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "cidade.h"
#include "svg.h"
#include "qry.h"
#include "retangulo.h"
#include "linha.h"
#include "circulo.h"
#include "texto.h"
#include "extras.h"


void tp(XyyTree arvores[5], FILE *saida, double x, double y, double *pontuacao){
    Info infoAux;
    No noAuxiliar;
    Lista auxiliar;
    int acertou = 0;
    fprintf(saida, "TP:\n");
    // Retangulo
    auxiliar = getInfosAtingidoPontoXyyT(arvores[RETANGULO], x, y, isPontoDentroRetangulo);
    
    if(auxiliar != NULL){
        for(noAuxiliar = getFirst(auxiliar); noAuxiliar != NULL; noAuxiliar = getNext(auxiliar, noAuxiliar)){
            infoAux =  getInfos(noAuxiliar);
            fprintf(saida, "\tRetangulo: ID %s COR-B %s COR-P %s X %lf Y %lf HEIGHT %lf WIDTH %lf\n", 
                getRetanguloID(infoAux), getRetanguloCorB(infoAux), getRetanguloCorP(infoAux), getRetanguloX(infoAux), getRetanguloY(infoAux), getRetanguloHeight(infoAux), getRetanguloWidth(infoAux));
            fprintf(saida,"\t\tProtecao %d\n", getRetanguloVida(infoAux));
            *pontuacao += getRetanguloPontosDestruicao(infoAux);
            No remov = getNodeXyyT(arvores[RETANGULO], getRetanguloX(infoAux), getRetanguloY(infoAux), 1);
            removeNoXyyT(arvores[RETANGULO], remov);
            acertou++;
        
        }
    }

    // Circulo
    auxiliar = getInfosAtingidoPontoXyyT(arvores[CIRCULO], x, y, isPontoDentroCirculo);
    
    if(auxiliar != NULL){
        for(noAuxiliar = getFirst(auxiliar); noAuxiliar != NULL; noAuxiliar = getNext(auxiliar, noAuxiliar)){
            
            infoAux =  getInfos(noAuxiliar);
            fprintf(saida, "\tCirculo: ID %s COR-B %s COR-P %s X %lf Y %lf RAIO %lf\n", 
                getCirculoID(infoAux), getCirculoCorB(infoAux), getCirculoCorP(infoAux), getCirculoX(infoAux), getCirculoY(infoAux), getCirculoRaio(infoAux));
            fprintf(saida,"\t\tProtecao %d\n", getCirculoVida(infoAux));
            *pontuacao += getCirculoPontosDestruicao(infoAux);
            No remov = getNodeXyyT(arvores[CIRCULO], getCirculoX(infoAux), getCirculoY(infoAux), 1);
            removeNoXyyT(arvores[CIRCULO], remov);
            acertou++;
        }
    }

    // Linha
    auxiliar = getInfosAtingidoPontoXyyT(arvores[LINHA], x, y, isPontoDentroLinha);
    
    if(auxiliar != NULL){
        for(noAuxiliar = getFirst(auxiliar); noAuxiliar != NULL; noAuxiliar = getNext(auxiliar, noAuxiliar)){
            infoAux =  getInfos(noAuxiliar);
            fprintf(saida, "\tLINHA: ID %s X1 %lf Y1 %lf X2 %lf Y2 %lf\n", 
                getLinhaID(infoAux), getLinhaX1(infoAux), getLinhaY1(infoAux), getLinhaX2(infoAux), getLinhaY2(infoAux));
            fprintf(saida,"\t\tProtecao %d\n", getLinhaVida(infoAux));
            *pontuacao += getLinhaPontosDestruicao(infoAux);
            No remov = getNodeXyyT(arvores[LINHA], getLinhaX1(infoAux), getLinhaY1(infoAux), 1);
            removeNoXyyT(arvores[LINHA], remov);
            acertou++;
        }
    }

    
    // Texto
    auxiliar =NULL;
    
    if(auxiliar != NULL){
        for(noAuxiliar = getFirst(auxiliar); noAuxiliar != NULL; noAuxiliar = getNext(auxiliar, noAuxiliar)){
            infoAux =  getInfos(noAuxiliar);
            fprintf(saida, "\tTexto: ID %s X %lf Y %lf Texto %s\n", 
                getTextoID(infoAux), getTextoX(infoAux), getTextoY(infoAux), getTextoTeX(infoAux));
            fprintf(saida,"\t\tProtecao %d\n", getTextoVida(infoAux));
            *pontuacao += getTextoPontosDestruicao(infoAux);
            No remov = getNodeXyyT(arvores[TEXTO], getTextoX(infoAux), getTextoY(infoAux), 1);
            removeNoXyyT(arvores[TEXTO], remov); 
            acertou++;
        }
    }


    if(acertou == 0){
        fprintf(saida,"- AGUA\n");
        insertXyyT(arvores[TEXTO], x, y, criaTexto("-1", "GRAY", "GRAY", "*", x, y, 'm'));
        return;
    }
    fprintf(saida,"\t- Acertou %d alvos!\n", acertou);
    insertXyyT(arvores[TEXTO], x, y, criaTexto("-1", "RED", "RED", "*", x, y, 'm'));
}

void tr(XyyTree arvores[5], FILE *saida, double x, double y, double dx, double dy, int id){
    Info infoAux;
    No noAuxiliar;
    Lista auxiliar;
    int copiaId = id;
    char idAux[10];
    fprintf(saida, "TR:\n");
    // Retangulo
    auxiliar = getInfosAtingidoPontoXyyT(arvores[RETANGULO], x, y, isPontoDentroRetangulo);
    
    if(auxiliar != NULL){
        for(noAuxiliar = getFirst(auxiliar); noAuxiliar != NULL; noAuxiliar = getNext(auxiliar, noAuxiliar)){
            sprintf(idAux, "%d", id);
            infoAux =  getInfos(noAuxiliar);
            
            fprintf(saida, "\tRetangulo ORIGINAL: ID %s COR-B %s COR-P %s X %lf Y %lf HEIGHT %lf WIDTH %lf\n", 
                getRetanguloID(infoAux), getRetanguloCorB(infoAux), getRetanguloCorP(infoAux), getRetanguloX(infoAux), getRetanguloY(infoAux), getRetanguloHeight(infoAux), getRetanguloWidth(infoAux));
            fprintf(saida, "\tRetangulo CLONE: ID %s COR-B %s COR-P %s X %lf Y %lf HEIGHT %lf WIDTH %lf\n", 
                getRetanguloID(infoAux), getRetanguloCorP(infoAux), getRetanguloCorB(infoAux), getRetanguloX(infoAux) + dx, getRetanguloY(infoAux) + dy, getRetanguloHeight(infoAux), getRetanguloWidth(infoAux));
            
            insertXyyT(arvores[RETANGULO], getRetanguloX(infoAux) + dx, getRetanguloY(infoAux) + dy, criaRetangulo(idAux, getRetanguloCorP(infoAux), getRetanguloCorB(infoAux), getRetanguloWidth(infoAux), getRetanguloHeight(infoAux), getRetanguloX(infoAux), getRetanguloY(infoAux)));
            id++;
        }
    }

    // Circulo
    auxiliar = getInfosAtingidoPontoXyyT(arvores[CIRCULO], x, y, isPontoDentroCirculo);
    
    if(auxiliar != NULL){
        for(noAuxiliar = getFirst(auxiliar); noAuxiliar != NULL; noAuxiliar = getNext(auxiliar, noAuxiliar)){
            sprintf(idAux, "%d", id);
            
            infoAux =  getInfos(noAuxiliar);
            fprintf(saida, "\tCirculo ORIGINAL: ID %s COR-B %s COR-P %s X %lf Y %lf RAIO %lf\n", 
                getCirculoID(infoAux), getCirculoCorB(infoAux), getCirculoCorP(infoAux), getCirculoX(infoAux), getCirculoY(infoAux), getCirculoRaio(infoAux));
            fprintf(saida, "\tCirculo CLONE: ID %s COR-B %s COR-P %s X %lf Y %lf RAIO %lf\n", 
                getCirculoID(infoAux), getCirculoCorP(infoAux), getCirculoCorB(infoAux), getCirculoX(infoAux) + dx, getCirculoY(infoAux) + dy, getCirculoRaio(infoAux));
            
            insertXyyT(arvores[CIRCULO], getCirculoX(infoAux) + dx, getCirculoY(infoAux) + dy, criaCirculo(idAux, getCirculoCorP(infoAux), getCirculoCorB(infoAux), getCirculoRaio(infoAux), getCirculoX(infoAux), getCirculoY(infoAux)));

            id++;

        }
    }

    // Linha
    auxiliar = getInfosAtingidoPontoXyyT(arvores[LINHA], x, y, isPontoDentroLinha);
    
    if(auxiliar != NULL){
        for(noAuxiliar = getFirst(auxiliar); noAuxiliar != NULL; noAuxiliar = getNext(auxiliar, noAuxiliar)){
            sprintf(idAux, "%d", id);
            infoAux =  getInfos(noAuxiliar);

            fprintf(saida, "\tLINHA ORIGINAL: ID %s X1 %lf Y1 %lf X2 %lf Y2 %lf\n", 
                getLinhaID(infoAux), getLinhaX1(infoAux), getLinhaY1(infoAux), getLinhaX2(infoAux),getLinhaY2(infoAux));
            fprintf(saida, "\tLINHA CLONE: ID %s X1 %lf Y1 %lf X2 %lf Y2 %lf\n", 
                getLinhaID(infoAux), getLinhaX1(infoAux) + dx, getLinhaY1(infoAux) + dy, getLinhaX2(infoAux) +dx, getLinhaY2(infoAux));

            insertXyyT(arvores[LINHA], getLinhaX1(infoAux) + dx, getLinhaY2(infoAux)+ dy, criaLinha(idAux, "red", getLinhaX1(infoAux) + dx, getLinhaY1(infoAux) + dy,  getLinhaX2(infoAux) +dx, getLinhaY2(infoAux) +dy));
            id++;
        }
    }

    
    // Texto
    auxiliar = NULL;
    
    if(auxiliar != NULL){
        for(noAuxiliar = getFirst(auxiliar); noAuxiliar != NULL; noAuxiliar = getNext(auxiliar, noAuxiliar)){
            sprintf(idAux, "%d", id);
            infoAux =  getInfos(noAuxiliar);

            fprintf(saida, "\tTexto ORIGINAL: ID %s X %lf Y %lf Texto %s\n", 
                getTextoID(infoAux), getTextoX(infoAux), getTextoY(infoAux), getTextoTeX(infoAux));
            fprintf(saida, "\tTexto CLONE: ID %s X %lf Y %lf Texto %s\n", 
                getTextoID(infoAux), getTextoX(infoAux) + dx, getTextoY(infoAux) + dy, getTextoTeX(infoAux));

            id++;
        }
    }
    if(copiaId == id)
        fprintf(saida, "- Nao acertou nenhuma forma\n");
    insertXyyT(arvores[TEXTO], x, y, criaTexto("-1", "RED", "RED", "@", x, y, 'm'));
}


void be(XyyTree arvores[5], FILE *saida, double x, double y, double w, double h, double *pontuacao, double agressividade){
    Info infoAux;
    No noAuxiliar;
    Lista auxiliar;
    fprintf(saida, "BE:\n");
    double areaRegiao = w * h;
    double danoLevado;
    // Retangulo
    auxiliar = getNodesDentroRegiaoXyyT(arvores[RETANGULO], x, y, w, h);
    
    if(auxiliar != NULL){
        for(noAuxiliar = getFirst(auxiliar); noAuxiliar != NULL; noAuxiliar = getNext(auxiliar, noAuxiliar)){
            infoAux = getInfoXyyT(arvores[RETANGULO], getInfos(noAuxiliar));
            if(strcmp(getRetanguloID(infoAux), "-1") != 0 && x < getRetanguloX(infoAux) && (x + w) > (getRetanguloX(infoAux) + getRetanguloWidth(infoAux))  && y < getRetanguloY(infoAux) && (y+h) > (getRetanguloY(infoAux) + getRetanguloHeight(infoAux))){
                danoLevado = getRetanguloWidth(infoAux) * getRetanguloHeight(infoAux) * agressividade / areaRegiao;
                setRetanguloDano(infoAux, danoLevado);
                if(getRetanguloVida(infoAux) == 0){
                    fprintf(saida, "REMOVIDO:\n");
                    *pontuacao += getRetanguloPontosDestruicao(infoAux);
                } else{
                    *pontuacao += getRetanguloPontosInativacao(infoAux);
                }
                fprintf(saida, "\tAtingido Retangulo: ID %s COR-B %s COR-P %s X %lf Y %lf HEIGHT %lf WIDTH %lf Vida_Restante %d\n", getRetanguloID(infoAux), getRetanguloCorB(infoAux), getRetanguloCorP(infoAux), getRetanguloX(infoAux), getRetanguloY(infoAux), getRetanguloHeight(infoAux), getRetanguloWidth(infoAux), getRetanguloVida(infoAux));
            }
        }
    }
    // Circulo
    auxiliar = getNodesDentroRegiaoXyyT(arvores[CIRCULO], x, y, w, h);
    
    if(auxiliar != NULL){
        for(noAuxiliar = getFirst(auxiliar); noAuxiliar != NULL; noAuxiliar = getNext(auxiliar, noAuxiliar)){
            infoAux = getInfoXyyT(arvores[CIRCULO], getInfos(noAuxiliar));
            if(strcmp(getCirculoID(infoAux), "-1") != 0 && x < (getCirculoX(infoAux) - getCirculoRaio(infoAux)) && (x+w) > getCirculoX(infoAux) + getCirculoRaio(infoAux) && y < getCirculoY(infoAux) - getCirculoRaio(infoAux) && (y+h) > getCirculoY(infoAux) + getCirculoRaio(infoAux)){
                danoLevado = 3.14 * getCirculoRaio(infoAux) * getCirculoRaio(infoAux) * agressividade / areaRegiao;
                setCirculoDano(infoAux, danoLevado);
                if(getCirculoVida(infoAux) == 0){
                    fprintf(saida, "REMOVIDO:\n");
                    *pontuacao += getCirculoPontosDestruicao(infoAux);
                } else{
                    *pontuacao += getCirculoPontosInativacao(infoAux);
                }
                fprintf(saida, "\tAtingido Circulo: ID %s COR-B %s COR-P %s X %lf Y %lf RAIO %lf Vida_Restante %d\n", getCirculoID(infoAux), getCirculoCorB(infoAux), getCirculoCorP(infoAux), getCirculoX(infoAux), getCirculoY(infoAux), getCirculoRaio(infoAux), getCirculoVida(infoAux));
            }
        }
    }
    // Linha
    auxiliar = getNodesDentroRegiaoXyyT(arvores[LINHA], x, y, w, h);
    
    if(auxiliar != NULL){
        for(noAuxiliar = getFirst(auxiliar); noAuxiliar != NULL; noAuxiliar = getNext(auxiliar, noAuxiliar)){
            infoAux = getInfoXyyT(arvores[LINHA], getInfos(noAuxiliar));
            if(x < getLinheMenorX(infoAux) && x+w > getLinheMaiorX(infoAux) && y < getLinheMenorY(infoAux) && y+h > getLinheMaiorY(infoAux)){
                danoLevado = 0.1 * (getLinheMaiorX(infoAux) - 30) * agressividade / areaRegiao;
                setLinhaDano(infoAux, danoLevado);
                if(getLinhaVida(infoAux) == 0){
                    fprintf(saida, "REMOVIDO:\n");
                    *pontuacao += getLinhaPontosDestruicao(infoAux);
                }else{
                    *pontuacao += getLinhaPontosInativacao(infoAux);
                }
                fprintf(saida, "\tAtingido LINHA: ID %s X1 %lf Y1 %lf X2 %lf Y2 %lf Vida_Restante %d\n", getLinhaID(infoAux), getLinhaX1(infoAux), getLinhaY1(infoAux), getLinhaX2(infoAux),getLinhaY2(infoAux), getLinhaVida(infoAux));
            }
        }
    }

    
    // Texto
    auxiliar = NULL;//getNodesDentroRegiaoXyyT(arvores[TEXTO], x, y, w, h);
    
    if(auxiliar != NULL){
        for(noAuxiliar = getFirst(auxiliar); noAuxiliar != NULL; noAuxiliar = getNext(auxiliar, noAuxiliar)){
            infoAux = getInfoXyyT(arvores[LINHA], getInfos(noAuxiliar));
            float xAux, yAux;
            int tamaho = strlen(getTextoTeX(infoAux));
            if(getTextoAP(infoAux) == 'i'){
                xAux = getTextoX(infoAux);
                yAux = getTextoY(infoAux);
            } else if(getTextoAP(infoAux) == 'm'){
                xAux =  getTextoX(infoAux) - (tamaho/2);  
                yAux =  getTextoY(infoAux) - (tamaho/2);  
            } else {
                xAux =  getTextoX(infoAux) - (tamaho) * 2;  
                yAux =  getTextoY(infoAux) - (tamaho) * 2 ;  
            }
            if( x < xAux && x+w > xAux + tamaho && y < yAux && y+h > (yAux + tamaho) ){
                danoLevado = 0.1;
                setTextoDano(infoAux, danoLevado);
                if(getTextoVida(infoAux) == 0){
                    fprintf(saida, "REMOVIDO:\n");
                    *pontuacao += getTextoPontosDestruicao(infoAux);
                } else{
                    *pontuacao += getTextoPontosInativacao(infoAux);
                }
                fprintf(saida, "\tAtingido Texto: ID %s X %lf Y %lf Texto %s Vida_Restante %d\n", getTextoID(infoAux), getTextoX(infoAux), getTextoY(infoAux), getTextoTeX(infoAux), getTextoVida(infoAux));
            }       
        }
    }

    insertXyyT(arvores[RETANGULO], x, y, criaRetangulo("-1", "RED", "none", w, h ,x, y));
}