#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "lista.h"
#include "fila.h"
#include "svg.h"
#include "mainAux.h"
#include "formasGeometricas.h"

void leituraQRY(Lista listas[5], char *pathQRY, char pathSaida[]){

    char comando[10], id[20], corb[30], corp[30];
    double x, y, h, w;
    int k;
    Lista selecionados = CriarLista(); //Armazena o id dos selecionados
    char* saidaTXT = malloc((5 + strlen(pathSaida))* sizeof(char));
    char* saidaSVG = malloc((5 + strlen(pathSaida))* sizeof(char));
    sprintf(saidaSVG, "%s.svg", pathSaida);
    sprintf(saidaTXT, "%s.txt", pathSaida);    
    FILE* qry   = fopen(pathQRY, "r");
    FILE* saida = fopen(saidaTXT, "w");
    FILE* svg   = iniciarSvg(saidaSVG);
    Fila filaPoligonos = CriaFila();

    if(saida == NULL || qry == NULL){        
        printf("\nErro ao abrir QRY");
        exit(1);
    }else(printf("QRY Iniciado\n")); 

    while (1){
        fscanf(qry, "%s", comando);
        if(feof(qry)) //fim do arquivo
            break;
        else if(strcmp("inp", comando) == 0){
            fscanf(qry, "%s", id);
            funcao_inp(saida, listas, filaPoligonos, id);
        }
        else if(strcmp("sel", comando) == 0){
            fscanf(qry, "%lf %lf %lf %lf", &x, &y, &w, &h);
            DesalocarLista(selecionados);
            selecionados = CriarLista();
            funcao_sel(saida, listas, selecionados, x, y, w, h);
            fprintf(saida, "Total: %d\n",TamanhoLista(selecionados));
        }
        else if(strcmp("sel+", comando) == 0){
            fscanf(qry, "%lf %lf %lf %lf", &x, &y, &w, &h);
            int aux_total = TamanhoLista(selecionados);
            fprintf(saida, "sel+: Total-antes: %d\n",TamanhoLista(selecionados));
            funcao_sel(saida, listas, selecionados, x, y, w, h);
            fprintf(saida, "sel+: Total adicionado: %d\n",TamanhoLista(selecionados) - aux_total);
        }
        else if(strcmp("rmp", comando) == 0){
            if(FilaVazia(filaPoligonos) != 1){
                ListaPosicao auxInfo = FilaRemove(filaPoligonos); 
                fprintf(saida, "rmp: %lf %lf\n", get_ponto_x(auxInfo), get_ponto_y(auxInfo));
            }
        }
        else if(strcmp("clp", comando) == 0){
            filaPoligonos = CriaFila();
        }
        else if(strcmp("dels", comando) == 0){
            funcao_dels(saida, listas, selecionados); 
            DesalocarLista(selecionados);
            selecionados = CriarLista();
        }
        else if(strcmp("dps", comando) == 0){
            fscanf(qry, "%s %lf %lf %s %s", id, &x, &y, corb, corp);
            k = atoi(id);
            funcao_dps(listas, selecionados, k, x, y, corb, corp);
        }
        else if(strcmp("pol", comando) == 0){
            fscanf(qry, "%s %lf %lf %s %s", id, &x, &y, corb, corp);
            funcao_pol(listas, filaPoligonos, corb, corp);
        }
        else if(strcmp("ups", comando) == 0){
            fscanf(qry, "%s %s %lf %lf %d", corb, corp, &x, &y, &k);
            funcao_ups(listas, selecionados, corb, corp, x, y, k);
        }              
    }

    desenharSvg(svg, listas);
    fecharSvg(svg);
    fclose(saida);
    fclose(qry);
}
