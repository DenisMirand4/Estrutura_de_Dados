#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "lista.h"
#include "string.h"
#include "formasGeometricas.h"
#include "mainAux.h"

typedef struct No{
    ListaPosicao posicao;
    struct No *anterior;
    struct No *proxima;
} no;

typedef struct lista
{
    int tamanho;
    no *primeiro;
    no *ultimo;
} ListaStr;

Lista CriarLista(){
    ListaStr* lista = (ListaStr*) malloc(sizeof(ListaStr));
    if(lista==NULL){
        printf("Erro ao criar a lista\n");
        exit(1);
    }
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
    return lista;
}

int TamanhoLista(Lista lista){    
    Posicao posicao= PrimeiroDaLista(lista);
    int i = 0;
    while (posicao != NULL){
        i++;
        posicao = ProximaPosicao(lista, posicao);
    }
    return i;
}

Posicao InserirFinalLista(Lista lista, ListaPosicao posicao){
    ListaStr *listaAux = (ListaStr *)lista;
    no *nodeAux;
    no *nodeInsert = (no *)malloc(sizeof(no));
    nodeInsert->posicao = posicao;

    if (listaAux->primeiro == NULL) {
        listaAux->primeiro = nodeInsert;
        nodeInsert->anterior = NULL;
        nodeInsert->proxima = NULL;

        listaAux->ultimo = nodeInsert;
        listaAux->tamanho++;
        return nodeInsert;
    } else {
        nodeAux = listaAux->ultimo;
        nodeAux->proxima = nodeInsert;
        nodeInsert->anterior = nodeAux;
        nodeInsert->proxima = NULL;
        listaAux->ultimo = nodeInsert;
        listaAux->tamanho++;
        return nodeInsert;
    }    
}

void RemoveNoLista(Lista lista, Posicao position){
    ListaStr *listaAuxiliar = (ListaStr *)lista;
    no *noAuxiliar = (no *)position;
    no *noAnterior = NULL;
    no *noProximo = NULL;

    if (noAuxiliar == NULL) {        
        return;
    } else {
        if (noAuxiliar == listaAuxiliar->primeiro) {       //caso primeiro elemento da lista
            noProximo = noAuxiliar->proxima;
            listaAuxiliar->primeiro = noProximo;
            noProximo->anterior = NULL;

            free(noAuxiliar);
            
            listaAuxiliar->tamanho--;
        } else if (noAuxiliar == listaAuxiliar->ultimo) {  //caso último elemento da lista
            noAnterior = noAuxiliar->anterior;
            listaAuxiliar->ultimo = noAnterior;
            noAnterior->proxima = NULL;

            free(noAuxiliar);
            listaAuxiliar->tamanho--;
        } else {                                           //caso no meio da lista
            noAnterior = noAuxiliar->anterior;
            noProximo = noAuxiliar->proxima;
            noAnterior->proxima = noProximo;
            noProximo->anterior = noAnterior;
            free(noAuxiliar);
            listaAuxiliar->tamanho--;
        }
        return;
    }
}

ListaPosicao ValorPosicao(Posicao p) {
    no *node_auxiliar = (no *) p;
    if (p == NULL) {
        return NULL;
    } else {
        return node_auxiliar->posicao;
    }
}

Posicao PrimeiroDaLista(Lista lista) {
    ListaStr *lista_aux = (ListaStr *)lista;
    if (lista_aux->tamanho == 0) {
        return NULL;
    } else {
        return lista_aux->primeiro;
    }
}

Posicao UltimoDaLista(Lista lista) {
    ListaStr *lista_aux = (ListaStr *)lista;
    if (lista_aux->tamanho == 0) {
        printf("Não há elementos na lista\n");
        return NULL;
    } else {
        return lista_aux->ultimo;
    }
}


Posicao ProximaPosicao(Lista lista, Posicao p) {
    ListaStr *lista_aux = (ListaStr *)lista;
    no *nodeAux = (no *)p;
    if (nodeAux == lista_aux->ultimo) {
        return NULL;
    } else {
        return nodeAux->proxima;
    }
}

Posicao PosicaoAnterior(Lista lista, Posicao p) {
    ListaStr *lista_aux = (ListaStr *)lista;
    no *node_aux = (no *)p;
    if (node_aux == lista_aux->primeiro) {
        return NULL;
    } else {
        return node_aux->anterior;
    }
}

ListaPosicao getInsideList(Lista ListaStr, char id[], int tipo){
    No node;
    ListaPosicao posicao;
    for(node = PrimeiroDaLista(ListaStr); node != NULL; node = ProximaPosicao(ListaStr, node)){
        posicao = ValorPosicao(node);
        if(tipo == RETANGULO){
            if(strcmp(get_retangulo_id(posicao), id) == 0)
                return node;
        }
        if(tipo == CIRCULO){
            if(strcmp(get_circulo_id(posicao), id) == 0)
                return node;
        }
        if(tipo == TEXTO){
            if(strcmp(get_texto_id(posicao), id) == 0)
                return node;
        }
        if(tipo == LINHA){
            if(strcmp(get_linha_id(posicao), id) == 0)
                return node;
        }
    }
    return NULL;
}

void DesalocarLista(Lista lista){
    ListaStr *lista_aux = (ListaStr *)lista;
    no *ultimo = lista_aux->ultimo;
    while (ultimo != NULL)
    {
        no * prev = ultimo->anterior;
        free(ultimo);
        ultimo = prev;
    }
    lista_aux->primeiro = lista_aux->ultimo = NULL;

}
