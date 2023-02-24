#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linha.h"
#include <stdbool.h>

typedef struct linha
{
    char id[50], corP[50], ldir[50], lesq[50], from[50], to[50];
    double x1, y1, x2, y2, cmp, vm;
    int fromNum, toNum;
}ItemRe;

Linha criaLinha(char id[50], char corP[50],char from[50], char to[50], char ldir[50],char lesq[50], double cmp, double vm, double x1, double y1, double x2, double y2, int fromNum, int toNum)
{
    ItemRe *re;
    re = (ItemRe*) calloc(1, sizeof(ItemRe));
    strcpy(re->id, id);
    strcpy(re->corP, corP);
    strcpy(re->ldir, ldir);
    strcpy(re->lesq, lesq);
    strcpy(re->from, from);
    strcpy(re->to, to);
    re->cmp = cmp;
    re->vm = vm;
    re->x1 = x1;
    re->y1 = y1;
    re->x2 = x2;
    re->y2 = y2;
    re->fromNum = fromNum;
    re->toNum = toNum;

    return re;
}
int getLinhaFromNum(Linha l)
{
    ItemRe *re = (ItemRe*)l;
    return re->fromNum;
}
int getLinhaToNum(Linha l)
{
    ItemRe *re = (ItemRe*)l;
    return re->toNum;
}

char *getLinhaFrom(Linha r){
    ItemRe *re = (ItemRe*) r;
    return re->from;
}

char *getLinhaTo(Linha r){
    ItemRe *re = (ItemRe*) r;
    return re->to;

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
double getLinhaCmp(Linha r){
    ItemRe *re = (ItemRe*)r;
    return re->cmp;
}
double getLinhaVm(Linha r){
    ItemRe *re = (ItemRe*)r;
    return re->vm;
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
void getLinhaCor(Linha r, char cor[50]){
    ItemRe *re = (ItemRe*)r;
    strcpy(cor, re->corP);
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
void setLinhaCmp(Linha r, float valor){
    ItemRe *re = (ItemRe*)r;
    re->cmp = valor;

}
void setLinhaVm(Linha r, float valor){
    ItemRe *re = (ItemRe*)r;
    re->vm = valor;
}
char *getLinhaLdir(Linha r){
    ItemRe *re = (ItemRe*)r;
    return re->ldir;
}
char *getLinhaLesq(Linha r){
    ItemRe *re = (ItemRe*)r;
    return re->lesq;
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

bool isLinhaDentroRetangulo(Linha r, double x, double y, double w, double h) {
    ItemRe *re = (ItemRe*)r;
    return re->x1 >= x && re->x1 <= x + w && re->y1 >= y && re->y1 <= y + h && re->x2 >= x && re->x2 <= x + w && re->y2 >= y && re->y2 <= y + h;
}

bool isLinhaParcialmenteDentroRetangulo(Linha r, double x, double y, double w, double h) {
    ItemRe *re = (ItemRe*)r;
    return (re->x1 >= x && re->x1 <= x + w && re->y1 >= y && re->y1 <= y + h) || (re->x2 >= x && re->x2 <= x + w && re->y2 >= y && re->y2 <= y + h);
}

void desenharLinha(Linha r, double x, double y, FILE* svg){
    ItemRe *ret = (ItemRe*)r;
    x=x;
    y=y;
    if(ret->y1 == ret->y2){
        fprintf(svg,"\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\"  stroke=\"%s\" stroke-width=\"1\" marker-end=\"url(#arrowhead)\"/>\n",ret->x1, ret->y1-7, ret->x2-27, ret->y2-7,ret->corP);

    }
    else if(ret->x1 == ret->x2){
        fprintf(svg,"\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\"  stroke=\"%s\" stroke-width=\"1\" marker-end=\"url(#arrowhead)\"/>\n",ret->x1-7, ret->y1, ret->x2-7, ret->y2-27,ret->corP);

    }
    else{
        fprintf(svg,"\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\"  stroke=\"%s\" stroke-width=\"1\" marker-end=\"url(#arrowhead)\"/>\n",ret->x1, ret->y1, ret->x2, ret->y2,ret->corP);

    }
}