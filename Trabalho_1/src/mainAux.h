#ifndef __MAINAUX_H
#define __MAINAUX_H

#include "lista.h"
#include "lista.h"
#include "formasGeometricas.h"

typedef void *Base;

enum objetos {RETANGULO = 0, CIRCULO, LINHA, TEXTO, POLIGONO};

void criarBase(char pathArquivo[], char pathSaida[], char pathGEO[], char pathQRY[]);//CRIA A BASE PARA CHAMAR AS OUTRAS FUNÇÕES

#endif