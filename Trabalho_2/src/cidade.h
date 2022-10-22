#ifndef __CIDADE_H
#define __CIDADE_H

#include "lista.h"
#include "ponto.h"
#include "lista.h"
#include "retangulo.h"
#include "circulo.h"
#include "texto.h"
#include "ponto.h"

/*
   Aqui implementamos uma cidade onde todas as listas estão interligadas, este modulo fará a ponte para todas as funções envolvendo as listas e seus elementos
*/

typedef void *Cidade;

enum objetos {RETANGULO = 0, CIRCULO, LINHA, TEXTO, POLIGONO};


/*
 *Cria a struct Cidade e suas listas
 *Não requer nada
 *Retorna uma struct cidade e suas listas
*/

void criarCidade(char diretorio[], char saidDiretorio[], char parGEO[], char parQRY[]);

#endif