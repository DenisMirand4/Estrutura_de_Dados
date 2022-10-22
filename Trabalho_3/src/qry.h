#ifndef __QRY_H
#define __QRY_H
#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "srbTree.h"
#include "fila.h"

/*
    Funções responsáveis pelos comandos do file .qry
*/

// void tp(SRbTree arvores[5], FILE *saida, double x, double y, double *pontuacao);

// void tr(SRbTree arvores[5], FILE *saida, double x, double y, double dx, double dy, int id);

// void be(SRbTree arvores[5], FILE *saida, double x, double y, double w, double h, double *pontuacao, double agressividade);

void energiza(SRbTree arvores[4],FILE *saida, double energia);

void mv(SRbTree arvores[4], FILE *saida, double x, double y, char* id);

void lr(SRbTree arvores[4], FILE *saida,FILE *svg, char* id, char* lado, double distancia, double w, double h);

void dispara(SRbTree arvores[4], FILE *saida, FILE *svg, char* id, char* lado, double d);

void mc(SRbTree arvores[4], FILE *saida, double dx, double dy, double x, double y, double w, double h);

#endif