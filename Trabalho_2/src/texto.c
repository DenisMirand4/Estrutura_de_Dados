#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"
#include <stdbool.h>

#define TEXT_MAX 1000

typedef struct texto {
    double x, y;
    char id[20], corP[20], corB[20], tex[TEXT_MAX], anchorPoint;
    double PROTECAO;
    double PONTOS_INATIVACAO, PONTOS_DESTRUICAO; 
} ItemT;

Texto criaTexto(char id[20], char corB[20], char corP[20], char tex[], double x, double y, char anchorPoint){
    ItemT *t;
    t = (ItemT *)calloc(1, sizeof(ItemT));
    strcpy(t->id,id);
    strcpy(t->tex,tex);
    strcpy(t->corB,corB);
    strcpy(t->corP,corP);
    t->x = x;
    t->y = y;
    t->anchorPoint = anchorPoint;    

    t->PROTECAO = 5;
    t->PONTOS_INATIVACAO = 30;
    t->PONTOS_DESTRUICAO = 500;

    return t;
}

void setTextoDano(Texto c, double dano){
    ItemT *te = (ItemT*)c;
    int recebido = te->PROTECAO - dano;
    if(recebido < 0)
        te->PROTECAO = 0;
    else
        te->PROTECAO = recebido;
}

int getTextoVida(Texto c){
    ItemT *te = (ItemT*)c;
    return te->PROTECAO;
}

double getTextoPontosInativacao(Texto c){
    ItemT *te = (ItemT*)c;
    return te->PONTOS_INATIVACAO;
}
double getTextoPontosDestruicao(Texto c){
    ItemT *te = (ItemT*)c;
    return te->PONTOS_DESTRUICAO;
}

double getTextoX(Texto t){
    ItemT *te = (ItemT*)t;
    return te->x;
}

double getTextoY(Texto t){
    ItemT *te = (ItemT*)t;
    return te->y;
}

char *getTextoCorP(Texto t){
    ItemT *te = (ItemT*)t;
    return te->corP;
}

char *getTextoCorB(Texto t){
    ItemT *te = (ItemT*)t;
    return te->corB;
}

char *getTextoID(Texto t){
    ItemT *te = (ItemT*)t;
    return te->id;
}

char *getTextoTeX(Texto t){
    ItemT *te = (ItemT*)t;
    return te->tex;
}

char getTextoAP(Texto t){
    ItemT *hi = (ItemT*)t;
    return hi->anchorPoint;
}

Ponto getTextoAnchorPoint(Texto t){
    ItemT *hi = (ItemT*)t;
    //int x;
    //int y;
    int tam;
    Ponto ponto; 
    if(hi->anchorPoint == 'i')
        ponto = criaPonto(hi->x, hi->y);
    else if(hi->anchorPoint == 'm'){ // (numeroDeLetras/2) * 10px
        tam = strlen(hi->tex);
        tam = hi->x + (tam/2) * 10;
        ponto = criaPonto(tam, hi->y);
    } else {
        tam = strlen(hi->tex);
        tam = hi->x + tam * 10;
        ponto = criaPonto(tam, hi->y);
    }

    return ponto; 
}

void setTextoX(Texto t, double x){
    ItemT *te = (ItemT*)t;
    te->x = x;
}

void setTextoY(Texto t, double y){
    ItemT *te = (ItemT*)t;
    te->y = y;
}

void setTextoID(Texto t, char id[]){
    ItemT *te = (ItemT*)t;
    strcpy(te->id,id);
}

void setTextoCorP(Texto t, char corP[]){
    ItemT *te = (ItemT*)t;
    strcpy(te->corP,corP);
}

void setTextoCorB(Texto t, char corB[]){
    ItemT *te = (ItemT*)t;
    strcpy(te->corB,corB);
}

void setTextoTex(Texto t, char Tex[]){
    ItemT *te = (ItemT*)t;
    strcpy(te->tex,Tex);
}

Ponto getTextoPonto(Texto t){
    ItemT *hi = (ItemT*)t;
    Ponto ponto = criaPonto(hi->x, hi->y);
    return ponto;
}

void swapTexto(Texto x, Texto y){
    ItemT *cv1 = (ItemT*)x;
    ItemT *cv2 = (ItemT*)y;
    ItemT temp = *cv1;
    *cv1 = *cv2;
    *cv2 = temp;
}

bool isPontoDentroTexto(Texto t, double x, double y){
    ItemT *te = (ItemT*)t;
    int tamanhoTexto = strlen(te->tex);
    double dx = x - te->x; double dy = y - te->y;
    return dx >= 0 && dx <= (te->x*tamanhoTexto*2) && dy >= 0 && dy <= 3;
}

void desenharTexto(Texto t, double x, double y, FILE* svg){
    ItemT *te = (ItemT*)t;
    x = x * 2;
    y = y * 2;
    fprintf(svg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"%s\" stroke=\"%s\">%s</text>", te->x, te->y, te->corP, te->corB,te->tex);
}