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

#define limites 100000

FILE* iniciarSvg(char arq[]){

    FILE* svg = fopen(arq, "w+");
    if(svg == NULL){
        printf("erro ao abrir o arquivo\n");
        exit(1);
    };
    fprintf(svg, "<svg width=\"100%%\" height=\"100%%\" viewBox=\"0 0 1366 2304\" preserveAspectRatio=\"none\">\n");
    
    return svg;
}

void fecharSvg(FILE* svg){
    fprintf(svg, "</svg>");
    fclose(svg);
}


void desenharSvg(FILE* svg, SRbTree l[4]){
    printf("PrintarSVG\n");
    Node no;
    for(int i = 0; i < 4; i++){
        Lista aux = createList();
        getBbSRb(l[i], 0, 0, limites, limites, aux);
        for(no = getFirst(aux); no != NULL; no = getNext(aux, no)){
            if(getInfos(no) != NULL){
                if(i == 0){
                    desenharRetangulo(getInfos(no), 0.0, 0.0, svg);
                }
                else if(i == 1){
                    desenharCirculo(getInfos(no), 0.0, 0.0, svg);
                }
                else if(i == 2){
                    desenharLinha(getInfos(no), 0.0, 0.0, svg);
                }
                else if(i == 3){
                    desenharTexto(getInfos(no), 0.0, 0.0, svg);
                }
            }
        }
        freeList(aux);
    }
}

void desenharDot(char *dot, SRbTree l[4]){
    printf("PrintarDot\n");
    for(int i = 0; i < 4; i++){
        if(i == 0){
            char figura[] = "Retangulo";
            char* aux = (char*)malloc((strlen(dot)+strlen(figura)+2)*sizeof(char));
            sprintf(aux, "%s-%s", dot, figura);
            printSRb(l[0], aux);
            free(aux);
        }
        else if(i == 1){
            char figura[] = "Circulo";
            char* aux = (char*)malloc((strlen(dot)+strlen(figura)+2)*sizeof(char));
            sprintf(aux, "%s-%s", dot, figura);
            printSRb(l[1], aux);
            free(aux);
        }
        else if(i == 2){
            char figura[] = "Linha";
            char* aux = (char*)malloc((strlen(dot)+strlen(figura)+2)*sizeof(char));
            sprintf(aux, "%s-%s", dot, figura);
            printSRb(l[2], aux);
            free(aux);
        }
        else if(i == 3){
            char figura[] = "Texto";
            char* aux = (char*)malloc((strlen(dot)+strlen(figura)+2)*sizeof(char));
            sprintf(aux, "%s-%s", dot, figura);
            printSRb(l[3], aux);
            free(aux);
        }
    }
    
}