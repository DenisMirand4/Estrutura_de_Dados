#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "mainAux.h"
#include "svg.h"
#include "qry.h"
#include "formasGeometricas.h"

void funcao_inp(FILE *saidaTXT, Lista listas[], Fila filaPoligonos, char *id){
    No no;    
    char* (*ids[4])(void*) = {get_retangulo_id, get_circulo_id ,get_linha_id , get_texto_id};
    Ponto (*pontos[4])(void*) = {get_ponto_retangulo, get_circulo_ponto ,get_linha_ponto , get_texto_anchor_point};
    
    for(int i = 0; i < 4; i++){
        for(no = PrimeiroDaLista(listas[i]); no != NULL; no = ProximaPosicao(listas[i], no)){
            if( strcmp(ids[i](ValorPosicao(no)), id) == 0){
                FilaAdicionar(pontos[i](ValorPosicao(no)), filaPoligonos);
                fprintf(saidaTXT, "inp: %lf %lf\n", get_ponto_x(pontos[i](ValorPosicao(no))), get_ponto_y(pontos[i](ValorPosicao(no))));
                break;
            }
        }
    }
}

void funcao_dels(FILE *saidaTXT, Lista listas[], Lista selecionados){
    No no, no_aux;
    ListaPosicao aux;
    int tam = 0;
    int listaTam = TamanhoLista(selecionados);
    for(no_aux = PrimeiroDaLista(selecionados); no_aux != NULL; no_aux = ProximaPosicao(selecionados, no_aux), tam++){
        if(tam == listaTam)
            break;

        char id_aux[50];

        strcpy(id_aux, get_retangulo_id(ValorPosicao(no_aux)));
        no = getInsideList(listas[RETANGULO], id_aux, RETANGULO);
        if(no != NULL){
            aux = ValorPosicao(no);
            fprintf(saidaTXT, "dels: id = %s x = %lf y = %lf w = %lf h = %lf\n", get_retangulo_id(aux), get_retangulo_x(aux), get_retangulo_y(aux), get_retangulo_width(aux), get_retangulo_height(aux));
            RemoveNoLista(listas[RETANGULO], no);
            continue;
        }
        no = getInsideList(listas[CIRCULO], id_aux, CIRCULO);
        if(no != NULL){
            aux = ValorPosicao(no);
            fprintf(saidaTXT, "dels: id = %s x = %lf y = %lf r = %lf\n", get_circulo_id(aux), get_circulo_x(aux), get_circulo_y(aux), get_circulo_raio(aux));
            RemoveNoLista(listas[CIRCULO], no);
            continue;
        }
        no = getInsideList(listas[LINHA], id_aux, LINHA);
        if(no != NULL){
            aux = ValorPosicao(no);
            fprintf(saidaTXT, "dels: id = %s x1 = %lf y1 = %lf x2 = %lf y2 = %lf\n", get_linha_id(aux), get_linha_x1(aux), get_linha_y1(aux), get_linha_x2(aux), get_linha_y2(aux));
            no = getInsideList(listas[LINHA], id_aux, LINHA);
            RemoveNoLista(listas[LINHA], no);
            continue;
        }
        no = getInsideList(listas[TEXTO], id_aux, TEXTO);
        if(no != NULL){
            aux = ValorPosicao(no);
            fprintf(saidaTXT, "dels: id = %s x = %lf y = %lf Texto = \" %s \"\n", get_texto_id(aux), get_texto_x(aux), get_texto_y(aux), get_texto_text(aux));
            RemoveNoLista(listas[TEXTO], no);
            continue;
        }
    }
            
        
}

void funcao_sel(FILE *saidaTXT, Lista listas[], Lista selecionados, double x, double y, double w, double h){
    No no;
    ListaPosicao aux;

    InserirFinalLista(listas[RETANGULO], cria_retangulo("-1", "red", "none", w, h, x,y));
    for(int i = 0; i < 4; i++){
            int tamanho = TamanhoLista(listas[i]);
            for(no = PrimeiroDaLista(listas[i]); no != NULL; no = ProximaPosicao(listas[i], no)){
                aux = ValorPosicao(no);
                if(tamanho == 0)
                    break;
                if(i == 0){
                    if(strcmp(get_retangulo_id(aux), "-1") != 0 && x < get_retangulo_x(aux) && (x + w) > (get_retangulo_x(aux) + get_retangulo_width(aux))  
                        && y < get_retangulo_y(aux) && (y+h) > (get_retangulo_y(aux) + get_retangulo_height(aux)))
                    {
                        InserirFinalLista(listas[CIRCULO], criar_circulo("-1","red","none", 3.0, get_retangulo_x(aux), get_retangulo_y(aux)));
                        InserirFinalLista(selecionados, cria_retangulo(get_retangulo_id(aux), "0", "0", 0, 0 ,0,0));
                        fprintf(saidaTXT, "\tRetangulo id = %s \n", get_retangulo_id(aux));
                    } 
                }
                else if (i==1){
                    if(strcmp(get_circulo_id(aux), "-1") != 0 && x < (get_circulo_x(aux) - get_circulo_raio(aux)) && (x+w) > get_circulo_x(aux) + get_circulo_raio(aux) 
                        && y < get_circulo_y(aux) - get_circulo_raio(aux) && (y+h) > get_circulo_y(aux) + get_circulo_raio(aux))
                    {
                        InserirFinalLista(listas[CIRCULO], criar_circulo("-1","red","none", 3.0, get_circulo_x(aux), get_circulo_y(aux)));
                        InserirFinalLista(selecionados, cria_retangulo(get_circulo_id(aux), "0", "0", 0, 0 ,0,0));
                        fprintf(saidaTXT, "\tCirculo id = %s \n", get_circulo_id(aux));
                        }
                }
                else if (i==2){
                    if(x < get_linha_menor_X(aux) && x+w > get_linhe_maior_x(aux) && 
                        y < get_linha_menor_y(aux) && y+h > get_linha_maior_y(aux)){
                            InserirFinalLista(listas[CIRCULO], criar_circulo("-1","red","none", 3.0, get_ponto_x(get_linha_ponto(aux)), get_ponto_y(get_linha_ponto(aux))));
                            InserirFinalLista(selecionados, cria_retangulo(get_linha_id(aux), "0", "0", 0, 0 ,0,0));
                            
                            fprintf(saidaTXT, "\tLinha id = %s \n", get_linha_id(aux));
                        }
                }
                else if (i==3){
                    float xAux, yAux;
                    int tamaho = strlen(get_texto_text(aux));
                    if(get_texto_ap(aux) == 'i'){
                        xAux = get_texto_x(aux);
                        yAux = get_texto_y(aux);
                    } else if(get_texto_ap(aux) == 'm'){
                        xAux =  get_texto_x(aux) - (tamaho/2);  
                        yAux =  get_texto_y(aux) - (tamaho/2);  
                    } else {
                        xAux =  get_texto_x(aux) - (tamaho) * 2;  
                        yAux =  get_texto_y(aux) - (tamaho) * 2 ;  
                    }
                    if( x < xAux && x+w > xAux + tamaho && y < yAux && y+h > (yAux + tamaho) ){
                        InserirFinalLista(listas[CIRCULO], criar_circulo("-1","red","none", 3.0, get_texto_x(aux), get_texto_y(aux)));
                        InserirFinalLista(selecionados, cria_retangulo(get_texto_id(aux), "0", "0", 0, 0 ,0,0));
                        fprintf(saidaTXT, "\tTexto id = %s \n", get_texto_id(aux));
                    }
                }
                tamanho--;            
            }
        }
}

void funcao_dps(Lista listas[],Lista selecionados, int id, double x, double y, char *corb, char *corp){
    No no, no_aux;
    ListaPosicao infoAux;
    char idAux[50];

    for(no = PrimeiroDaLista(selecionados); no != NULL; no = ProximaPosicao(selecionados, no)){

        strcpy(idAux, get_retangulo_id(ValorPosicao(no)));//salva id
        //compara as formas
        no_aux = getInsideList(listas[RETANGULO], idAux, RETANGULO);
        if(no_aux != NULL){
            infoAux = ValorPosicao(no_aux);
            sprintf(idAux, "%d", id);
            InserirFinalLista(listas[RETANGULO], cria_retangulo(idAux, corb, corp, get_retangulo_width(infoAux), get_retangulo_height(infoAux), get_retangulo_x(infoAux) + x, get_retangulo_y(infoAux) + y));
            continue;
        }
        no_aux = getInsideList(listas[CIRCULO], idAux, CIRCULO);
        if(no_aux != NULL){
            infoAux = ValorPosicao(no_aux);
            sprintf(idAux, "%d", id);
            InserirFinalLista(listas[CIRCULO], criar_circulo(idAux, corb, corp, get_circulo_raio(infoAux), get_circulo_x(infoAux) + x, get_circulo_y(infoAux) + y));
            continue;
        }
        no_aux = getInsideList(listas[LINHA], idAux, LINHA);
        if(no_aux != NULL){
            infoAux = ValorPosicao(no_aux);
            sprintf(idAux, "%d", id);
            InserirFinalLista(listas[LINHA], cria_linha(idAux, corp, get_linha_x1(infoAux) + x, get_linha_y1(infoAux) + y, get_linha_x2(infoAux) + x, get_linha_y2(infoAux) + y ));
            continue;
        }
        no_aux = getInsideList(listas[TEXTO], idAux, TEXTO);
        if(no_aux != NULL){
            infoAux = ValorPosicao(no_aux);
            sprintf(idAux, "%d", id);
            InserirFinalLista(listas[TEXTO], cria_texto(idAux, corb, corp, get_texto_text(infoAux), get_texto_x(infoAux) + x, get_texto_y(infoAux) + y, get_texto_ap(infoAux)));
            continue;
        }
        id++;                
    }
}

void funcao_pol(Lista listas[], Fila filaPoligonos,  char *corb, char *corp){
    ListaPosicao infoAux;
    Fila aux_fila = CriaFila();

    if(FilaVazia(filaPoligonos))
        return;
    
    infoAux = FilaRemove(filaPoligonos);
    Lista pontos = CriarLista();
    while (FilaVazia(filaPoligonos) != 1)
    {
        InserirFinalLista(pontos, infoAux);
        infoAux = FilaRemove(filaPoligonos);
        FilaAdicionar(infoAux, aux_fila);
    }
    if(infoAux != NULL)
        InserirFinalLista(pontos, infoAux);
    do
    {
        FilaAdicionar(FilaRemove(aux_fila), filaPoligonos);
    } while (FilaVazia(aux_fila) != 1);
    
    
    Poligono p = cria_poligono(pontos, corb, TamanhoLista(listas[POLIGONO]), corp);
    InserirFinalLista(listas[POLIGONO], p);

}

void funcao_ups(Lista listas[], Lista selecionados, char *corb, char *corp, float x, float y, int n){
    No no, no_aux;
    ListaPosicao infoAux;
    char idAux[50];
    int cont = 1;
    if(n > 0){
        for(no = PrimeiroDaLista(selecionados); no != NULL; no = ProximaPosicao(selecionados, no), cont++, n--){
            if(n == 0)
                break;
            strcpy(idAux, get_retangulo_id(ValorPosicao(no))); // pega ID do selecionado

            no_aux = getInsideList(listas[RETANGULO], idAux, RETANGULO);
            if(no_aux != NULL){
                infoAux = ValorPosicao(no_aux);
                set_retangulo_x(infoAux, get_retangulo_x(infoAux) + x);                
                set_retangulo_y(infoAux, get_retangulo_y(infoAux) + cont * y);                
                set_retangulo_corp(infoAux, corp);
                set_retangulo_corb(infoAux, corb);
                continue;
            }
            no_aux = getInsideList(listas[CIRCULO], idAux, CIRCULO);
            if(no_aux != NULL){
                infoAux = ValorPosicao(no_aux);
                set_circulo_x(infoAux, get_circulo_x(infoAux) + x);                
                set_circulo_y(infoAux, get_circulo_y(infoAux) + cont * y);                
                set_circulo_corp(infoAux, corp);
                set_circulo_corb(infoAux, corb);
                continue;
            }
            no_aux = getInsideList(listas[LINHA], idAux, LINHA);
            if(no_aux != NULL){
                infoAux = ValorPosicao(no_aux);
                set_linha_x1(infoAux, get_linha_x1(infoAux) + x);                
                set_linha_x2(infoAux, get_linha_x2(infoAux) + x);                
                set_linha_y1(infoAux, get_linha_y1(infoAux) + cont * y);                
                set_linha_y2(infoAux, get_linha_y2(infoAux) + cont * y);                
                continue;
            }
            no_aux = getInsideList(listas[TEXTO], idAux, TEXTO);
            if(no_aux != NULL){
                infoAux = ValorPosicao(no_aux);
                set_texto_x(infoAux, get_texto_x(infoAux) + x);                
                set_texto_y(infoAux, get_texto_y(infoAux) + cont * y);                
                set_texto_corp(infoAux, corp);
                set_texto_corb(infoAux, corb);
                continue;
            }
        }
    }
    else{
        for(no = UltimoDaLista(selecionados); no != NULL; no = PosicaoAnterior(selecionados, no), n++, cont++){
            if(n == 0)
                break;
            strcpy(idAux, get_retangulo_id(ValorPosicao(no))); // pega ID do selecionado
            
            no_aux = getInsideList(listas[RETANGULO], idAux, RETANGULO);
            if(no_aux != NULL){
                infoAux = ValorPosicao(no_aux);
                set_retangulo_x(infoAux, get_retangulo_x(infoAux) + x);                
                set_retangulo_y(infoAux, get_retangulo_y(infoAux) + cont * y);                
                set_retangulo_corp(infoAux, corp);
                set_retangulo_corb(infoAux, corb);
                continue;
            }
            no_aux = getInsideList(listas[CIRCULO], idAux, CIRCULO);
            if(no_aux != NULL){
                infoAux = ValorPosicao(no_aux);
                set_circulo_x(infoAux, get_circulo_x(infoAux) + x);                
                set_circulo_y(infoAux, get_circulo_y(infoAux) + cont * y);                
                set_circulo_corp(infoAux, corp);
                set_circulo_corb(infoAux, corb);
                continue;
            }
            no_aux = getInsideList(listas[LINHA], idAux, LINHA);
            if(no_aux != NULL){
                infoAux = ValorPosicao(no_aux);
                set_linha_x1(infoAux, get_linha_x1(infoAux) + x);                
                set_linha_x2(infoAux, get_linha_x2(infoAux) + x);                
                set_linha_y1(infoAux, get_linha_y1(infoAux) + cont * y);                
                set_linha_y2(infoAux, get_linha_y2(infoAux) + cont * y);                
                continue;
            }
            no_aux = getInsideList(listas[TEXTO], idAux, TEXTO);
            if(no_aux != NULL){
                infoAux = ValorPosicao(no_aux);
                set_texto_x(infoAux, get_texto_x(infoAux) + x);                
                set_texto_y(infoAux, get_texto_y(infoAux) + cont * y);                
                set_texto_corp(infoAux, corp);
                set_texto_corb(infoAux, corb);
                continue;
            }
        }
    }
}