#include "stdio.h"
#include "stdlib.h"
#include "extras.h"
#include "string.h"
#include "math.h"
#include "ponto.h"
#include "lista.h"
#include "cidade.h"
#include "fila.h"
#include "linha.h"

Ponto defaultGetPonto(Ponto info){
    return info;
}

int strInList(Lista lista, char* info){
    for(No node = getFirst(lista); node != NULL; node = getNext(lista, node)){
        if(strcmp(getInfos(node), info) == 0){
            return 1;
        }
    }
    return 0;
}


double maior(double x, double y){
    if(x > y)
        return x;
    return y;
}

double menor(double x, double y){
    if(x > y)
        return y;
    return x;
}

double distancia(double x1, double y1, double x2, double y2){
    return sqrt(pow(x1 - x2,2) + pow(y1 - y2,2));
}

int pontoInternoCirculo(double x, double y, double xC, double yC, double r){
    return distancia(x, y, xC, yC) <= r;
}

int pontoInternoRetangulo(double x, double y, double xRet, double yRet, double w, double h){
    double dx = x - xRet; double dy = y - yRet;
    return dx >= 0 && dx <= w && dy >= 0 && dy <= h;
}

int retInternoCirculo(double xRet, double yRet, double w, double h, double x, double y, double r){
    if(distancia(xRet,yRet,x,y) <= r && distancia(xRet + w ,yRet + h,x,y) <= r){
        if(distancia(xRet + w, yRet,x,y) <= r && distancia(xRet, yRet + h,x,y) <= r){
            return 1;
        }
    }
    return 0;
}

int retInternoRetangulo(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2){
    return x1 >= x2 && y1 >= y2 && x1 + w1 <= x2 + w2 && y1 + h1 <= y2 + h2;
}


Info getInsideList(Lista list, char id[], int tipo){
    No node;
    Info info;
    for(node = getFirst(list); node != NULL; node = getNext(list, node)){
        info = getInfos(node);
        if(tipo == RETANGULO){
            if(strcmp(getRetanguloID(info), id) == 0)
                return node;
        }
        if(tipo == CIRCULO){
            if(strcmp(getCirculoID(info), id) == 0)
                return node;
        }
        if(tipo == TEXTO){
            if(strcmp(getTextoID(info), id) == 0)
                return node;
        }
        if(tipo == LINHA){
            if(strcmp(getLinhaID(info), id) == 0)
                return node;
        }
    }
    return NULL;
}

