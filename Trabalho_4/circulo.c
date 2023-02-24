#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"
#include <math.h>


typedef struct circulo {
    double r, x, y;
    int num;
    char id[50], corP[50], corB[50];
    bool visited;
    
} ItemC;

Circulo criaCirculo(char id[50], double x, double y,int num){
    ItemC *c;
    c = (ItemC *)calloc(1, sizeof(ItemC));
    strcpy(c->id, id);
    c->r = 7;
    c->visited = false;
    c->num = num;
    c->x = x;
    c->y = y;

    return c;
}
int getCirculoNum(Circulo c){
    ItemC *cir = (ItemC*)c;
    return cir->num;
}
void setCirculoNum(Circulo c, int num){
    ItemC *cir = (ItemC*)c;
    cir->num = num;
}

bool getCirculoVisited(Circulo c){
    ItemC *cir = (ItemC*)c;
    return cir->visited;
}
void setCirculoVisited(Circulo c, bool visited){
    ItemC *cir = (ItemC*)c;
    cir->visited = visited;
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
    cir->r = 8;
    fprintf(svg,"\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"red\" fill=\"blue\"/>", cir->x-cir->r, cir->y-cir->r,cir->r);
}