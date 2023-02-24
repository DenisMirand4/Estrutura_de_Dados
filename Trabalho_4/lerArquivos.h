#ifndef __LERARQUIVOS_H
#define __LERARQUIVOS_H
#include "digraph.h"
#include "stdio.h"

// Le o arquivo .geo e chamas as funções que realizam os comandos
void lerGEO(SRbTree arvore, char arqGeo[], char said[]);

Digraph lerVIA(char *arqVia, Digraph dg);

//le o arquivo .qry e chama as funcoes que realizam os comandos
void lerQRY(SRbTree arvore, char *diretorio, char said[], Digraph dg);


#endif
    