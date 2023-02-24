#ifndef __CIRCULO_H
#define __CIRCULO_H
#include "ponto.h"
#include <stdbool.h>

typedef void *Circulo;

/*
 *cria uma struct do tipo circulo
 *Requer a informações que formam o circulo como id, cor, posição, etc
 *Devolve uma struct com valores definidos
*/
Circulo criaCirculo(char id[50], double x, double y, int num);

/* 
 *Função responsável por obter o valor da espessura na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve a espessura da forma
*/
char *getCEspessura(Circulo c);

/* 
 *Função responsável por obter o valor do x na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve o x da forma
*/
double getCirculoX(Circulo c);

/* 
 *Função responsável por obter o valor do y na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve o y da forma
*/
double getCirculoY(Circulo c);

/* 
 *Função responsável por obter o valor do raio na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve o raio da forma
*/
double getCirculoRaio(Circulo c);

/* 
 *Função responsável por obter o valor do Id na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve o Id da forma
*/
char *getCirculoID(Circulo c);

/* 
 *Função responsável por obter a cor da forma na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve a cor da forma
*/
char *getCirculoCorP(Circulo c);

/* 
 *Função responsável por obter o valor da cor da borda na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve a cor da borda da forma
*/
char *getCirculoCorB(Circulo c);
bool getCirculoVisited(Circulo c);
void setCirculoVisited(Circulo c, bool visited);


int getCirculoVida(Circulo c);
void setCirculoDano(Circulo c, double dano);
double getCirculoPontosInativacao(Circulo c);
double getCirculoPontosDestruicao(Circulo c);
int getCirculoNum(Circulo c);
void setCirculoNum(Circulo c, int num);


/* 
 *Função responsável por definir a espessura da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setCEspessura(Circulo c, char espessura);

/* 
 *Função responsável por definir o x da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setCirculoX(Circulo c, double x);

/* 
 *Função responsável por definir o y da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setCirculoY(Circulo c, double y);

/* 
 *Função responsável por definir raio da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setCirculoRaio(Circulo c, double r);

/* 
 *Função responsável por definir o Id da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setCirculoID(Circulo c, char id[]);

/* 
 *Função responsável por definir a cor da forma da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setCirculoCorP(Circulo c, char corP[]);

/* 
 *Função responsável por definir a cor da borda da struct
 * Requer o endereço da struct a ter sua informação adquirida e o valor a ser definido
 * Devolve nenhum dado
*/
void setCirculoCorB(Circulo c, char corB[]);

/*
*Retorna o local do circulo como um Ponto
*Rqeuer o circulo
*Retorna o Ponto
*/
Ponto getCirculoPonto(Circulo c);

/*
*Troca os valores de dois circulos
*Requer os dois circulos
*Retorna nada
*/
void swapCirculo(Circulo x, Circulo y);

bool isPontoDentroCirculo(Circulo c, double x, double y);

/*
*Desenha o circulo no svg
*Requer o circulo
*Retorna nada
*/
void desenharCirculo(Circulo c, double x, double y, FILE* svg);

#endif