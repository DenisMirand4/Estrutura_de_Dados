#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "xyytree.h"
#include "ponto.h"
#include "extras.h"
#include "fila.h"

#define esq 0
#define mei 1
#define dir 2

typedef struct node{
    struct node *children[3];
    struct node *parent;
    Ponto ponto;
    Info info;
}NoStruct;

typedef struct xyytree{
    NoStruct* root;
    double fd;
}XyyStruct;

XyyTree newXyyTree (double fd){
    XyyStruct* xyy = (XyyStruct*)malloc(sizeof(XyyStruct));
    xyy->root = NULL;
    xyy->fd = fd;
    return xyy;
}



void insere(XyyStruct* t, NoStruct* node){
    NoStruct* aux = t->root;
    node->parent = NULL;
    for(int i = 0; i < 3; i++){
        node->children[i] = NULL;
    }
    if(aux == NULL){
        t->root = node;
        return;
    }
    do{
        Ponto pAux = aux->ponto;
        Ponto p = node->ponto;
        if(pontoX(p) <= pontoX(pAux)){
            if(pontoY(p) <= pontoY(pAux)){
                if(aux->children[dir] == NULL){
                    aux->children[dir] = node;
                    node->parent = aux;
                }
                else{
                    aux = aux->children[dir];
                }
            }
            else{
                if(aux->children[mei] == NULL){
                    aux->children[mei] = node;
                    node->parent = aux;
                }
                else{
                    aux = aux->children[mei];
                }
            }
        }
        else{
            if(aux->children[esq] == NULL){
                aux->children[esq] = node;
                node->parent = aux;
            }
            else{
                aux = aux->children[esq];
            }
            
        }
    }while(node->parent == NULL);
}

Node insertXyyT (XyyTree t, double x, double y, Info i){
    XyyStruct* xyy = (XyyStruct*) t;
    NoStruct* node = (NoStruct*)malloc(sizeof(NoStruct));
    node->ponto = criaPonto(x, y);
    node->info = i;
    insere(xyy,node);
    return node;
}

Node getNodeXyyT (XyyTree t, double x, double y, double epsilon){
    XyyStruct* xyy = (XyyStruct*) t;
    NoStruct* aux = xyy->root;
    Ponto p;
    xyy->fd -= epsilon;

    while (aux != NULL){
        p = aux->ponto;
        if(pontoInternoCirculo(pontoX(p), pontoY(p), x, y, epsilon)){
            return aux;
        }
        if(x <= pontoX(p)){
            if(y > pontoY(p)){
                aux = aux->children[mei];
            }
            else{
                aux = aux->children[dir];
            }
        }
        else{
            aux = aux->children[esq];
        }
    }
    return NULL;
}


Info getInfoXyyT(XyyTree t, Node pNo){
    NoStruct* node = (NoStruct*) pNo;
    t = t;
    return node->info;
}

void removeNoXyyT (XyyTree t, Node n){
    if(n == NULL)
        return;
    XyyStruct* xyy = (XyyStruct*) t;
    NoStruct* node = (NoStruct*) n;
    NoStruct* aux;
    int i;
    Fila fila = createQueue();
    if(node->parent == NULL){
        for(i = 0; i < 3; i++){
            if(node->children[i] != NULL){
                enqueue(node->children[i], fila);
            }
        }
        xyy->root = NULL;
    }
    else{
        for(i = 0; i < 3; i++){
            if(node->parent->children[i] == node){
                node->parent->children[i] = NULL;
                break;
            }
        }
        for(i = 0; i < 3; i++){
            if(node->children[i] != NULL){
                if(node->parent->children[i] == NULL){
                    node->parent->children[i] = node->children[i];
                    node->children[i]->parent = node->parent;
                }
                else{
                    enqueue(node->children[i], fila);
                }
            }
        }
    }
    while(!queueIsEmpty(fila)){
        aux = dequeue(fila);
        for(i = 0; i < 3; i++){
            if(aux->children[i] != NULL){
                enqueue(aux->children[i], fila);
            }
        }
        insere(xyy,aux);
    }
    free(node);
    free(fila);
}

void dentroRetangulo(XyyTree t, NoStruct* node, Lista l, double x1, double y1, double x2, double y2, void* (*fun)(void*, void*)){
    if(node == NULL){
        return;
    }
    if(pontoInternoRetangulo(pontoX(node->ponto), pontoY(node->ponto), x1, y1, x2, y2)){
        if(fun != NULL){
            insertFinal(l, fun(t, node));
        }
        else{            
            insertFinal(l, node);
        }
        
    }
    for(int i = 0; i < 3; i++){
        dentroRetangulo(t, node->children[i], l, x1, y1, x2, y2, NULL);
    }
}


void dentroRetanguloInfos(XyyTree t, NoStruct* node, Lista l, double x1, double y1, double x2, double y2, void* (*fun)(void*, void*)){
    if(node == NULL){
        return;
    }
    if(pontoInternoRetangulo(pontoX(node->ponto), pontoY(node->ponto), x1, y1, x2 - x1, y2 - y1)){
        if(fun != NULL){
            insertFinal(l, fun(t, node));
        }
        else{            
            insertFinal(l, node->info);
        }
        
    }
    for(int i = 0; i < 3; i++){
        dentroRetanguloInfos(t, node->children[i], l, x1, y1, x2, y2, NULL);
    }
}

Lista getNodesDentroRegiaoXyyT (XyyTree t, double x1, double y1, double x2, double y2){
    XyyStruct* tree = (XyyStruct*) t;
    NoStruct* node = tree->root;
    Lista l = createList();
    dentroRetangulo(t, node, l, x1, y1, x2, y2, NULL);
    return l;
}

Lista getInfosDentroRegiaoXyyT (XyyTree t, double x1, double y1, double x2, double y2, FdentroDe f){
    XyyStruct* tree = (XyyStruct*) t;
    NoStruct* node = tree->root;
    Lista l = createList();
    f=f;
    dentroRetanguloInfos(t, node, l, x1, y1, x2, y2, NULL);
    return l;
}

void infoAtingidos(XyyTree t, NoStruct* node, Lista l, double x, double y, bool (*fun)(void*, double x, double y)){
    if(node == NULL){
        return;
    }
    Info infoAux = node->info;
    if(fun(infoAux, x, y)){
        insertFinal(l, node->info);
    }
    for(int i = 0; i < 3; i++){
        infoAtingidos(t, node->children[i], l, x, y, fun);
    }
}

Lista getInfosAtingidoPontoXyyT (XyyTree t, double x, double y, FatingidoPor f){
    XyyStruct* tree = (XyyStruct*) t;
    NoStruct* node = tree->root;
    Lista l = createList();
    infoAtingidos(t, node, l, x, y, f);
    return l;
}

void percorreProfundidade(XyyTree t, NoStruct* node, FvisitaNo f, void *aux){
    if(node == NULL){
        return;
    }
    f(getInfoXyyT(t, node), 0, 0, aux);
    for(int i = 0; i < 4; i++){
        percorreProfundidade(t, node->children[i],f, aux);
    }
}

void visitaProfundidadeXyyT (XyyTree t, FvisitaNo f, void *aux){
    XyyStruct* tree = (XyyStruct*) t;
    NoStruct* node = tree->root;
    percorreProfundidade(t, node, f, aux);
}

void visitaLarguraXyyT (XyyTree t, FvisitaNo f, void *aux){
    XyyStruct* tree = (XyyStruct*) t;
    NoStruct* node;
    if(tree->root == NULL){
        return;
    }
    Fila fila = createQueue();
    enqueue(tree->root, fila);
    do{
        node = dequeue(fila);
        for(int i = 0; i < 3; i++){
            if(node->children[i] != NULL){
                enqueue(node->children[i], fila);
            }
        }
        f(getInfoXyyT(tree, node),pontoY(node->ponto), pontoY(node->ponto), aux);
    }while(!queueIsEmpty(fila));
    free(fila);
}
