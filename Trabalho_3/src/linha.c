#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linha.h"
#include <stdbool.h>

typedef struct linha
{
    char id[20], corP[20];
    double x1, y1, x2, y2;
}ItemRe;

Linha criaLinha(char id[20], char corP[20], double x1, double y1, double x2, double y2)
{
    ItemRe *re;
    re = (ItemRe*) calloc(1, sizeof(ItemRe));
    strcpy(re->id, id);
    strcpy(re->corP, corP);
    re->x1 = x1;
    re->y1 = y1;
    re->x2 = x2;
    re->y2 = y2;

    return re;
}

char *getLinhaID(Linha r){
    ItemRe *re = (ItemRe*)r;
    return re->id;
}

double getLinhaX1(Linha r){
    ItemRe *re = (ItemRe*)r;
    return re->x1;
}

double getLinhaY1(Linha r){
    ItemRe *re = (ItemRe*)r;
    return re->y1;
}

double getLinhaX2(Linha r){
    ItemRe *re = (ItemRe*)r;
    return re->x2;
}

double getLinhaY2(Linha r){
    ItemRe *re = (ItemRe*)r;
    return re->y2;
}

double getLinheMenorX(Linha r){
    ItemRe *re = (ItemRe*)r;
    if(re->x1 < re->x2)
        return re->x1;
    return re->x2;
}
double getLinheMenorY(Linha r){
    ItemRe *re = (ItemRe*)r;
    if(re->y1 < re->y2)
        return re->y1;
    return re->y2;
}

double getLinheMaiorY(Linha r){
    ItemRe *re = (ItemRe*)r;
    if(re->y1 < re->y2)
        return re->y2;
    return re->y1;
}
double getLinheMaiorX(Linha r){
    ItemRe *re = (ItemRe*)r;
    if(re->x1 < re->x2)
        return re->x2;
    return re->x1;
}

void setLinhaX1(Linha r, float valor){
    ItemRe *re = (ItemRe*)r;
    re->x1 = valor;

}
void setLinhaX2(Linha r, float valor){
    ItemRe *re = (ItemRe*)r;
    re->x2 = valor;

}
void setLinhaY1(Linha r, float valor){
    ItemRe *re = (ItemRe*)r;
    re->y1 = valor;

}
void setLinhaY2(Linha r, float valor){
    ItemRe *re = (ItemRe*)r;
    re->y2 = valor;

}


Ponto getLinhaPonto(Linha r){
    ItemRe *re = (ItemRe*)r;
    int x, y;
    if(re->x1 == re->x2){
        if(re->y1 <= re->y2){
            x = re->x1;
            y = re->y1;
        }
        else {
            x = re->x2;
            y = re->y2;
        }
    }
    else if(re->x1 < re->x2){
        x = re->x1;
        y = re->y1;
    } else {
        x = re->x2;
        y = re->y2;
    }
    return criaPonto(x, y);
}

void swapLinha(Linha x, Linha y){
    ItemRe *cv1 = (ItemRe*)x;
    ItemRe *cv2 = (ItemRe*)y;
    ItemRe temp = *cv1;
    *cv1 = *cv2;
    *cv2 = temp;
}


bool isPontoDentroLinha(Linha r, double x, double y) {
    ItemRe *re = (ItemRe*)r;
   if (re->x1 == x) return re->x2 == x;
   if (re->y1 == y) return re->y2 == y;
   return (re->x1 - x)*(re->y1 - y) == (x - re->x2)*(y - re->y2);
}

void desenharLinha(Linha r, double x, double y, FILE* svg){
    ItemRe *ret = (ItemRe*)r;
    x = x * 2;
    y = y * 2;
    fprintf(svg,"\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\"  stroke=\"%s\" style=\"stroke-width:2\" />\n",ret->x1, ret->y1, ret->x2, ret->y2,ret->corP);
}