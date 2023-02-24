#ifndef __Texto_H
#define __Texto_H
#include "ponto.h"
#include <stdbool.h>

/*
  Aqui está implementado uma TAD do tipo Texto, contendo todas as funções necessarias para criar texto em um SVG.
*/


typedef void *Texto;


void setTextoDano(Texto c, double dano);
int getTextoVida(Texto c);
double getTextoPontosInativacao(Texto c);
double getTextoPontosDestruicao(Texto c);
/*
 *Cria uma struct do tipo texto
 *Requer a informações que formam o texto como id, cor, posição, etc
 *Devolve uma struct com valores definidos
*/
Texto criaTexto(char id[20], char corB[20], char corP[20], char tex[], double x, double y, char anchorPoint);

/* 
 *Função responsável por obter o valor do x na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve a posição y do texto
*/
double getTextoX(Texto t);

/* '
 *Função responsável por obter o valor do y na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve a posição y do texto
*/
double getTextoY(Texto t);

/* 
 *Função responsável por obter a cor da forma na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve a posição y do texto
*/
char *getTextoCorP(Texto t);

/* 
 *Função responsável por obter o valor da cor da borda na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve a cor da borda do texto
*/
char *getTextoCorB(Texto t);

/* 
 *Função responsável por obter o valor do Id na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve o Id do texto
*/
char *getTextoID(Texto t);

char getTextoAP(Texto t);

/* 
 *Função responsável por obter o valor do texto na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve o texto
*/
char *getTextoTeX(Texto t);

Ponto getTextoAnchorPoint(Texto t);

/* 
 *Função responsável por definir o x da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setTextoX(Texto t, double x);

/* 
 *Função responsável por definir o y da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setTextoY(Texto t, double y);

/* 
 *Função responsável por definir o Id da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setTextoID(Texto t, char id[]);

/* 
 *Função responsável por definir a cor da forma da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setTextoCorP(Texto t, char corP[]);

/* 
 *Função responsável por definir a cor da borda da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setTextoCorB(Texto t, char corB[]);

/* 
 *Função responsável por definir o texto da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setTextoTex(Texto t, char Tex[]);
/*
*Função que cria um ponto com as coordenadas do texto
*Requer o texto
*Retorna um ponto
*/
Ponto getTextoPonto(Texto t);
/*
*Troca as informações de dois textos
*Requer dois textos
*Retorna nada
*/
void swapTexto(Texto x, Texto y);
/*
*Função que desenha o texto
*Requer o texto e o .svg
*Retorna nada
*/

bool isPontoDentroTexto(Texto t, double x, double y);

void desenharTexto(Texto t, double x, double y, FILE* svg);

#endif