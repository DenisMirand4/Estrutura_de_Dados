#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "lista.h"
#include "string.h"
#include "ponto.h"

typedef struct N{
    Info infos;
    struct N *ant;
    struct N *prox;
} no;

typedef struct L
{
    int tamanho;
    no *primeiro;
    no *ultimo;
} list;

Lista createList(){
    list* lista = (list*) malloc(sizeof(list));
    if(lista==NULL){
        printf("Erro ao criar a lista\n");
        exit(1);
    }
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
    return lista;
}

int getLength(Lista lista){
    //list *aux = (list*) lista;
    Posic posic= getFirst(lista);
    int i = 0;
    while (posic != NULL){
        i++;
        posic = getNext(lista, posic);
    }

    return i;
}

void listInsert(Info infos, Lista lista){
    list *listaAux = (list *)lista;
    no *nodeAux;
    no *nodeInsert = (no *)malloc(sizeof(no));
    nodeInsert->infos = infos;
    int tamAux = listaAux->tamanho;

    if (listaAux->primeiro == NULL) {
        listaAux->primeiro = nodeInsert;
        nodeInsert->ant = NULL;
        nodeInsert->prox = NULL;

        listaAux->ultimo = nodeInsert;
        listaAux->tamanho++;
        //return nodeInsert;
    } else {
        nodeAux = listaAux->ultimo;
        nodeAux->prox = nodeInsert;
        nodeInsert->ant = nodeAux;
        nodeInsert->prox = NULL;
        listaAux->ultimo = nodeInsert;
        listaAux->tamanho++;
        //return nodeInsert;
    }
    if (listaAux->tamanho != tamAux) {
        //  printf("Nó adicionado!\n");
    }
}

Posic insertFinal(Lista lista, Info infos){
    list *listaAux = (list *)lista;
    no *nodeAux;
    no *nodeInsert = (no *)malloc(sizeof(no));
    nodeInsert->infos = infos;
    int tamAux = listaAux->tamanho;
    
    if (listaAux->primeiro == NULL) {
        listaAux->primeiro = nodeInsert;
        nodeInsert->ant = NULL;
        nodeInsert->prox = NULL;

        listaAux->ultimo = nodeInsert;
        listaAux->tamanho++;
        return nodeInsert;
    } else {
        nodeAux = listaAux->ultimo;
        nodeAux->prox = nodeInsert;
        nodeInsert->ant = nodeAux;
        nodeInsert->prox = NULL;
        listaAux->ultimo = nodeInsert;
        listaAux->tamanho++;
        return nodeInsert;
    }
    if (listaAux->tamanho != tamAux) {
          //printf("Nó adicionado!\n");
    }
}

Posic insertAfter(Lista lista, Info infos, Posic p){
    list *listaAux = (list *) lista;
    no *nodeAux;
    no *nodeProx;

    //no *nodeAnt = NULL;
    no *nodeInsert = (no *) malloc(sizeof(no));
    nodeInsert->infos = infos;
    nodeAux = p;
    if(nodeAux == listaAux->ultimo){
        nodeAux->prox = nodeInsert;
        listaAux->ultimo = nodeInsert;

        nodeInsert->ant = nodeAux;
        nodeInsert->prox = NULL;
        listaAux->tamanho++;
    } else {
        nodeProx = nodeAux->prox;
        nodeAux->prox = nodeInsert;
        nodeProx->ant = nodeInsert;

        nodeInsert->prox = nodeProx;
        nodeInsert->ant = nodeAux;
        listaAux->tamanho++;

    }

    return nodeInsert;

}

Posic insertBefore(Lista lista, Info infos, Posic p){
    list *listaAux = (list *) lista;
    no *nodeAux;
    //no *nodeProx = NULL;
    no *nodeAnt = NULL;
    no *nodeInsert = (no *) malloc(sizeof(no));

    nodeInsert->infos = infos;
    nodeAux = p;

    if(nodeAux == listaAux->primeiro){
        nodeAux->ant = nodeInsert;
        nodeInsert->prox = nodeAux;
        nodeInsert->ant = NULL;

        listaAux->primeiro = nodeInsert;
        listaAux->tamanho++;
    } else {
        nodeAnt = nodeAux->ant;
        nodeAux->ant = nodeInsert;
        nodeAnt->prox = nodeInsert;

        nodeInsert->prox = nodeAux;
        nodeInsert->ant = nodeAnt;
        listaAux->tamanho++;
    }

    return nodeInsert;

}

int insideList(Lista list, int a){
    Posic rNext;
    rNext = getFirst(list); // pega o primeir No e ta colocando dentro de int
    Info info;
    info = getInfos(rNext);
    while(rNext != NULL){
        if(pontoY(info) == a) // ta comparando um no com int 
            return 1;
        rNext = getNext(list,rNext);
        info = (getInfos(rNext));
    }
    return 0;
}

void printLista(Lista lista){
    list *listaAux = (list*) lista;
    no *node = listaAux->primeiro;
    int i = 0;
    if(listaAux->primeiro == NULL){
        printf("Lista Vazia\n");
        return;
    } else {
        while (node != NULL){
            printf("No %d\n", i);
            node = node->prox;
            i++;
        }
    }
}

void removeNo(Lista lista, Posic position){
    list *listaAuxiliar = (list *)lista;
    no *noAuxiliar = (no *)position;
    no *noAnterior = NULL;
    no *noProximo = NULL;

    if (noAuxiliar == NULL) {
        //printf("ID invalido\n");
        return;
    } else {
        if (noAuxiliar == listaAuxiliar->primeiro) {  //se for o primeiro elemento da lista
            noProximo = noAuxiliar->prox;
            listaAuxiliar->primeiro = noProximo;
            noProximo->ant = NULL;

            free(noAuxiliar);
            
            listaAuxiliar->tamanho--;
        } else if (noAuxiliar == listaAuxiliar->ultimo) {  //se for o último elemento da lista
            noAnterior = noAuxiliar->ant;
            listaAuxiliar->ultimo = noAnterior;
            noAnterior->prox = NULL;

            free(noAuxiliar);
            listaAuxiliar->tamanho--;
        } else {  //se estiver no meio da lista
            noAnterior = noAuxiliar->ant;
            noProximo = noAuxiliar->prox;

            noAnterior->prox = noProximo;
            noProximo->ant = noAnterior;

            free(noAuxiliar);
            listaAuxiliar->tamanho--;
        }

        //printf("Removido da lista com sucesso\n");
        return;
    }
}

Posic getPosic(Lista lista, int i) {
    Posic pos = getFirst(lista);
    int iAuxiliar = 0;
    if(i > getLength(lista) || i < 0)
        return NULL;
    //printf("i = %d e tam = %d \n", i,  getLength(lista));

    while (pos != NULL)
    {
        if(iAuxiliar == i)
            return pos;
        pos = getNext(lista, pos);
        iAuxiliar++;
    }
    return NULL;

}

Posic getFirst(Lista lista) {
    list *lista_aux = (list *)lista;
    if (lista_aux->tamanho == 0) {
        //printf("Não há elementos na lista\n");
        return NULL;
    } else {
        return lista_aux->primeiro;
    }
}

Posic getLast(Lista lista) {
    list *lista_aux = (list *)lista;
    if (lista_aux->tamanho == 0) {
        printf("Não há elementos na lista\n");
        return NULL;
    } else {
        //printf("retornando %p\n", lista_aux->ultimo);
        return lista_aux->ultimo;
    }
}


Info getInfos(Posic p) {
    no *node_auxiliar = (no *) p;
    if (p == NULL) {
        // printf("Erro ao obter infromações do nó especificado\n");
        return NULL;
    } else {
        return node_auxiliar->infos;
    }
}

Posic getNext(Lista lista, Posic p) {
    list *lista_aux = (list *)lista;
    no *nodeAux = (no *)p;
    if (nodeAux == lista_aux->ultimo) {
        return NULL;
    } else {
        return nodeAux->prox;
    }
}

void swap(Posic p1, Posic p2){
    //list *lista_aux = (list *)lista;
    no *nodeAux1 = (no *)p1;
    no *nodeAux2 = (no *)p2;
    Info aux = nodeAux1->infos; 

    nodeAux1->infos = nodeAux2->infos;
    nodeAux2->infos = aux;
        
}

Posic getPrevious(Lista lista, Posic p) {
    list *lista_aux = (list *)lista;
    no *node_aux = (no *)p;
    if (node_aux == lista_aux->primeiro) {
        return NULL;
    } else {
        return node_aux->ant;
    }
}

void freeList(Lista lista){
    list *lista_aux = (list *)lista;
    no *cur = lista_aux->ultimo;
    while (cur != NULL)
    {
        no * prev = cur->ant;
        free(cur);
        cur = prev;
    }
    lista_aux->primeiro = lista_aux->ultimo = NULL;

}
