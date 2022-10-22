#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "formasGeometricas.h"
#include "lista.h"
#include "math.h"
#define MAX 1000

////////////////////CIRCULO//////////////////////

typedef struct circulo {
    double r, x, y;
    char id[20], corp[20], corB[20];
} ItemC;

Circulo criar_circulo(char id[20], char corB[20], char corp[20], double raio, double x, double y){
    ItemC *c;
    c = (ItemC *)calloc(1, sizeof(ItemC));
    strcpy(c->id, id);
    strcpy(c->corp, corp);
    strcpy(c->corB, corB);
    c->x = x;
    c->y = y;
    c->r = raio;
    return c;
}

double get_circulo_x(Circulo c){
    ItemC *cir = (ItemC*)c;
    return cir->x;
}

double get_circulo_y(Circulo c){
    ItemC *cir = (ItemC*)c;
    return cir->y;
}

double get_circulo_raio(Circulo c){
    ItemC *cir = (ItemC*)c;
    return cir->r;
}

char *get_circulo_id(Circulo c){
    ItemC *cir = (ItemC*)c;
    return cir->id;
}

void set_circulo_x(Circulo c, double x){
    ItemC *cir = (ItemC*)c;
    cir->x = x;
}

void set_circulo_y(Circulo c, double y){
    ItemC *cir = (ItemC*)c;
    cir->y = y;
}

void set_circulo_corp(Circulo c, char corp[]){
    ItemC *cir = (ItemC*)c;
    strcpy(cir->corp,corp);
}

void set_circulo_corb(Circulo c, char corB[]){
    ItemC *cir = (ItemC*)c;
    strcpy(cir->corB,corB);
}


Ponto get_circulo_ponto(Circulo c){
    ItemC *cir = (ItemC*)c;
    Ponto ponto = criar_ponto(cir->x, cir->y);
    return ponto;
}

void desenhar_circulo(Circulo c, FILE* svg){
    ItemC *cir = (ItemC*)c;

    fprintf(svg,"\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\"/>", cir->x, cir->y, cir->r, cir->corB, cir->corp);
}

////////////LINHA////////////////

typedef struct linha
{
    char id[20], corp[20];
    double x1, y1, x2, y2;
}NoLinha;

Linha cria_linha(char id[20], char corp[20], double x1, double y1, double x2, double y2)
{
    NoLinha *re;
    re = (NoLinha*) calloc(1, sizeof(NoLinha));
    strcpy(re->id, id);
    strcpy(re->corp, corp);
    re->x1 = x1;
    re->x2 = x2;
    re->y1 = y1;    
    re->y2 = y2;

    return re;
}

char *get_linha_id(Linha r){
    NoLinha *re = (NoLinha*)r;
    return re->id;
}

double get_linha_x1(Linha r){
    NoLinha *re = (NoLinha*)r;
    return re->x1;
}

double get_linha_y1(Linha r){
    NoLinha *re = (NoLinha*)r;
    return re->y1;
}

double get_linha_x2(Linha r){
    NoLinha *re = (NoLinha*)r;
    return re->x2;
}

double get_linha_y2(Linha r){
    NoLinha *re = (NoLinha*)r;
    return re->y2;
}

double get_linha_menor_X(Linha r){
    NoLinha *re = (NoLinha*)r;
    if(re->x1 < re->x2)
        return re->x1;
    return re->x2;
}
double get_linha_menor_y(Linha r){
    NoLinha *re = (NoLinha*)r;
    if(re->y1 < re->y2)
        return re->y1;
    return re->y2;
}

double get_linha_maior_y(Linha r){
    NoLinha *re = (NoLinha*)r;
    if(re->y1 < re->y2)
        return re->y2;
    return re->y1;
}
double get_linhe_maior_x(Linha r){
    NoLinha *re = (NoLinha*)r;
    if(re->x1 < re->x2)
        return re->x2;
    return re->x1;
}

void set_linha_x1(Linha r, float valor){
    NoLinha *re = (NoLinha*)r;
    re->x1 = valor;

}
void set_linha_x2(Linha r, float valor){
    NoLinha *re = (NoLinha*)r;
    re->x2 = valor;

}
void set_linha_y1(Linha r, float valor){
    NoLinha *re = (NoLinha*)r;
    re->y1 = valor;

}
void set_linha_y2(Linha r, float valor){
    NoLinha *re = (NoLinha*)r;
    re->y2 = valor;

}

Ponto get_linha_ponto(Linha r){
    NoLinha *re = (NoLinha*)r;
    int x, y;
    if(re->x1 == re->x2){
        if(re->y1 <= re->y2){
            x = re->x1;
            y = re->y1;
        }
        else {
            x = re->x2;
            y = re->y2;
        }
    }
    else if(re->x1 < re->x2){
        x = re->x1;
        y = re->y1;
    } else {
        x = re->x2;
        y = re->y2;
    }
    return criar_ponto(x, y);
}

void desenhar_linha(Linha r, FILE* svg){
    NoLinha *ret = (NoLinha*)r;
    fprintf(svg,"\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\"  stroke=\"%s\" style=\"stroke-width:2\" />\n",ret->x1, ret->y1, ret->x2, ret->y2,ret->corp);
}

///////////POLIGONO//////////////

typedef struct pol {
    Lista pontos; 
    char cor[30];
    char corp[30];
    int id;
} Polig;

Poligono cria_poligono(Lista pontos, char cor[], int id, char corp[]){
    Polig *p;
    p = (Polig *)calloc(1, sizeof(Polig));
    p->pontos = pontos;
    strcpy(p->cor, cor);
    strcpy(p->corp, corp);
    p->id = id;
    return p;
}

void desenhar_poligono(Poligono c, FILE* svg){
    Polig *p = (Polig*) c; 
    ListaPosicao info;
    No no;
    Lista casos =  p->pontos;
    char cor[30];
    strcpy(cor, p->cor);
    fprintf(svg, "<defs>\n");
    fprintf(svg, "\t<pattern id=\"%d\" patternUnits=\"userSpaceOnUse\" width=\"16\" height=\"16\" patternTransform=\"rotate(90)\"> \n", p->id);
    fprintf(svg, "\t\t<line x1=\"0\" y=\"0\" x2=\"0\" y2=\"16\" stroke=\"%s\" stroke-width=\"7\" /> \n", p->corp);
    fprintf(svg, "\t</pattern>\n");
    fprintf(svg, "</defs>");

    fprintf(svg,"\t<polygon fill=\"url(#%d)\" fill-opacity=\"0.7\" stroke=\"%s\" stroke-width=\"5px\" points=\" ",p->id, cor);
    for(no = PrimeiroDaLista(casos); no != NULL; no = ProximaPosicao(casos,no)){
        info = ValorPosicao(no);
        if(ProximaPosicao(casos, no) == NULL)
            fprintf(svg," %lf,%lf",get_ponto_x(info),get_ponto_y(info));
        else
            fprintf(svg," %lf,%lf,",get_ponto_x(info),get_ponto_y(info));
    }
    fprintf(svg," \"/>\n");
}

////////////////////////PONTO//////////////////////

typedef struct PONTO {
    double x, y; 
} ponto;

Ponto criar_ponto(double x, double y){
    ponto *p;
    p = (ponto *)calloc(1, sizeof(ponto));
    p->x = x;
    p->y = y;
    return p;
}

double get_ponto_x(Ponto p){
    ponto *tp = (ponto*) p;
    return tp->x;
}

double get_ponto_y(Ponto p){
    ponto *tp = (ponto*) p;
    return tp->y;
}

void desenhar_ponto(Ponto pont, FILE* svg) {
    ponto* p = (ponto*) pont;
    fprintf(svg,"\t<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"black\" />\n", p->x, p->y);
}

//////////////////////////RETANGULO/////////////////////////////

typedef struct retangulo
{
    char id[20], corp[20], corb[20];
    double x, y, w, h;
}NoRet;

Retangulo cria_retangulo(char id[20], char corb[20], char corp[20], double w, double h, double x, double y)
{
    NoRet *retangulo;
    retangulo = (NoRet*) calloc(1, sizeof(NoRet));
    strcpy(retangulo->id, id);
    strcpy(retangulo->corp, corp);
    strcpy(retangulo->corb, corb);
    retangulo->w = w;
    retangulo->h = h;
    retangulo->x = x;
    retangulo->y = y;

    return retangulo;
}

double get_retangulo_x(Retangulo r){
    NoRet *retangulo = (NoRet*)r;
    return retangulo->x;
}

double get_retangulo_y(Retangulo r){
    NoRet *retangulo = (NoRet*)r;
    return retangulo->y;
}

double get_retangulo_width(Retangulo r){
    NoRet *retangulo = (NoRet*)r;
    return retangulo->w;
}

double get_retangulo_height(Retangulo r){
    NoRet *retangulo = (NoRet*)r;
    return retangulo->h;
}

char *get_retangulo_id(Retangulo r){
    NoRet *retangulo = (NoRet*)r;
    return retangulo->id;
}


void set_retangulo_x(Retangulo r, double x){
    NoRet *retangulo = (NoRet*)r;
    retangulo->x = x;
}

void set_retangulo_y(Retangulo r, double y){
    NoRet *retangulo = (NoRet*)r;
    retangulo->y = y;
}

void set_retangulo_corp(Retangulo r, char corp[]){
    NoRet *retangulo = (NoRet*)r;
    strcpy(retangulo->corp,corp);
}

void set_retangulo_corb(Retangulo r, char corb[]){
    NoRet *retangulo = (NoRet*)r;
    strcpy(retangulo->corb,corb);
}

Ponto get_ponto_retangulo(Retangulo p){
    NoRet *hi = (NoRet*)p;
    Ponto ponto = criar_ponto(hi->x, hi->y);
    return ponto;
}

void desenhar_retangulo(Retangulo r, FILE* svg){
    NoRet *retangulo = (NoRet*)r;
    fprintf(svg,"\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" />\n",retangulo->x, retangulo->y, retangulo->w, retangulo->h,retangulo->corp,retangulo->corb);
}

///////////////////////TEXTO////////////////////////////

typedef struct texto {
    double x, y;
    char id[20], corp[20], corB[20], txto[MAX], anchorPoint;
} ItemT;

Texto cria_texto(char id[20], char corB[20], char corp[20], char txto[], double x, double y, char anchorPoint){
    ItemT *t;
    t = (ItemT *)calloc(1, sizeof(ItemT));
    strcpy(t->id,id);
    strcpy(t->txto,txto);
    strcpy(t->corB,corB);
    strcpy(t->corp,corp);
    t->x = x;
    t->y = y;
    t->anchorPoint = anchorPoint;    

    return t;
}

double get_texto_x(Texto t){
    ItemT *te = (ItemT*)t;
    return te->x;
}

double get_texto_y(Texto t){
    ItemT *te = (ItemT*)t;
    return te->y;
}

char *get_texto_id(Texto t){
    ItemT *te = (ItemT*)t;
    return te->id;
}

char *get_texto_text(Texto t){
    ItemT *te = (ItemT*)t;
    return te->txto;
}

char get_texto_ap(Texto t){
    ItemT *hi = (ItemT*)t;
    return hi->anchorPoint;
}

Ponto get_texto_anchor_point(Texto t){
    ItemT *hi = (ItemT*)t;
    int tam;
    Ponto ponto; 
    if(hi->anchorPoint == 'i')
        ponto = criar_ponto(hi->x, hi->y);
    else if(hi->anchorPoint == 'm'){ // (numeroDeLetras/2) * 10px
        tam = strlen(hi->txto);
        tam = hi->x + (tam/2) * 10;
        ponto = criar_ponto(tam, hi->y);
    } else {
        tam = strlen(hi->txto);
        tam = hi->x + tam * 10;
        ponto = criar_ponto(tam, hi->y);
    }

    return ponto; 
}

void set_texto_x(Texto t, double x){
    ItemT *te = (ItemT*)t;
    te->x = x;
}

void set_texto_y(Texto t, double y){
    ItemT *te = (ItemT*)t;
    te->y = y;
}

void set_texto_corp(Texto t, char corp[]){
    ItemT *te = (ItemT*)t;
    strcpy(te->corp,corp);
}

void set_texto_corb(Texto t, char corB[]){
    ItemT *te = (ItemT*)t;
    strcpy(te->corB,corB);
}

void desenhar_texto(Texto t, FILE* svg){
    ItemT *te = (ItemT*)t;
    fprintf(svg, "\n\t<text x=\"%f\" y=\"%f\" fill=\"%s\" stroke=\"%s\">%s</text>", te->x, te->y, te->corp, te->corB,te->txto);
}