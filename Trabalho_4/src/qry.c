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
#include "digraph.h"
#include "prio.h"

#define limites 100000
#define MAX_INT 2147483647

typedef struct geoPos{
    char cep[10], face[10];
    double num;
    Info info;
    bool visitado;
    Ponto ponto;
}geoPosStruct;

typedef struct djk{
    int max;
    int* prev;
    double* dist;
}DJK;

Node closestNode(Digraph dg,double x, double y){
    double dist = limites;
    Lista aux = createList();
    int nodeFinal;
    getEdges(dg,aux);
    for(Lista no = getFirst(aux); no != NULL; no = getNext(aux,no)){
        if(getInfos(no) != NULL){
            Edge e = getEdge(dg, getNode(dg, getLinhaFrom(getInfos(no))), getNode(dg, getLinhaTo(getInfos(no))));
            if(e == NULL)
                continue;
            int from = getFromNode(dg,e);
            int to = getToNode(dg,e);
            Ponto pontoFrom = getCirculoPonto(getNodeInfo(dg, from));
            Ponto pontoTo = getCirculoPonto(getNodeInfo(dg, to));
            if(getPontoDist(pontoFrom,x,y) < dist){
                dist = getPontoDist(pontoFrom,x,y);
                nodeFinal = from;
            }
            else if(getPontoDist(pontoTo,x,y) < dist){
                dist = getPontoDist(pontoTo,x,y);
                nodeFinal = to;
            }
        }
    }
    freeList(aux);
    return nodeFinal;
}

void desenharPos(FILE* svg, geoPosicao pos){
    geoPosStruct* p = (geoPosStruct*) pos;
    if(strcmp("S", p->face) == 0 || strcmp("N",p->face) == 0){
        fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"yellow\" stroke-width=\"1\"/>\n", pontoX(p->ponto), pontoY(p->ponto), pontoX(p->ponto), pontoY(p->ponto)+1500);
        fprintf(svg,"<text x=\"%lf\" y=\"%lf\" fill=\"yellow\">o? - %s</text>\n", pontoX(p->ponto), pontoY(p->ponto)+1500, p->cep);
    }
    else if(strcmp("L", p->face) == 0 || strcmp("O",p->face) == 0){
        fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"yellow\" stroke-width=\"1\"/>\n", pontoX(p->ponto), pontoY(p->ponto), pontoX(p->ponto)+1500, pontoY(p->ponto));
        fprintf(svg,"<text x=\"%lf\" y=\"%lf\" fill=\"yellow\">o? - %s</text>\n", pontoX(p->ponto)+1500, pontoY(p->ponto), p->cep);
    }
}

void desenharPosF(FILE* svg, geoPosicao pos){
    geoPosStruct* p = (geoPosStruct*) pos;
    if(strcmp("S", p->face) == 0 || strcmp("N",p->face) == 0){
        fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"yellow\" stroke-width=\"1\"/>\n", pontoX(p->ponto), pontoY(p->ponto), pontoX(p->ponto), pontoY(p->ponto)+1500);
        fprintf(svg,"<text x=\"%lf\" y=\"%lf\" fill=\"yellow\">p? - %s</text>\n", pontoX(p->ponto), pontoY(p->ponto)+1500, p->cep);
    }
    else if(strcmp("L", p->face) == 0 || strcmp("O",p->face) == 0){
        fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"yellow\" stroke-width=\"1\"/>\n", pontoX(p->ponto), pontoY(p->ponto), pontoX(p->ponto)+1500, pontoY(p->ponto));
        fprintf(svg,"<text x=\"%lf\" y=\"%lf\" fill=\"yellow\">p? - %s</text>\n", pontoX(p->ponto)+1500, pontoY(p->ponto), p->cep);
    }
}

geoPosicao armazenaEndereco(SRbTree arvore, FILE *svg, char* cep, char* face, double num){
    geoPosStruct* geoPos = (geoPosStruct*) malloc(sizeof(geoPosStruct));
    strcpy(geoPos->cep,cep);
    strcpy(geoPos->face,face);  
    geoPos->num = num;
    geoPos->visitado = false;
    Lista aux = createList();
    getBbSRb(arvore, 0, 0, limites, limites, aux);
    for(Lista no = getFirst(aux); no != NULL; no = getNext(aux, no)){
        if(getInfos(no) != NULL){
            if(strcmp(getRetanguloID(getInfos(no)), cep) == 0){
                geoPos->info = getInfos(no);
                if(strcmp("N",face) == 0){
                    int x = getRetanguloX(geoPos->info)+geoPos->num;
                    int y = getRetanguloY(geoPos->info)+ getRetanguloHeight(geoPos->info);
                    geoPos->ponto = criaPonto(x,y);

                }
                else if(strcmp("S", face)==0){
                    int x = getRetanguloX(geoPos->info)+geoPos->num;
                    int y = getRetanguloY(geoPos->info);
                    geoPos->ponto = criaPonto(x,y);
                }
                else if(strcmp("L", face)==0){
                    int x = getRetanguloX(geoPos->info);
                    int y = getRetanguloY(geoPos->info)+geoPos->num;
                    geoPos->ponto = criaPonto(x,y);
                }
                else if(strcmp("O", face)==0){
                    int x = getRetanguloX(geoPos->info) + getRetanguloWidth(geoPos->info);
                    int y = getRetanguloY(geoPos->info)+geoPos->num;    
                    geoPos->ponto = criaPonto(x,y);
                }
                desenharPos(svg, geoPos);
                return geoPos;
            }
        }
    }
    freeList(aux);
    return NULL;
}

void catac(SRbTree arvore, Digraph dg, FILE *saida, FILE *svg, double x, double y, double w, double h){
    NodeTree no;
    Lista edges = createList();
    Lista aux = createList();
    getBbSRb(arvore, x, y, w, h, aux);
    getEdges(dg, edges);
    for(no = getFirst(aux); no != NULL; no = getNext(aux, no)){
        if(getInfos(no) != NULL){
            removeSRb(arvore, pontoX(getInfos(no)), pontoY(getInfos(no)), 0,0,0,0);
            fprintf(saida,"Quadra removida: CEP: %s x:%lf y:%lf h:%lf w:%lf\n", getRetanguloID(getInfos(no)), getRetanguloX(getInfos(no)), getRetanguloY(getInfos(no)), getRetanguloHeight(getInfos(no)), getRetanguloWidth(getInfos(no)));	
        }
    }
    for(no = getFirst(edges); no != NULL; no = getNext(edges, no)){
        if(getInfos(no) != NULL){
            if(isLinhaParcialmenteDentroRetangulo(getInfos(no), x, y, w, h)){
                Edge ed = getEdge(dg, getNode(dg, getLinhaFrom(getInfos(no))), getNode(dg, getLinhaTo(getInfos(no))));
                removeEdge(dg, ed);
                fprintf(saida, "Aresta removida: from: %s to: %s ldir: %s lesq: %s cmp: %lf vm: %lf nome: %s\n", getLinhaFrom(getInfos(no)), getLinhaTo(getInfos(no)), getLinhaLdir(getInfos(no)), getLinhaLesq(getInfos(no)), getLinhaCmp(getInfos(no)), getLinhaVm(getInfos(no)), getLinhaID(getInfos(no)));
            }
        }
    }

    fprintf(svg,"<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"#AB37C8\" opacity=\"0.5\" stroke=\"#AA0044\" stroke-width=\"5\"/>\n", x, y, w, h);
    freeList(aux);
    freeList(edges);
}

void pnt(SRbTree arvore, FILE *saida, char *cep, char* cfill, char* cstrk){
    NodeTree no;
    Lista aux = createList();
    getBbSRb(arvore, 0, 0, limites, limites, aux);
    for(no = getFirst(aux); no != NULL; no = getNext(aux, no)){
        if(getInfos(no) != NULL){
            if(strcmp(getRetanguloID(getInfos(no)), cep) == 0){
                setRetanguloCorP(getInfos(no), cfill);
                setRetanguloCorB(getInfos(no), cstrk);
                fprintf(saida, "pnt - CEP:%s - x:%lf y:%lf w:%lf h:%lf\n",cep, getRetanguloX(getInfos(no)), getRetanguloY(getInfos(no)), getRetanguloWidth(getInfos(no)), getRetanguloHeight(getInfos(no)));
            }
        }
    }
    freeList(aux);
}

void blq(Digraph dg, FILE *saida,char* sentido, double x, double y, double w, double h, Lista result){
    Lista aux = createList();
    getEdges(dg,aux);
    for(Lista no = getFirst(aux); no != NULL; no = getNext(aux, no)){
        if(getInfos(no) != NULL){
            if(isLinhaDentroRetangulo(getInfos(no), x, y, w, h)){
                if(strcmp(sentido,"ns") == 0){
                    if(getLinhaX1(getInfos(no)) == getLinhaX2(getInfos(no)) && getLinhaY1(getInfos(no))<getLinhaY2(getInfos(no))){
                        listInsert(getInfos(no), result);
                        disableEdge(dg, getEdge(dg, getNode(dg, getLinhaFrom(getInfos(no))), getNode(dg, getLinhaTo(getInfos(no)))));
                        fprintf(saida, "blq - nome:%s - from:%s to:%s - sentido:%s - x1:%lf y1:%lf x2:%lf y2:%lf cmp:%lf vm:%lf\n", getLinhaID(getInfos(no)), getLinhaFrom(getInfos(no)), getLinhaTo(getInfos(no)), sentido, getLinhaX1(getInfos(no)), getLinhaY1(getInfos(no)), getLinhaX2(getInfos(no)), getLinhaY2(getInfos(no)), getLinhaCmp(getInfos(no)), getLinhaVm(getInfos(no)));
                    }
                }
                else if(strcmp(sentido,"sn") == 0){
                    if(getLinhaX1(getInfos(no)) == getLinhaX2(getInfos(no)) && getLinhaY1(getInfos(no))>getLinhaY2(getInfos(no))){
                        listInsert(getInfos(no), result);
                        disableEdge(dg, getEdge(dg, getNode(dg, getLinhaFrom(getInfos(no))), getNode(dg, getLinhaTo(getInfos(no)))));
                        fprintf(saida, "blq - nome:%s - from:%s to:%s - sentido:%s - x1:%lf y1:%lf x2:%lf y2:%lf cmp:%lf vm:%lf\n", getLinhaID(getInfos(no)), getLinhaFrom(getInfos(no)), getLinhaTo(getInfos(no)), sentido, getLinhaX1(getInfos(no)), getLinhaY1(getInfos(no)), getLinhaX2(getInfos(no)), getLinhaY2(getInfos(no)), getLinhaCmp(getInfos(no)), getLinhaVm(getInfos(no)));
                        
                    }
                }
                else if(strcmp(sentido,"lo") == 0){
                    if(getLinhaY1(getInfos(no)) == getLinhaY2(getInfos(no)) && getLinhaX1(getInfos(no))>getLinhaX2(getInfos(no))){
                        listInsert(getInfos(no), result);
                        disableEdge(dg, getEdge(dg, getNode(dg, getLinhaFrom(getInfos(no))), getNode(dg, getLinhaTo(getInfos(no)))));
                        fprintf(saida, "blq - nome:%s - from:%s to:%s - sentido:%s - x1:%lf y1:%lf x2:%lf y2:%lf cmp:%lf vm:%lf\n", getLinhaID(getInfos(no)), getLinhaFrom(getInfos(no)), getLinhaTo(getInfos(no)), sentido, getLinhaX1(getInfos(no)), getLinhaY1(getInfos(no)), getLinhaX2(getInfos(no)), getLinhaY2(getInfos(no)), getLinhaCmp(getInfos(no)), getLinhaVm(getInfos(no)));

                    }
                }
                else if(strcmp(sentido,"ol") == 0){
                    if(getLinhaY1(getInfos(no)) == getLinhaY2(getInfos(no)) && getLinhaX1(getInfos(no))<getLinhaX2(getInfos(no))){
                        listInsert(getInfos(no), result);
                        disableEdge(dg, getEdge(dg, getNode(dg, getLinhaFrom(getInfos(no))), getNode(dg, getLinhaTo(getInfos(no)))));
                        fprintf(saida, "blq - nome:%s - from:%s to:%s - sentido:%s - x1:%lf y1:%lf x2:%lf y2:%lf cmp:%lf vm:%lf\n", getLinhaID(getInfos(no)), getLinhaFrom(getInfos(no)), getLinhaTo(getInfos(no)), sentido, getLinhaX1(getInfos(no)), getLinhaY1(getInfos(no)), getLinhaX2(getInfos(no)), getLinhaY2(getInfos(no)), getLinhaCmp(getInfos(no)), getLinhaVm(getInfos(no)));

                    }
                }
            }
        }
    }
}

void rf(SRbTree arvore, Digraph dg, FILE *saida, FILE *svg, char* cep, char *face, double fator){
    arvore = arvore;
    dg = dg;
    saida = saida;
    svg = svg;
    cep = cep;
    face = face;
    fator = fator;
    return;
}

void b(Digraph dg, FILE *saida, FILE *svg, double x, double y, double fator){
    double dist = limites;
    Lista aux = createList();
    Lista result = createList();
    int nodeFinal;
    getEdges(dg,aux);
    for(Lista no = getFirst(aux); no != NULL; no = getNext(aux,no)){
        if(getInfos(no) != NULL){
            Edge e = getEdge(dg, getNode(dg, getLinhaFrom(getInfos(no))), getNode(dg, getLinhaTo(getInfos(no))));
            int from = getFromNode(dg,e);
            int to = getToNode(dg,e);
            Ponto pontoFrom = getCirculoPonto(getNodeInfo(dg, from));
            Ponto pontoTo = getCirculoPonto(getNodeInfo(dg, to));
            if(getPontoDist(pontoFrom,x,y) < dist){
                dist = getPontoDist(pontoFrom,x,y);
                nodeFinal = from;
            }
            else if(getPontoDist(pontoTo,x,y) < dist){
                dist = getPontoDist(pontoTo,x,y);
                nodeFinal = to;
            }
        }
    }
    bfs(dg, nodeFinal, NULL, result);
    for(Lista no = getFirst(result); no != NULL; no = getNext(result,no)){
        if(getInfos(no) != NULL){
            double vmAntiga = getLinhaVm(getInfos(no));
            setLinhaVm(getInfos(no), vmAntiga*fator);
            fprintf(saida, "b - nome:%s - from:%s to:%s - x1:%lf y1:%lf x2:%lf y2:%lf cmp:%lf vm antes:%lf vm depois:%lf \n", getLinhaID(getInfos(no)), getLinhaFrom(getInfos(no)), getLinhaTo(getInfos(no)), getLinhaX1(getInfos(no)), getLinhaY1(getInfos(no)), getLinhaX2(getInfos(no)), getLinhaY2(getInfos(no)), getLinhaCmp(getInfos(no)), vmAntiga, getLinhaVm(getInfos(no)));
            fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\"  stroke=\"#c83737\" stroke-width=\"5\"/>\n", getLinhaX1(getInfos(no)), getLinhaY1(getInfos(no)), getLinhaX2(getInfos(no)), getLinhaY2(getInfos(no)));
        }
    }
    freeList(result);
    freeList(aux);
}

geoPosicao p(SRbTree arvore,Digraph dg, FILE *saida, FILE *svg, char* cep, char *face, double num, char* cmc, char* cmr, geoPosicao info, int i){
    geoPosStruct *inicio = (geoPosStruct*) info;
    geoPosStruct *fim = (geoPosStruct*) malloc(sizeof(geoPosStruct));
    strcpy(fim->cep, cep);
    strcpy(fim->face, face);
    fim->num = num;
    fim->visitado = false;
    Lista aux = createList();
    getBbSRb(arvore, 0, 0, limites, limites, aux);
    for(Lista no = getFirst(aux); no != NULL; no = getNext(aux, no)){
        if(getInfos(no) != NULL){
            if(strcmp(getRetanguloID(getInfos(no)), cep) == 0){
                fim->info = getInfos(no);
                if(strcmp("N",face) == 0){
                    int x = getRetanguloX(fim->info)+fim->num;
                    int y = getRetanguloY(fim->info)+ getRetanguloHeight(fim->info);
                    fim->ponto = criaPonto(x,y);

                }
                else if(strcmp("S", face)==0){
                    int x = getRetanguloX(fim->info)+fim->num;
                    int y = getRetanguloY(fim->info);
                    fim->ponto = criaPonto(x,y);
                }
                else if(strcmp("L", face)==0){
                    int x = getRetanguloX(fim->info);
                    int y = getRetanguloY(fim->info)+fim->num;
                    fim->ponto = criaPonto(x,y);
                }
                else if(strcmp("O", face)==0){
                    int x = getRetanguloX(fim->info) + getRetanguloWidth(fim->info);
                    int y = getRetanguloY(fim->info)+fim->num;    
                    fim->ponto = criaPonto(x,y);
                }
            }
        }
    }
    int nodeInicio = closestNode(dg,pontoX(inicio->ponto), pontoY(inicio->ponto));
    Info nodeInicioInfo = getNodeInfo(dg, nodeInicio);
    int nodeFim = closestNode(dg,pontoX(fim->ponto), pontoY(fim->ponto));
    inicio->info = nodeInicioInfo;

    double dist[i];
    int prev[i];
    bool lido[i];
    
    Info menor;
    Lista edges = createList();
    Lista adj;
    PQueue pqueue = createPQ(i, NULL);
    //dijkstra CMP
    getEdges(dg, edges);
    for (int f1 = 0; f1 < i; f1++)
    {
        dist[f1] = MAX_INT;
        prev[f1] = -1;
        lido[f1] = false;
    }
    dist[nodeInicio] = 0;
    prev[nodeInicio] = -1;
    lido[nodeInicio] = true;
    int u = nodeInicio;
    int toU = u;
    insertPQ(pqueue, NULL, inicio->info, 0);
    while(emptyPQ(pqueue) != true){
        menor = removeMaximunPQ(pqueue);
        u = getNode(dg,getCirculoID(menor));
        lido[u] = true;

        adj = createList();
        adjacentEdges(dg, u, adj);
        for(Lista no1 = getFirst(adj); no1 != NULL; no1 = getNext(adj, no1)){
            if(getInfos(no1) != NULL){
                toU = getNode(dg, getLinhaTo(getInfos(no1)));
                 if(lido[toU] == false){
                    if(dist[getNode(dg, getLinhaTo(getInfos(no1)))] > dist[u] + getLinhaCmp(getInfos(no1))){
                        dist[getNode(dg, getLinhaTo(getInfos(no1)))] = dist[u] + getLinhaCmp(getInfos(no1));
                        prev[getNode(dg, getLinhaTo(getInfos(no1)))] = u;
                        insertPQ(pqueue, NULL, getNodeInfo(dg,getNode(dg, getLinhaTo(getInfos(no1)))), getLinhaCmp(getInfos(no1)));

                    }
                }

            }
        }
        freeList(adj);
    }
    
    int nodeAux = nodeFim;
    int nodeAux1;
    int nodeAux2[i];
    fprintf(svg, "\n<path d=\"M%lf, %lf ", getCirculoX(getNodeInfo(dg, nodeInicio)), getCirculoY(getNodeInfo(dg, nodeInicio)));
    while(prev[nodeAux] != -1){
        fprintf(svg, "L%lf %lf", getCirculoX(getNodeInfo(dg, prev[nodeAux])), getCirculoY(getNodeInfo(dg, prev[nodeAux])));
        nodeAux = prev[nodeAux];
    }
    fprintf(svg, "\" stroke=\"%s\" stroke-width=\"2\" fill=\"none\" id= \"theMotionPath2\"/>\n", cmc);
    fprintf(svg, "<circle r=\"15\" fill=\"green\" stroke=\"black\" stroke-width=\"2\"> \n\t<animateMotion dur=\"16s\" repeatCount=\"indefinite\"> \n\t\t <mpath xlink:href=\"#theMotionPath2\"/> </animateMotion> </circle>\n");
    if(nodeFim == -1){
        fprintf(saida, "\nNao ha caminho entre os vertices %d e %d", nodeInicio, nodeFim);
    }
    else{
        fprintf(saida, "\nCaminho mais curto entre os vertices %d e %d: ", nodeInicio, nodeFim);
        int aux1 = 1;
        nodeAux2[0] = nodeFim;
        nodeAux1 = nodeFim;
        while(prev[nodeAux1] != -1){
            nodeAux2[aux1] = prev[nodeAux1];
            nodeAux1 = prev[nodeAux1];
            aux1++;
        }
        while(aux1 > 0){
            fprintf(saida, "%d-> ", nodeAux2[aux1-1]);
            aux1--;
        }
        fprintf(saida, "%d", nodeFim);
    }

    //dijkstra VM
    getEdges(dg, edges);
    for (int f1 = 0; f1 < i; f1++)
    {
        dist[f1] = MAX_INT;
        prev[f1] = -1;
        lido[f1] = false;
    }
    dist[nodeInicio] = 0;
    prev[nodeInicio] = -1;
    lido[nodeInicio] = true;
     u = nodeInicio;
     toU = u;
    insertPQ(pqueue, NULL, inicio->info, 0);
    while(emptyPQ(pqueue) != true){
        menor = removeMaximunPQ(pqueue);
        u = getNode(dg,getCirculoID(menor));
        lido[u] = true;
        adj = createList();
        adjacentEdges(dg, u, adj);
        for(Lista no1 = getFirst(adj); no1 != NULL; no1 = getNext(adj, no1)){
            if(getInfos(no1) != NULL){
                toU = getNode(dg, getLinhaTo(getInfos(no1)));
                 if(lido[toU] == false){
                    if(dist[getNode(dg, getLinhaTo(getInfos(no1)))] > dist[u] + getLinhaVm(getInfos(no1))){
                        dist[getNode(dg, getLinhaTo(getInfos(no1)))] = dist[u] + getLinhaVm(getInfos(no1));
                        prev[getNode(dg, getLinhaTo(getInfos(no1)))] = u;
                        insertPQ(pqueue, NULL, getNodeInfo(dg,getNode(dg, getLinhaTo(getInfos(no1)))), getLinhaVm(getInfos(no1)));

                    }
                }

            }
        }
        freeList(adj);
    }
    nodeAux = nodeFim;
    fprintf(svg, "\n<path d=\"M%lf, %lf ", getCirculoX(getNodeInfo(dg, nodeFim))+5, getCirculoY(getNodeInfo(dg, nodeFim))+5);
    while(prev[nodeAux] != -1){
        fprintf(svg, "L%lf %lf", getCirculoX(getNodeInfo(dg, prev[nodeAux]))+5, getCirculoY(getNodeInfo(dg, prev[nodeAux]))+5);
        nodeAux = prev[nodeAux];
    }
    fprintf(svg, "\" stroke=\"%s\" stroke-width=\"2\" fill=\"none\" id= \"theMotionPath\"/>\n", cmr);
    fprintf(svg, "<circle r=\"15\" fill=\"red\" stroke=\"black\" stroke-width=\"2\"> \n\t<animateMotion dur=\"16s\" repeatCount=\"indefinite\"> \n\t\t <mpath xlink:href=\"#theMotionPath\"/> </animateMotion> </circle>\n");
    int nodeAux3[i];
    int nodeAux4 = nodeFim;
    if(nodeFim == -1){
        fprintf(saida, "\nNao ha caminho entre os vertices %d e %d", nodeInicio, nodeFim);
    }
    else{
        fprintf(saida, "\nCaminho mais rapido entre os vertices %d e %d: ", nodeInicio, nodeFim);
        int aux1 = 1;
        nodeAux3[0] = nodeFim;
        while(prev[nodeAux4] != -1){
            nodeAux3[aux1] = prev[nodeAux4];
            nodeAux4 = prev[nodeAux4];
            aux1++;
        }
        while(aux1 > 0){
            fprintf(saida, "%d-> ", nodeAux3[aux1-1]);
            aux1--;
        }
        fprintf(saida, "%d", nodeFim);
    }

    return fim;
}
