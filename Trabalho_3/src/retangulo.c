#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"


typedef struct retangulo
{
    char id[20], corP[20], corB[20];
    double x, y, w, h,energia, moeda, riqueza;

}ItemRe;

Retangulo criaRetangulo(char id[20], char corB[20], char corP[20], double largura, double altura, double x, double y)
{
    ItemRe *re;
    re = (ItemRe*) calloc(1, sizeof(ItemRe));
    strcpy(re->id, id);
    strcpy(re->corP, corP);
    strcpy(re->corB, corB);
    re->w = largura;
    re->h = altura;
    re->x = x;
    re->y = y;
    re->moeda = 0;
    re->energia = 0;
    re->riqueza = 0;

    return re;
}

double getRetanguloX(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->x;
}

double getRetanguloY(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->y;
}

double getRetanguloWidth(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->w;
}

double getRetanguloHeight(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->h;
}

char *getRetanguloID(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->id;
}

char *getRetanguloCorP(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->corP;
}

char *getRetanguloCorB(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->corB;
}


void setRetanguloX(Retangulo r, double x){
    ItemRe *re = (ItemRe*)r;
    re->x = x;
}

void setRetanguloY(Retangulo r, double y){
    ItemRe *re = (ItemRe*)r;
    re->y = y;
}

void setRetanguloWidth(Retangulo r, double w){
    ItemRe *re = (ItemRe*)r;
    re->w = w;
}

void setRetanguloHeight(Retangulo r, double h){
    ItemRe *re = (ItemRe*)r;
    re->h = h;
}


void setRetanguloID(Retangulo r, char id[]){
    ItemRe *re = (ItemRe*)r;
    strcpy(re->id,id);
}

void setRetanguloCorP(Retangulo r, char corP[]){
    ItemRe *re = (ItemRe*)r;
    strcpy(re->corP,corP);
}

void setRetanguloCorB(Retangulo r, char corB[]){
    ItemRe *re = (ItemRe*)r;
    strcpy(re->corB,corB);
}

Ponto getPontoRetangulo(Retangulo p){
    ItemRe *hi = (ItemRe*)p;
    Ponto ponto = criaPonto(hi->x, hi->y);
    return ponto;
}
double getEnergiaRetangulo(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    if(r == NULL){
        return 0;
    }
    return re->energia;
}
void setEnergiaRetangulo(Retangulo r, double energia){
    ItemRe *re = (ItemRe*)r;
    re->energia = energia;
}
double getMoedaRetangulo(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->moeda;
}
void setMoedaRetangulo(Retangulo r, double moeda){
    ItemRe *re = (ItemRe*)r;
    re->moeda = moeda;
}
double getRiquezaRetangulo(Retangulo r){
    ItemRe *re = (ItemRe*)r;
    return re->riqueza;
}
void setRiquezaRetangulo(Retangulo r, double riqueza){
    ItemRe *re = (ItemRe*)r;
    re->riqueza = riqueza;
}

void swapRetangulo(Retangulo x, Retangulo y){
    ItemRe *cv1 = (ItemRe*)x;
    ItemRe *cv2 = (ItemRe*)y;
    ItemRe temp = *cv1;
    *cv1 = *cv2;
    *cv2 = temp;
}

bool isPontoDentroRetangulo(Retangulo r, double x, double y){
    ItemRe *re = (ItemRe*)r;
    double dx = x - re->x; double dy = y - re->y;
    return dx >= 0 && dx <= re->w && dy >= 0 && dy <= re->h;
}

void desenharRetangulo(Retangulo r, double x, double y, FILE* svg){
    ItemRe *ret = (ItemRe*)r;
    x = x * 2;
    y = y * 2;
    if(ret->energia == 0){
        strcpy(ret->corB,"#484537");
    }else if(ret->energia <10){
        strcpy(ret->corB,"#FFCC00");
    }else if(ret->energia <30){
        strcpy(ret->corB,"#217821");
    }else if(ret->energia >=30){
        strcpy(ret->corB,"#800066");
    }
    fprintf(svg,"\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"2\" />\n",ret->x, ret->y, ret->w, ret->h,ret->corP,ret->corB);
}