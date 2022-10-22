#ifndef __LISTA_H
#define __LISTA_H


typedef void* No;
typedef void* Lista;
typedef void* ListaPosicao;
typedef void* Posicao;

Lista CriarLista();//CRIA UMA LISTA

int TamanhoLista(Lista lista);//RETORNA O TAMANHO DA LISTA

Posicao InserirFinalLista(Lista lista, ListaPosicao info);//ADICIONA E RETORNA O NÓ NO FIM DA LISTA

void RemoveNoLista(Lista lista, Posicao position);//REMOVE O NÓ DA POSICAO FORNECIDA

Posicao UltimoDaLista(Lista lista);//RETORNA ULTIMO NÓ DA LISTA

Posicao PrimeiroDaLista(Lista lista);//RETORNA PRIMEIRO NÓ DA LISTA

ListaPosicao ValorPosicao(Posicao p);//RETORNA OS DADOS DA POSICAO FORNECIDA

Posicao ProximaPosicao(Lista lista, Posicao p);//RETORNA PROXIMO NO DA LISTA

Posicao PosicaoAnterior(Lista lista, Posicao p);//RETORNA NÓ ANTERIOR DA LISTA

ListaPosicao getInsideList(Lista ListaStr, char id[], int tipo);//RETORNA A POSICAO NA LISTA COM BASE NO ID E TIPO PASSADO

void DesalocarLista(Lista lista);//DESALOCA LISTA

#endif