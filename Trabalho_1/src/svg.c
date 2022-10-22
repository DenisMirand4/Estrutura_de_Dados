#include <stdio.h>
#include <stdlib.h>

#include "svg.h"
#include "lista.h"
#include "formasGeometricas.h"


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



void desenharSvg(FILE* svg, Lista l[5]){
    No no;
    printf("PrintarSVG\n");

    void (*desenhar[5])(void*, FILE*) = {desenhar_retangulo, desenhar_circulo ,desenhar_linha, desenhar_texto, desenhar_poligono};    
    for(int i = 0; i < 5; i++){
        for(no = PrimeiroDaLista(l[i]); no != NULL; no = ProximaPosicao(l[i], no)){
            if(ValorPosicao(no) != NULL)
                desenhar[i](ValorPosicao(no), svg);
        }
    }
    printf("Printado.\n");


}

