#ifndef __LERARQUIVOS_H
#define __LERARQUIVOS_H

#include "stdio.h"

// Le o arquivo .geo e chamas as funções que realizam os comandos
void lerGEO(XyyTree arvores[5], char arqGeo[], char said[]);

//le o arquivo .qry e chama as funcoes que realizam os comandos
void lerQRY(XyyTree arvores[5], char *diretorio, char said[]);


#endif
    