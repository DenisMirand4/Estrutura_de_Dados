#ifndef __SVG_H
#define __SVG_H

#include "lista.h"
#include "stdio.h"

FILE* iniciarSvg(char arq[]);//ABRE O ARQUIVO SVG

void fecharSvg(FILE* svg);//FECHA O ARQUIVO SVG

void desenharSvg(FILE* svg, Lista l[4]);//ESCREVE NO SVG COM BASE NA LISTA PASSADA

#endif