#ifndef __QRY_H
#define __QRY_H
#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "srbTree.h"
#include "digraph.h"
#include "fila.h"

/*
    Funções responsáveis pelos comandos do file .qry
*/
typedef void* geoPosicao;

geoPosicao armazenaEndereco(SRbTree arvore, FILE *svg, char* cep, char* face, double num);

void desenharPos(FILE* svg, geoPosicao pos);
void desenharPosF(FILE* svg, geoPosicao pos);


void catac(SRbTree arvore, Digraph dg, FILE *saida, FILE *svg, double x, double y, double w, double h);

void pnt(SRbTree arvore, FILE *saida, char *cep, char* cfill, char* cstrk);

void blq(Digraph dg, FILE *saida,char* sentido, double x, double y, double w, double h, Lista result);

void rf(SRbTree arvore, Digraph dg, FILE *saida, FILE *svg, char* cep, char *face, double fator);

void b(Digraph dg, FILE *saida, FILE *svg, double x, double y, double fator);

geoPosicao p(SRbTree arvore, Digraph dg, FILE *saida, FILE *svg, char* cep, char* face, double num, char* cmc, char* cmr, geoPosicao info, int i);

#endif