#ifndef __FORMASGEOMETRICAS_H
#define __FORMASGEOMETRICAS_H
#define MAX 1000
#include "lista.h"

////////////////////////////PONTO//////////////////////////////////////

typedef void *Ponto;

Ponto criar_ponto(double x, double y);//CRIA UM PONTO

double get_ponto_x(Ponto p);//RETORNA O VALOR X DO PONTO

double get_ponto_y(Ponto p);//RETORNA O VALOR Y DO PONTO

void desenhar_ponto(Ponto pont, FILE* svg);//DESENHA PONTO NO SVG

////////////////////////CIRCULO///////////////////////////////////////////

typedef void *Circulo;

Circulo criar_circulo(char id[20], char corB[20], char corp[20], double raio, double x, double y);//CRIA UM CIRCULO

double get_circulo_x(Circulo c);//RETORNA O VALOR X DO CIRCULO

double get_circulo_y(Circulo c);//RETORNA O VALOR Y DO CIRCULO

double get_circulo_raio(Circulo c);//RETORNA O VALOR DO RAIO DO CIRCULO

char *get_circulo_id(Circulo c);//RETORNA O ID DO CIRCULO

void set_circulo_x(Circulo c, double x);//DEFINE O VALOR X DO CIRCULO PARA O INSERIDO

void set_circulo_y(Circulo c, double y);//DEFINE O VALOR Y DO CIRCULO PARA O INSERIDO

void set_circulo_corp(Circulo c, char corp[]);//DEFINE O VALOR CORP DO CIRCULO PARA O INSERIDO

void set_circulo_corb(Circulo c, char corB[]);//DEFINE O VALOR CORB DO CIRCULO PARA O INSERIDO

Ponto get_circulo_ponto(Circulo c);//RETORNA O PONTO(X,Y) DO CIRCULO DADO

void desenhar_circulo(Circulo c, FILE* svg);//DESENHA CIRCULO NO SVG

////////////////////////////LINHA////////////////////////////////////

typedef void *Linha;

Linha cria_linha(char id[20], char corp[20], double x1, double y1, double x2, double y2);//CRIA UMA LINHA

char *get_linha_id(Linha r);//RETORNA O ID DA LINHA

double get_linha_x1(Linha r);//RETORNA O VALOR X1 DA LINHA

double get_linha_x2(Linha r);//RETORNA O VALOR X2 DA LINHA

double get_linha_y1(Linha r);//RETORNA O VALOR Y1 DA LINHA

double get_linha_y2(Linha r);//RETORNA O VALOR Y2 DA LINHA

void set_linha_x1(Linha r, float valor);//DEFINE O VALOR X1 DA LINHA PARA O INSERIDO

void set_linha_x2(Linha r, float valor);//DEFINE O VALOR X2 DA LINHA PARA O INSERIDO

void set_linha_y1(Linha r, float valor);//DEFINE O VALOR Y1 DA LINHA PARA O INSERIDO

void set_linha_y2(Linha r, float valor);//DEFINE O VALOR X2 DA LINHA PARA O INSERIDO

double get_linha_menor_X(Linha r);//RETORNA O MENOR VALOR DE X DA LINHA

double get_linha_menor_y(Linha r);//RETORNA O MENOR VALOR DE Y DA LINHA

double get_linhe_maior_x(Linha r);//RETORNA O MAIOR VALOR DE X DA LINHA

double get_linha_maior_y(Linha r);//RETORNA O MAIOR VALOR DE X DA LINHA

Ponto get_linha_ponto(Linha r);//RETORNA O MENOR PONTO X DA LINHA

void desenhar_linha(Linha r, FILE* svg);//DESENHA UMA LINHA NO SVG

////////////////////////POLIGONO/////////////////////////////////////////

typedef void *Poligono;

Poligono cria_poligono(Lista pontos, char cor[], int id, char corp[]);//CRIA UM POLIGONO

void desenhar_poligono(Poligono c, FILE* svg);//DESENHA UM POLIGONO NO SVG

//////////////////////////RETANGULO/////////////////////////////////

typedef void *Retangulo;

Retangulo cria_retangulo(char id[20], char corB[20], char corp[20], double largura, double altura, double x, double y);//CRIA UM RETANGULO

double get_retangulo_x(Retangulo r);//RETORNA O VALOR X DO RETANGULO


double get_retangulo_y(Retangulo r);//RETORNA O VALOR Y DO RETANGULO

double get_retangulo_width(Retangulo r);//RETORNA O VALOR W DO RETANGULO

double get_retangulo_height(Retangulo r);//RETORNA O VALOR H DO RETANGULO

char *get_retangulo_id(Retangulo r);//RETORNA O ID DO RETANGULO

void set_retangulo_x(Retangulo r, double x);//DEFINE O VALOR X DO RETANGULO PARA O INSERIDO

void set_retangulo_y(Retangulo r, double y);//DEFINE O VALOR Y DO RETANGULO PARA O INSERIDO

void set_retangulo_corp(Retangulo r, char corp[]);//DEFINE O VALOR CORP DO RETANGULO PARA O INSERIDO

void set_retangulo_corb(Retangulo r, char corB[]);//DEFINE O VALOR CORB DO RETANGULO PARA O INSERIDO

Ponto get_ponto_retangulo(Retangulo p);//RETORNA AS CORDENADAS DO RETANGULO COMO UM PONTO

void desenhar_retangulo(Retangulo r, FILE* svg);//DESENHA UM RETANGULO NO SVG

/////////////////////////TEXTO//////////////////////////////////

typedef void *Texto;

Texto cria_texto(char id[20], char corB[20], char corp[20], char txto[], double x, double y, char anchorPoint);//CRIA UM TEXTO

double get_texto_x(Texto t);//RETORNA O VALOR X DO TEXTO

double get_texto_y(Texto t);//RETORNA O VALOR Y DO TEXTO

char *get_texto_id(Texto t);//RETORNA O ID DO TEXTO

char get_texto_ap(Texto t);//RETORNA O VALOR ANCORA DO TEXTO

char *get_texto_text(Texto t);//RETORNA O VALOR TEXTO DO TEXTO

Ponto get_texto_anchor_point(Texto t);//RETORNA O VALOR DA ANCORA COMO UM PONTO DO TEXTO

void set_texto_x(Texto t, double x);//DEFINE O VALOR X DO TEXTO PARA O INSERIDO

void set_texto_y(Texto t, double y);//DEFINE O VALOR Y DO TEXTO PARA O INSERIDO

void set_texto_corp(Texto t, char corp[]);//DEFINE O VALOR CORP DO TEXTO PARA O INSERIDO

void set_texto_corb(Texto t, char corB[]);//DEFINE O VALOR CORB DO TEXTO PARA O INSERIDO

void desenhar_texto(Texto t, FILE* svg);//DESENHA UM TEXTO NO SVG

#endif