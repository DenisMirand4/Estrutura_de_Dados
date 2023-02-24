#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svg.h"
#include "lista.h"
#include "retangulo.h"
#include "circulo.h"
#include "texto.h"
#include "ponto.h"
#include "linha.h"
#include "srbTree.h"
#include "digraph.h"

#define limites 100000

FILE* iniciarSvg(char arq[]){

    FILE* svg = fopen(arq, "w+");
    if(svg == NULL){
        printf("erro ao abrir o arquivo\n");
        exit(1);
    };
    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"100%%\" height=\"100%%\" viewBox=\"-200 -200 4800 8600\" preserveAspectRatio=\"none\">\n<defs>\n<marker id=\"arrowhead\" markerWidth=\"10\" markerHeight=\"7\" fill=\"white\" refX=\"0\" refY=\"3.5\" orient=\"auto\">\n<polygon points=\"0 0, 10 3.5, 0 7\" />\n</marker>\n</defs>");
    
    return svg;
}

void fecharSvg(FILE* svg){
    fprintf(svg, "</svg>");
    fclose(svg);
}


void desenharSvg(FILE* svg, SRbTree l, Digraph dg){
    printf("PrintarSVG\n");
    NodeTree no;
    Lista aux = createList();
    getBbSRb(l, 0, 0, limites, limites, aux);
    for(no = getFirst(aux); no != NULL; no = getNext(aux, no)){
        if(getInfos(no) != NULL){
            desenharRetangulo(getInfos(no), 0.0, 0.0, svg);
        }
    }
    freeList(aux);

    Lista aux1 = createList();
    Digraph noG;
    getEdges(dg, aux1);
    for(noG = getFirst(aux1); noG != NULL; noG = getNext(aux1, noG)){
        if(getInfos(noG) != NULL){
            desenharLinha(getInfos(noG), 0.0, 0.0, svg);
        }
    }
    freeList(aux1);

    Lista aux2 = createList();
    getNodeNames(dg, aux2);
    for(noG = getFirst(aux2); noG != NULL; noG = getNext(aux2, noG)){
        if(getInfos(noG) != NULL){
            desenharCirculo(getInfos(noG), 0.0, 0.0, svg);
        }
    }


}
