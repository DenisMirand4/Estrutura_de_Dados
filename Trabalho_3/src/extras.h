#ifndef __EXTRAS_H
#define __EXTRAS_H
#include "lista.h"
#include "ponto.h"



double maior(double x, double y);

/*
* Retorna o maior numero entre dois numeros
* Requer dois float
* Retorna um Float
*/
double menor(double x, double y);

double modulo(double x);
/*
* Retorna o menor numero entre dois numeros
* Requer dois floats
* Retorna um floar
*/
double distancia(double x1, double y1, double x2, double y2);

int pontoInternoCirculo(double x, double y, double xC, double yC, double r);

int pontoInternoRetangulo(double x, double y, double xRet, double yRet, double w, double h);




int getIndex(char r[]);

int insidePolygon(Lista pontos, Ponto ponto);

int strInList(Lista lista, char* info);

Info getIndexInfo(Lista list, int i);

Info getInsideList(Lista list, char id[], int tipo);

#endif