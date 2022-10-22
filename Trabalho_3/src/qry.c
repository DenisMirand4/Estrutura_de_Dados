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
#include "srbTree.h"
#include "lista.h"

#define limites 100000

double* disparaRede(FILE *svg,double distancia, char* lado, double x, double y, double w, double h, double wRede, double hRede){
    double* coordenadas = (double*)malloc(2*sizeof(double));

    if(strcmp(lado, "PP")==0){
        coordenadas[0] = x;
        coordenadas[1] = y - distancia - hRede;
        fprintf(svg,"\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\"  stroke=\"%s\" style=\"stroke-width:2\" />\n",x, y, x, y - distancia - hRede,"red");
    }else if(strcmp(lado, "PR")==0){
        coordenadas[0] = x;
        coordenadas[1] = y + h + distancia;
        fprintf(svg,"\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\"  stroke=\"%s\" style=\"stroke-width:2\" />\n",x, y + h, x, y + h + distancia,"red");
    }else if(strcmp(lado, "BB")==0){
        coordenadas[0] = x + w + distancia;
        coordenadas[1] = y;
        fprintf(svg,"\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\"  stroke=\"%s\" style=\"stroke-width:2\" />\n",x + w, y, x + w + distancia, y,"red");
    }else if(strcmp(lado, "EB")==0){
        coordenadas[0] = x - distancia - wRede;
        coordenadas[1] = y;
        fprintf(svg,"\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\"  stroke=\"%s\" style=\"stroke-width:2\" />\n",x, y, x - distancia - wRede, y,"red");
    }
    return coordenadas;
}

double* disparaCanhao(double distancia, char* lado, double x, double y, double w, double h){
    double* ancorCanhao = malloc(2*sizeof(double));
    if(strcmp(lado,"PP")==0){
        ancorCanhao[0] = x + w/2;
        ancorCanhao[1] = y - distancia;
    }else if(strcmp(lado,"PR")==0){
        ancorCanhao[0] = x + w/2;
        ancorCanhao[1] = y + h - distancia;
    }else if(strcmp(lado,"BB")==0){
        ancorCanhao[0] = x + w + distancia;
        ancorCanhao[1] = y + h/2;
    }else if(strcmp(lado,"EB")==0){
        ancorCanhao[0] = x - distancia;
        ancorCanhao[1] = y + h/2;
    }
    return ancorCanhao;
}

void energiza(SRbTree arvores[4],FILE *saida, double energia){
    Lista aux = createList();
    getBbSRb(arvores[0], 0, 0, limites, limites, aux);
    for(Node no = getFirst(aux); no != NULL; no = getNext(aux, no)){
        if(getInfos(no) != NULL){
            setEnergiaRetangulo(getInfos(no),energia);
            fprintf(saida,"\t%s x:%lf y:%lf riquezas:%lf energia:%lf;\n",getRetanguloID(getInfos(no)),getRetanguloX(getInfos(no)),getRetanguloY(getInfos(no)), getRiquezaRetangulo(getInfos(no)),getEnergiaRetangulo(getInfos(no)));
        }
    }
    freeList(aux);
}

void mv(SRbTree arvores[4], FILE *saida, double x, double y, char* id){
    for(int i=0;i<4;i++){
        Lista aux = createList();
        getBbSRb(arvores[0], 0, 0, limites, limites, aux);
        for(Node no = getFirst(aux); no != NULL; no = getNext(aux, no)){
            if(getInfos(no) != NULL){
                if(strcmp(getRetanguloID(getInfos(no)),id) == 0){
                    if(getEnergiaRetangulo(getInfos(no))> sqrt(x*x+y*y)/5){
                        setEnergiaRetangulo(getInfos(no),getEnergiaRetangulo(getInfos(no)) - sqrt(x*x+y*y)/5);
                        double xInicial = getRetanguloX(getInfos(no));
                        double yInicial = getRetanguloY(getInfos(no));
                        setRetanguloX(getInfos(no),getRetanguloX(getInfos(no))+x);
                        setRetanguloY(getInfos(no),getRetanguloY(getInfos(no))+y);
                        fprintf(saida,"\t%s antes(x:%lf y:%lf) depois(x:%lf y:%lf) riqueza:%lf energia:%lf;\n",getRetanguloID(getInfos(no)), xInicial, yInicial,getRetanguloX(getInfos(no)),getRetanguloY(getInfos(no)), getRiquezaRetangulo(getInfos(no)), getEnergiaRetangulo(getInfos(no)));
                    }
                }       
            }
        }
        freeList(aux);
    }
}

void lr(SRbTree arvores[4], FILE *saida,FILE *svg, char* id, char* lado, double distancia, double w, double h){
    double area = w*h, energiaAntes;
    int moeda = 0, riqueza = 0, peixe = 0, camarao = 0 , lagosta = 0, detritos = 0;
    Lista aux = createList();
    getBbSRb(arvores[0], 0, 0, limites, limites, aux);
    Node barco;
    
    for(Node no = getFirst(aux); no != NULL; no = getNext(aux, no)){
        if(getInfos(no) != NULL){
            if(strcmp(getRetanguloID(getInfos(no)),id) == 0){
                barco = no;
            }
        }
    }
    if(getEnergiaRetangulo(getInfos(barco))>=area*distancia/125){
        energiaAntes = getEnergiaRetangulo(getInfos(barco));
        double* ancorRede = malloc(2*sizeof(double));
        ancorRede = disparaRede(svg, distancia, lado, getRetanguloX(getInfos(barco)), getRetanguloY(getInfos(barco)), getRetanguloWidth(getInfos(barco)), getRetanguloHeight(getInfos(barco)), w, h);        
        fprintf(svg,"\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"#757575\" stroke=\"#40403e\" stroke-width=\"1\"/>\n",ancorRede[0],ancorRede[1], w, h);
        for(int i=1;i<=3;i++){
            Lista aux2 = createList();
            getBbSRb(arvores[i], ancorRede[0], ancorRede[1], w, h, aux2);
            for(Node no2 = getFirst(aux2); no2 != NULL; no2 = getNext(aux2, no2)){
                if(getInfos(no2) != NULL){
                    if(i == 1){
                        riqueza += 5;
                        peixe++;
                        fprintf(saida,"\tPeixe capturado id:%s x:%lf y:%lf valor:%d;\n",getCirculoID(getInfos(no2)),getCirculoX(getInfos(no2)),getCirculoY(getInfos(no2)),5); 
                        removeSRb(arvores[i],getCirculoX(getInfos(no2)),getCirculoY(getInfos(no2)), 0, 0, 0, 0);

                    }else if(i == 2){
                        riqueza++;
                        camarao++;
                        fprintf(saida,"\tCamarao capturado id:%s x:%lf y:%lf valor:%d;\n",getLinhaID(getInfos(no2)),getLinhaX1(getInfos(no2)),getLinhaY1(getInfos(no2)),1);
                        removeSRb(arvores[i],getLinhaX1(getInfos(no2)),getLinhaY1(getInfos(no2)), 0, 0, 0, 0);

                    }else if(i == 3){
                        if(strcmp(getTextoTeX(getInfos(no2))," $\n")==0){
                            moeda++;
                            fprintf(saida,"\tMoeda capturada id:%s x:%lf y:%lf;\n",getTextoID(getInfos(no2)),getTextoX(getInfos(no2)),getTextoY(getInfos(no2)));
                        }
                        if(strcmp(getTextoTeX(getInfos(no2)),">-|-&lt;")==0){
                            riqueza +=20;
                            lagosta++;
                            fprintf(saida,"\tLagosta capturada id:%s x:%lf y:%lf valor:%d;\n",getTextoID(getInfos(no2)),getTextoX(getInfos(no2)),getTextoY(getInfos(no2)),20);
                        }
                        else{
                            detritos++;
                            fprintf(saida,"\tDetrito capturado id:%s x:%lf y:%lf valor:%d;\n",getTextoID(getInfos(no2)),getTextoX(getInfos(no2)),getTextoY(getInfos(no2)),0);
                        }
                        removeSRb(arvores[i],getTextoX(getInfos(no2)),getTextoY(getInfos(no2)), 0, 0, 0, 0);
                    }
                }
            }
            freeList(aux2);
        }
        setEnergiaRetangulo(getInfos(barco),getEnergiaRetangulo(getInfos(barco)) - (area*distancia/125) + moeda*0.5);
        setRiquezaRetangulo(getInfos(barco),getRiquezaRetangulo(getInfos(barco))+riqueza);
        fprintf(saida,"\tTotal da captura moedas:%d riqueza:%d peixes:%d camaroes:%d lagostas:%d detritos:%d energia antes:%lf energia depois:%lf;\n\n",moeda,riqueza,peixe,camarao,lagosta,detritos, energiaAntes, getEnergiaRetangulo(getInfos(barco)));
        free(ancorRede);
        freeList(aux);
        return;
    }
    freeList(aux);
    fprintf(saida,"\tNao foi possivel capturar nada;\n\n");
}

void dispara(SRbTree arvores[4], FILE *saida, FILE *svg, char* id, char* lado, double d){
    Node barco;
    Lista aux = createList();
    double* ancorCanhao = malloc(2*sizeof(double));

    getBbSRb(arvores[0], 0, 0, limites, limites, aux);
    for(Node no = getFirst(aux); no != NULL; no = getNext(aux, no)){
        if(getInfos(no) != NULL){
            if(strcmp(getRetanguloID(getInfos(no)),id) == 0){
                if(getEnergiaRetangulo(getInfos(no))>=d){
                    ancorCanhao = disparaCanhao(d, lado, getRetanguloX(getInfos(no)), getRetanguloY(getInfos(no)), getRetanguloWidth(getInfos(no)), getRetanguloHeight(getInfos(no)));
                    setEnergiaRetangulo(getInfos(no),getEnergiaRetangulo(getInfos(no))-d);
                    barco = no;
                    fprintf(svg, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"%s\" stroke=\"%s\">*</text>", ancorCanhao[0], ancorCanhao[1], "#ffffff", "#ffffff");
                }
            }
        }
    }
    getBbSRb(arvores[0], 0, 0, limites, limites, aux);
    for(Node no = getFirst(aux); no != NULL; no = getNext(aux, no)){
        if(getInfos(no) != NULL){
            if(isPontoDentroRetangulo(getInfos(no), ancorCanhao[0], ancorCanhao[1]) == 1){
                setRiquezaRetangulo(getInfos(barco), getRiquezaRetangulo(getInfos(barco))+getRiquezaRetangulo(getInfos(no)));
                fprintf(saida,"\tponto de impacto(x: %lf y:%lf) dados da nau destruida(id:%s x:%lf y:%lf riqueza:%lf);\n", ancorCanhao[0], ancorCanhao[1], getRetanguloID(getInfos(no)), getRetanguloX(getInfos(no)), getRetanguloY(getInfos(no)), getRiquezaRetangulo(getInfos(no)));
                removeSRb(arvores[0], getRetanguloX(getInfos(no)), getRetanguloY(getInfos(no)), 0, 0, 0, 0);
            }
        }
    }
    freeList(aux);
    free(ancorCanhao);
    fprintf(saida,"\tponto de impacto(x: %lf y:%lf);\n",ancorCanhao[0],ancorCanhao[1]);

}

void mc(SRbTree arvores[4], FILE *saida, double dx, double dy, double x, double y, double w, double h){
    Lista aux = createList();
    getBbSRb(arvores[1], x, y, w, h, aux);
    for(Node no = getFirst(aux); no != NULL; no = getNext(aux, no)){
        if(getInfos(no) != NULL){
            setCirculoX(getInfos(no),getCirculoX(getInfos(no))+dx);
            setCirculoY(getInfos(no),getCirculoY(getInfos(no))+dy);
            fprintf(saida,"\t%s antes x:%lf y:%lf depois x:%lf y:%lf raio:%lf ;\n",getCirculoID(getInfos(no)),getCirculoX(getInfos(no))-dx,getCirculoY(getInfos(no))-dy,getCirculoX(getInfos(no)),getCirculoY(getInfos(no)),getCirculoRaio(getInfos(no)));
        }
    }
    freeList(aux);
}
