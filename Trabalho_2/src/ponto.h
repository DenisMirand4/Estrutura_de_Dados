#ifndef __PONTO_H
#define __PONTO_H

#include "stdio.h"


typedef void *Ponto;
/*
 *cria uma struct do tipo PONTO
 *Requer a informações que formam o ponto como x e y
 *Devolve uma struct com valores definidos
*/
Ponto criaPonto(double x, double y);

Ponto getPontoPonto(Ponto p);

/*
    Retorna o valor X do ponto P
*/
double pontoX(Ponto p);

/*
    Retorna o valor Y do ponto P
*/
double pontoY(Ponto p);

/*
    Calcula a distancia do ponto  com os pontos x e y
*/
double getPontoDist(Ponto pont, double x, double y);

/*
    Atribui o valor do p2 no ponto p1
*/
void pontoXY(Ponto p, double x, double y);


void atribuirPonto(Ponto p1, Ponto p2);

/*
    Troca o valor de dois pontos
*/
void swapPonto(Ponto x, Ponto y);

/*
    Desenha o ponto no svg
*/
void desenharPonto(Ponto pont, FILE* svg);

#endif