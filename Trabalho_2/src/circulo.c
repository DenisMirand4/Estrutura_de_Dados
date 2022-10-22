#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"
#include <math.h>


typedef struct circulo {
    double r, x, y;
    char id[20], corP[20], corB[20];
    double PROTECAO;
    double PONTOS_INATIVACAO, PONTOS_DESTRUICAO; 
} ItemC;

Circulo criaCirculo(char id[20], char corB[20], char corP[20], double raio, double x, double y){
    ItemC *c;
    c = (ItemC *)calloc(1, sizeof(ItemC));
    strcpy(c->id, id);
    strcpy(c->corP, corP);
    strcpy(c->corB, corB);
    c->x = x;
    c->y = y;
    c->r = raio;

    c->PROTECAO = 60;
    c->PONTOS_INATIVACAO = 30;
    c->PONTOS_DESTRUICAO = 75/(3.14 * raio * raio / 5);

    return c;
}

void setCirculoDano(Circulo c, double dano){
    ItemC *cir = (ItemC*)c;
    int recebido = cir->PROTECAO - dano;
    if(recebido < 0)
        cir->PROTECAO = 0;
    else
        cir->PROTECAO = recebido;
}

int getCirculoVida(Circulo c){
    ItemC *cir = (ItemC*)c;
    return cir->PROTECAO;
}

double getCirculoPontosInativacao(Circulo c){
    ItemC *cir = (ItemC*)c;
    return cir->PONTOS_INATIVACAO;
}
double getCirculoPontosDestruicao(Circulo c){
    ItemC *cir = (ItemC*)c;
    return cir->PONTOS_DESTRUICAO;
}

double getCirculoX(Circulo c){
    ItemC *cir = (ItemC*)c;
    return cir->x;
}

double getCirculoY(Circulo c){
    ItemC *cir = (ItemC*)c;
    return cir->y;
}

double getCirculoRaio(Circulo c){
    ItemC *cir = (ItemC*)c;
    return cir->r;
}

char *getCirculoID(Circulo c){
    ItemC *cir = (ItemC*)c;
    return cir->id;
}

char *getCirculoCorP(Circulo c){
    ItemC *cir = (ItemC*)c;
    return cir->corP;
}

char *getCirculoCorB(Circulo c){
    ItemC *cir = (ItemC*)c;
    return cir->corB;
}

void setCirculoX(Circulo c, double x){
    ItemC *cir = (ItemC*)c;
    cir->x = x;
}

void setCirculoY(Circulo c, double y){
    ItemC *cir = (ItemC*)c;
    cir->y = y;
}

void setCirculoRaio(Circulo c, double r){
    ItemC *cir = (ItemC*)c;
    cir->r = r;
}

void setCirculoID(Circulo c, char id[]){
    ItemC *cir = (ItemC*)c;
    strcpy(cir->id,id);
}

void setCirculoCorP(Circulo c, char corP[]){
    ItemC *cir = (ItemC*)c;
    strcpy(cir->corP,corP);
}

void setCirculoCorB(Circulo c, char corB[]){
    ItemC *cir = (ItemC*)c;
    strcpy(cir->corB,corB);
}


Ponto getCirculoPonto(Circulo c){
    ItemC *cir = (ItemC*)c;
    Ponto ponto = criaPonto(cir->x, cir->y);
    return ponto;
}

void swapCirculo(Circulo x, Circulo y){
    ItemC *cir1 = (ItemC*)x;
    ItemC *cir2 = (ItemC*)y;
    ItemC temp = *cir1;
    *cir1 = *cir2;
    *cir2 = temp;
}

bool isPontoDentroCirculo(Circulo c, double x, double y){
    ItemC *cir = (ItemC*)c;

    if (sqrt(pow(x - cir->x,2) + pow(y - cir->y,2)) <= cir->r)
        return true;
    return false;

}

void desenharCirculo(Circulo c, double x, double y, FILE* svg){
    ItemC *cir = (ItemC*)c;
    x = x * 2;
    y = y * 2;
    fprintf(svg,"\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\"/>", cir->x, cir->y, cir->r, cir->corB, cir->corP);
}