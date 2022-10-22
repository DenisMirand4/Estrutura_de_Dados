#ifndef __fila__
#define __fila__

typedef void* Fila;

typedef void* FilaPosicao;

Fila CriaFila();//CRIA FILA

int FilaVazia(Fila fila);//VERIFICA SE ESTA VAZIA

void FilaAdicionar(FilaPosicao posicao, Fila fila);//ADICIONA UM ELEMENTO

FilaPosicao FilaRemove(Fila fila);//REMOVE UM ELEMENTO E RETORNA A POSICAO INCIAL

#endif