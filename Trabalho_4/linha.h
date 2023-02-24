  
#ifndef __Linha_H
#define __Linha_H
#include "ponto.h"
#include <stdbool.h>

/*
  Aqui está implementado uma TAD do tipo Linha, contendo todas as funções necessarias para criar um Linha.
*/


typedef void *Linha;

void setLinhaDano(Linha c, double dano);
int getLinhaVida(Linha c);
double getLinhaPontosInativacao(Linha c);
double getLinhaPontosDestruicao(Linha c);

/*
 *Cria uma struct do tipo Linha
 *Requer a informações que formam o Linha como ID, cor da borda, cor do preenchimento, largura, altura, posição , espessura da bora, opacidade e borda tracejada;
 *Caso não queira a borda tracejada, definir bordaTracejada = 0;
 *Devolve uma struct com valores definidos
*/
Linha criaLinha(char id[50], char corP[50],char from[50], char to[50], char ldir[50],char lesq[50], double cmp, double vm, double x1, double y1, double x2, double y2, int fromNum, int toNum);

int getLinhaFromNum(Linha l);
int getLinhaToNum(Linha l);
char *getLinhaFrom(Linha r);
char *getLinhaTo(Linha r);
char *getLinhaID(Linha r);

/* 
 *Função responsável por obter o valor do x na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve o x da forma
*/
double getLinhaX1(Linha r);
double getLinhaX2(Linha r);

/* 
 *Função responsável por obter o valor do y na struct
 * Requer o endereço da struct a ter sua informação adquirida
 * Devolve o y da forma
*/
double getLinhaY1(Linha r);
double getLinhaY2(Linha r);

void setLinhaX1(Linha r, float valor);
void setLinhaX2(Linha r, float valor);
void setLinhaY1(Linha r, float valor);
void setLinhaY2(Linha r, float valor);

double getLinhaCmp(Linha r);
double getLinhaVm(Linha r);
void setLinhaCmp(Linha r, float valor);
void setLinhaVm(Linha r, float valor);

double getLinheMenorX(Linha r);
double getLinheMenorY(Linha r);
double getLinheMaiorY(Linha r);
double getLinheMaiorX(Linha r);
char *getLinhaLdir(Linha r);
char *getLinhaLesq(Linha r);

/*
*Troca as informações entre dois Linhas
*Requer os dois Linhas
*Retorna void
*/
void swapLinha(Linha x, Linha y);

/*
*Desenha o Linha no .svg
*Requer o Linha e o svg
*Retorna void
*/
Ponto getLinhaPonto(Linha r);

bool isPontoDentroLinha(Linha r, double x, double y);

bool isLinhaDentroRetangulo(Linha r, double x, double y, double w, double h);
bool isLinhaParcialmenteDentroRetangulo(Linha r, double x, double y, double w, double h);

void desenharLinha(Linha r, double x, double y, FILE* svg);

#endif