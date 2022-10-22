#ifndef __LERARQUIVOS_H
#define __LERARQUIVOS_H

#include "stdio.h"

// Le o arquivo .geo e chamas as funções que realizam os comandos
void lerGEO(SRbTree arvores[4], char arqGeo[], char said[], SRbTree arvoresDot[4]);

//le o arquivo .qry e chama as funcoes que realizam os comandos
void lerQRY(SRbTree arvores[4], char *diretorio, char said[]);


#endif
    