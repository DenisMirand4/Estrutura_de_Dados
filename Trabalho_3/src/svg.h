#ifndef __SVG_H
#define __SVG_H

#include "srbTree.h"
#include "stdio.h"

/*
*Abre o aqruivo .svg e inicia
*Requer o nome do arquivo
*Retorna o arquivo
*/

FILE* iniciarSvg(char arq[]);
/*
*Finaliza o .svg
*Requer o file
*Retorna nada
*/
void fecharSvg(FILE* svg);
/*
*Função que manda desenhar as formas no svg
*Requer o svg a quadtree e a lista das formas e a lista com os pontos do poligono
*Retorna nada
*/
void desenharSvg(FILE* svg, SRbTree l[4]);
/*
*Função responsável por desenhar o caminho do algoritmo de dijkstra e de prim
*Requer a cor do caminho o .svg e a lista com os pontos a desenhar
*Retorna nada
*/

void desenharDot(char *dot, SRbTree l[4]);

#endif