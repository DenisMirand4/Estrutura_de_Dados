#ifndef __RETANGULO_H
#define __RETANGULO_H
#include <stdbool.h>
#include "ponto.h"

/*
  Aqui está implementado uma TAD do tipo Retangulo, contendo todas as funções necessarias para criar um retangulo.
*/


typedef void *Retangulo;

/*
 *Cria uma struct do tipo retangulo
 *Requer a informações que formam o retangulo como ID, cor da borda, cor do preenchimento, largura, altura, posição , espessura da bora, opacidade e borda tracejada;
 *Caso não queira a borda tracejada, definir bordaTracejada = 0;
 *Devolve uma struct com valores definidos
*/
Retangulo criaRetangulo(char id[20], char corB[20], char corP[20], char px[20], double largura, double altura, double x, double y);


void setRetanguloDano(Retangulo r, double dano);
int getRetanguloVida(Retangulo r);
double getRetanguloPontosInativacao(Retangulo r);
double getRetanguloPontosDestruicao(Retangulo r);

/* 
 *Função responsável por obter o valor do x na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve o x da forma
*/
double getRetanguloX(Retangulo r);

/* 
 *Função responsável por obter o valor do y na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve o y da forma
*/
double getRetanguloY(Retangulo r);

/* 
 *Função responsável por obter o valor da largura na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve a largura da forma
*/
double getRetanguloWidth(Retangulo r);


/* 
 *Função responsável por obter o valor da altura na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve a altura da forma
*/
double getRetanguloHeight(Retangulo r);


/* 
 *Função responsável por obter o valor do Id na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve o Id da forma
*/
char *getRetanguloID(Retangulo r);

/* 
 *Função responsável por obter a cor da forma na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve a cor da forma
*/
char *getRetanguloCorP(Retangulo r);

/* 
 *Função responsável por obter o valor da cor da borda na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve a cor da borda da forma
*/
char *getRetanguloCorB(Retangulo r);

/* 
 *Função por responder se a borda do retangulo e tracejada ou não na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve o valor da variavel bordaTracejada
*/
double getRBordaTracejada(Retangulo r);

/* 
 *Função responsável por definir o x da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setRetanguloX(Retangulo r, double x);

/* 
 *Função responsável por definir o y da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setRetanguloY(Retangulo r, double y);

/* 
 *Função responsável por definir a largura da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setRetanguloWidth(Retangulo r, double w);

/* 
 *Função responsável por definir a altura da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setRetanguloHeight(Retangulo r, double h);

/* 
 *Função responsável por definir a espessura da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setREspessura(Retangulo r, char espessura[10]);

/* 
 *Função responsável por definir o Id da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setRetanguloID(Retangulo r, char id[]);

/* 
 *Função responsável por definir a cor da forma da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setRetanguloCorP(Retangulo r, char corP[]);

/* 
 *Função responsável por definir a cor da borda da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setRetanguloCorB(Retangulo r, char corB[]);

/*
*Função que passa as coordenadas do retangulo como um ponto
*Requer o retangulo
*Retorna um ponto
*/

Ponto getPontoRetangulo(Retangulo p);

double getEnergiaRetangulo(Retangulo r);

void setEnergiaRetangulo(Retangulo r, double energia);

double getMoedaRetangulo(Retangulo r);

void setMoedaRetangulo(Retangulo r, double moeda);

double getRiquezaRetangulo(Retangulo r);

void setRiquezaRetangulo(Retangulo r, double riqueza);

/*
*Troca as informações entre dois retangulos
*Requer os dois retangulos
*Retorna void
*/
void swapRetangulo(Retangulo x, Retangulo y);


bool isPontoDentroRetangulo(Retangulo r, double x, double y);

/*
*Desenha o retangulo no .svg
*Requer o retangulo e o svg
*Retorna void
*/

void desenharRetangulo(Retangulo r, double x, double y, FILE* svg);
#endif