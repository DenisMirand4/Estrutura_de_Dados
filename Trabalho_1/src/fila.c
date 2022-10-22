#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct no{
    FilaPosicao posicao;
    struct no *proxima;
}NoStr;

typedef struct fila{
    NoStr *primeiro;
    NoStr *ultimo;
}FilaStr;

Fila CriaFila(){
    FilaStr* f = (FilaStr*)malloc(sizeof(FilaStr));
    f->primeiro = NULL;
    f->ultimo = NULL;
    return f;
}

int FilaVazia(Fila Fila){
    FilaStr* f = (FilaStr*) Fila;
    return f->primeiro == NULL;
}

void FilaAdicionar(FilaPosicao posicao, Fila fila){
    FilaStr* f = (FilaStr*) fila;
    NoStr* no = (NoStr*)malloc(sizeof(NoStr));
    no->posicao = posicao;
    no->proxima = NULL;
    if(f->primeiro == NULL){
        f->primeiro = no;
        f->ultimo = no;
    }
    else{
        f->ultimo->proxima = no;
    }
    f->ultimo = no;
}

FilaPosicao FilaRemove(Fila fila){
    FilaStr* f = (FilaStr*) fila;
    NoStr* no = f->primeiro;
    FilaPosicao posicao = no->posicao;
    f->primeiro = no->proxima;
    if(f->ultimo == no){
        f->ultimo = NULL;
    }
    free(no);
    return posicao;
}