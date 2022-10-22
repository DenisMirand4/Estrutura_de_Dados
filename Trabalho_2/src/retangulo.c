#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"


typedef struct retangulo
{
    char id[20], corP[20], corB[20];
    double x, y, w, h;
    double PROTECAO;
    double PONTOS_INATIVACAO, PONTOS_DESTRUICAO; 
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

    re->PROTECAO = 60;
    re->PONTOS_INATIVACAO = 90;
    re->PONTOS_DESTRUICAO = 90 * ((largura * altura) / 5);

    return re;
}

void setRetanguloDano(Retangulo r, double dano){
    ItemRe *te = (ItemRe*)r;
    int recebido = te->PROTECAO - dano;
    if(recebido < 0)
        te->PROTECAO = 0;
    else
        te->PROTECAO = recebido;
}

int getRetanguloVida(Retangulo r){
    ItemRe *te = (ItemRe*)r;
    return te->PROTECAO;
}
double getRetanguloPontosInativacao(Retangulo r){
    ItemRe *te = (ItemRe*)r;
    return te->PONTOS_INATIVACAO;
}
double getRetanguloPontosDestruicao(Retangulo r){
    ItemRe *te = (ItemRe*)r;
    return te->PONTOS_DESTRUICAO;
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
    fprintf(svg,"\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" />\n",ret->x, ret->y, ret->w, ret->h,ret->corP,ret->corB);
}