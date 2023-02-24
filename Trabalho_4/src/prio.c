#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "ponto.h"
#include "lista.h"
#include "digraph.h"
#include "extras.h"
#include "prio.h"
#include "circulo.h"

typedef struct chv{
    char* from;
    char* to;
    double custo;
}ChaveStruct;

typedef struct node{
    PInfo info;
    double prioridade;
    ChaveStruct *chave;
    struct node *prox;
}NodeStruct;

typedef struct fila{
    NodeStruct *first;
    NodeStruct *last;
    int size;
}FilaStruct;

void printPQ(FilaStruct *fila){
    FilaStruct* f = (FilaStruct*) malloc(sizeof(FilaStruct));
    f->first = NULL;
    f->last = NULL;
    NodeStruct* node = fila->first;
    while(node != NULL){
        node = node->prox;
    }
}

PQueue orderBy(FilaStruct *fila){
    FilaStruct* f = (FilaStruct*) malloc(sizeof(FilaStruct));
    f->first = NULL;
    f->last = NULL;
    NodeStruct* node = fila->first;
    while(node != NULL){
        NodeStruct* node2 = f->first;
        NodeStruct* node3 = NULL;
        while(node2 != NULL){
            if(node->prioridade > node2->prioridade){
                break;
            }
            node3 = node2;
            node2 = node2->prox;
        }
        if(node3 == NULL){
            node->prox = f->first;
            f->first = node;
        }
        else{
            node->prox = node3->prox;
            node3->prox = node;
        }
        if(node->prox == NULL){
            f->last = node;
        }
        node = node->prox;
    }
    return f;
}

int comparaChaves(Chave ch1, Chave ch2){
    ChaveStruct *c1 = (ChaveStruct*) ch1;
    ChaveStruct *c2 = (ChaveStruct*) ch2;
    if(c1->custo < c2->custo){
        return -1;
    }
    else if(c1->custo > c2->custo){
        return 1;
    }
    else{
        return 0;
    }
}

PQueue createPQ(int size, ComparaChavesPQ comp){
    comp = comp;
    FilaStruct* pq =  malloc(size*sizeof(FilaStruct));
    pq->first = NULL;
    pq->last = NULL;
    return pq;
}

bool emptyPQ(PQueue pq){
    FilaStruct* fila = (FilaStruct*) pq;
    if(fila->first == NULL){
        return true;
    }
    return false;
}

void insertPQ(PQueue pq, Chave ch, PInfo info, double prio){
    if(existsPQ(pq, ch) == true){
        puts("Chave ja existe na fila de prioridades");
        return;
    }
    FilaStruct* fila = (FilaStruct*) pq;
    NodeStruct* node = malloc(sizeof(NodeStruct));
    node->chave = ch;
    node->info = info;
    node->prioridade = prio;
    node->prox = NULL;
    if(fila->first == NULL){
        fila->first = node;
        fila->last = node;
    }
    else{
        fila->last->prox = node;
    }
    fila->last = node;
}

bool existsPQ(PQueue pq, Chave ch){
    if(ch == NULL){
        return false;
    }
    FilaStruct* fila = (FilaStruct*) pq;
    ChaveStruct *c = (ChaveStruct*) ch;
    NodeStruct* node = fila->first;
    while(node != NULL){
        if(strcmp(node->chave->from, c->from) == 0 && strcmp(node->chave->to, c->to) == 0){
            return true;
        }
        node = node->prox;
    }
    return false;
}

int priorityPQ(PQueue pq, Chave ch){
    FilaStruct* fila = (FilaStruct*) pq;
    ChaveStruct *c = (ChaveStruct*) ch;
    NodeStruct* node = fila->first;
    while(node != NULL){
        if(strcmp(node->chave->from, c->from) == 0 && strcmp(node->chave->to, c->to) == 0){
            return node->chave->custo;
        }
        node = node->prox;
    }
    return -1;
}

Info removeMaximunPQ(PQueue fila){
    FilaStruct* pq = (FilaStruct*) fila;
    NodeStruct* node = pq->first;
    NodeStruct* nodeMax = NULL;
    NodeStruct* nodeMaxAnt = NULL;
    while(node != NULL){
        if(nodeMax == NULL){
            nodeMax = node;
        }
        else{
            if(node->prioridade > nodeMax->prioridade){
                nodeMax = node;
            }
        }
        node = node->prox;
    }
    if(nodeMax == NULL){
        return NULL;
    }
    node = pq->first;
    while(node != NULL){
        if(node->prox == nodeMax){
            nodeMaxAnt = node;
            break;
        }
        node = node->prox;
    }
    if(nodeMaxAnt == NULL){
        pq->first = nodeMax->prox;
    }
    else{
        nodeMaxAnt->prox = nodeMax->prox;
    }
    if(nodeMax == pq->last){
        pq->last = nodeMaxAnt;
    }
    Info info = nodeMax->info;
    free(nodeMax);
    return info;
    
}

Info getMaximumPQ(PQueue pq){
    FilaStruct* fila = (FilaStruct*) pq;
    NodeStruct* node = fila->first;
    NodeStruct* nodeMax = NULL;
    while(node != NULL){
        if(nodeMax == NULL){
            nodeMax = node;
        }
        else{
            if(node->info > nodeMax->info){
                nodeMax = node;
            }
        }
        node = node->prox;
    }
    if(nodeMax == NULL){
        return NULL;
    }
    return nodeMax->info;

}

void increasePrioPQ(PQueue pq, Chave ch, double dp){
    FilaStruct* fila = (FilaStruct*) pq;
    ChaveStruct *c = (ChaveStruct*) ch;
    NodeStruct* node = fila->first;
    while(node != NULL){
        if(strcmp(node->chave->from, c->from) == 0 && strcmp(node->chave->to, c->to) == 0){
            node->chave->custo += dp;
            node->prioridade += dp;
            return;
        }
        node = node->prox;
    }

}
