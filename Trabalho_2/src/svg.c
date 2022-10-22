#include <stdio.h>
#include <stdlib.h>

#include "svg.h"
#include "lista.h"
#include "retangulo.h"
#include "circulo.h"
#include "texto.h"
#include "ponto.h"
#include "linha.h"
#include "xyytree.h"

#define limites 100000

FILE* iniciarSvg(char arq[]){

    FILE* svg = fopen(arq, "w");
    if(svg == NULL){
        printf("erro ao abrir o arquivo\n");
        exit(1);
    };
    fprintf(svg, "<svg>\n");
    
    return svg;
}

void fecharSvg(FILE* svg){
    fprintf(svg, "</svg>");
    fclose(svg);
}


void desenharSvg(FILE* svg, XyyTree l[5]){
    printf("PrintarSVG\n");
    Node no;
    Lista aux;
    void (*desenhar[4])(void*, double, double, FILE*) = {desenharRetangulo, desenharCirculo ,desenharLinha, desenharTexto };
    for(int i = 0; i < 4; i++){
        aux = getInfosDentroRegiaoXyyT(l[i], 0, 0, limites, limites, NULL);
        for(no = getFirst(aux); no != NULL; no = getNext(aux, no)){
            if(getInfos(no) != NULL)
                desenhar[i](getInfos(no), 0.0, 0.0, svg);
        }
        //visitaLarguraXyyT(l[i], (void (*)(void *, double, double, void *))desenhar, svg);
    }


}

