#ifndef __QRY_H
#define __QRY_H
#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "xyytree.h"
#include "fila.h"

/*
    Funções responsáveis pelos comandos do file .qry
*/

void tp(XyyTree arvores[5], FILE *saida, double x, double y, double *pontuacao);

void tr(XyyTree arvores[5], FILE *saida, double x, double y, double dx, double dy, int id);

void be(XyyTree arvores[5], FILE *saida, double x, double y, double w, double h, double *pontuacao, double agressividade);


#endif