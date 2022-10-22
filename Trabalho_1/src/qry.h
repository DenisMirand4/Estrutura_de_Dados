#ifndef __QRY_H
#define __QRY_H
#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "fila.h"


void funcao_inp(FILE *saidaTXT, Lista listas[], Fila filaPoligonos, char *id);//EXECUTA FUNCAO INP

void funcao_dels(FILE *saidaTXT, Lista listas[], Lista selecionados);//EXECUTA FUNCAO DELS

void funcao_sel(FILE *saidaTXT, Lista listas[], Lista selecionados, double x, double y, double w, double h);//EXECUTA FUNCAO SEL

void funcao_dps(Lista listas[],Lista selecionados, int id, double x, double y, char *corB, char *corp);//EXECUTA FUNCAO DPS

void funcao_pol(Lista listas[], Fila filaPoligonos, char *corB, char *corp);//EXECUTA FUNCAO POL

void funcao_ups(Lista listas[], Lista selecionados, char *corB, char *corp, float x, float y, int n);//EXECUTA FUNCAO UPS

#endif