#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"
#include "extras.h"


typedef struct PONTO {
    double x, y; 
} ponto;

Ponto criaPonto(double x, double y){
    ponto *p;
    p = (ponto *)calloc(1, sizeof(ponto));
    p->x = x;
    p->y = y;

    return p;
}


double pontoX(Ponto p){
    ponto *tp = (ponto*) p;
    return tp->x;
}

double pontoY(Ponto p){
    ponto *tp = (ponto*) p;
    return tp->y;
}

void swapPonto(Ponto x, Ponto y){
    ponto *cv1 = (ponto*)x;
    ponto *cv2 = (ponto*)y;
    ponto temp = *cv1;
    *cv1 = *cv2;
    *cv2 = temp;
}

double getPontoDist(Ponto pont, double x, double y) {
    ponto *tp = (ponto*) pont;
    return distancia(tp->x, tp->y, x, y);
}

void pontoXY(Ponto p, double x, double y){
    ponto *tp = (ponto*) p;
    tp->x = x;
    tp->y = y;
}

void atribuirPonto(Ponto p1, Ponto p2){  
    ponto *cv1 = (ponto*)p1;
    ponto *cv2 = (ponto*)p2;
    *cv1 = *cv2;  
}


void desenharPonto(Ponto pont, FILE* svg) {
    ponto* p = (ponto*) pont;
    fprintf(svg,"\t<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"black\" />\n", p->x, p->y);
}