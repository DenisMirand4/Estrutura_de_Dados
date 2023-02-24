#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "srbTree.h"
#include "ponto.h"
#include "extras.h"
#include "lista.h"
#include "fila.h"
#include "retangulo.h"

enum nodeColor
{
    RED,
    BLACK
};

typedef struct node
{
    struct node *right;
    struct node *left;
    struct node *parent;
    Ponto ponto;
    Info info;
    int cor, id;
    double mbbX1, mbbY1, mbbX2, mbbY2, energia;
} NoStruct;

typedef struct SRbTree
{
    NoStruct *root;
    NoStruct *nil;
    double epsilon;
} SrbStruct;

/* Funçoes auxiliares */

void liberaArvore_aux(SrbStruct *t, NoStruct *node)
{
    if (node->left != t->nil){
        liberaArvore_aux(t, node->left);
    }
    if (node->right != t->nil){
        liberaArvore_aux(t, node->right);
    }
    free(node->info);
    free(node->ponto);
    free(node);
}

void adicionaNull(FILE *pFile, int *count, int id)
{
    fprintf(pFile,"\tnull%d [shape=box,label=\"null\",fontcolor=white,fillcolor=black,style=\"rounded,filled\"];\n",*count);
    fprintf(pFile, "\t%d -> null%d;\n", id, *count);
    *count = *count + 1;
}

void add_node_color(NoStruct *pNode, FILE *pFile, int id)
{
    if (pNode->cor == BLACK)
    {
        fprintf(pFile,
                "\t%d [fontcolor=white,fillcolor=black,style=filled] [label = \"x:%lf\ny:%lf\"];\n", id, pontoX(pNode->ponto), pontoY(pNode->ponto));
    }
    else
    {
        fprintf(pFile,
                "\t%d [fontcolor=white,fillcolor=red,style=filled] [label = \"x:%lf\ny:%lf\"];\n", id, pontoX(pNode->ponto), pontoY(pNode->ponto));
    }
}

void adicionaFilho(SrbStruct *t, NoStruct *node, FILE *pFile, int *count, int has_null, int id)
{
    add_node_color(node, pFile, id);
    if (node->left != t->nil){
        fprintf(pFile, "\t%d -> %d;\n", id, id * 2);
        adicionaFilho(t, node->left, pFile, count, has_null, id * 2);
    }else{
        if (has_null == 1){
            adicionaNull(pFile, count, id);
        }
    }
    if (node->right != t->nil){
        fprintf(pFile, "\t%d -> %d;\n", id, id * 2 + 1);
        adicionaFilho(t, node->right, pFile, count, has_null, id * 2 + 1);
    }else{
        if (has_null == 1){
            adicionaNull(pFile, count, id);
        }
    }
}

int RBT_export_dot(SrbStruct *pRBT, char *filename, int has_null)
{
    char extension[] = ".dot";
    int filename_length = strlen(filename);
    int extension_length = strlen(extension);

    char *new_filename = malloc(
        sizeof(char) * (filename_length + extension_length + 2));
    strcpy(new_filename, filename);
    strcat(new_filename, extension);

    FILE *pFile = fopen(new_filename, "w+");
    if (pFile == NULL)
    {
        fprintf(stderr, "File couldn't be opened!\n");
        return -1;
    }

    // Start of the file
    fprintf(pFile, "digraph RBTree {\n");
    fprintf(pFile, "\tnode [shape=circle,fontname=\"Arial\"];\n");
    fprintf(pFile, "\tedge [arrowhead=none];\n");
    if (pRBT->root != pRBT->nil)
    {
        int count = 0;
        // pRBT->root->id=1;
        adicionaFilho(pRBT, pRBT->root, pFile, &count, has_null, 1);
    }
    fprintf(pFile, "}\n");
    fclose(pFile);

    free(new_filename);

    return 0;
}

bool chaveMaiorOuIgual(SrbStruct *t, NoStruct *ch1, NoStruct *ch2)
{
    bool igualX = false;
    bool igualY = false;
    if(ch1 == t->nil || ch2 == t->nil){
        return false;
    }
    if(modulo(pontoX(ch1->ponto) - pontoX(ch2->ponto)) <= t->epsilon){
        igualX = true;
    }
    if(modulo(pontoY(ch1->ponto) - pontoY(ch2->ponto)) <= t->epsilon){
        igualY = true;
    }
    if(igualX && igualY){
        return true;
    }
    if(igualX == false){
        if(pontoX(ch1->ponto) > pontoX(ch2->ponto)){
            return true;
        }
        return false;
    }
    if(igualX == true && igualY == false){
        if(pontoY(ch1->ponto) > pontoY(ch2->ponto)){
            return true;
        }
        return false;
    }
    return false;    
}

void leftRotate(SrbStruct *t, NoStruct *n)
{
    NoStruct *y = n->right;
    n->right = y->left;
    if (y->left != t->nil){
        y->left->parent = n;
    }
    y->parent = n->parent;
    if (n->parent == t->nil){
        t->root = y;
    }else if (n == n->parent->left){
        n->parent->left = y;
    }else{
        n->parent->right = y;
    }
    y->left = n;
    n->parent = y;
    return;
}

void rightRotate(SrbStruct *t, NoStruct *n)
{
    NoStruct *y = n->left;
    n->left = y->right;
    if (y->right != t->nil){
        y->right->parent = n;
    }
    y->parent = n->parent;
    if (n->parent == t->nil){
        t->root = y;
    }
    else if (n == n->parent->right){
        n->parent->right = y;
    }else{
        n->parent->left = y;
    }
    y->right = n;
    n->parent = y;
    return;
}

void insertion_fixup(SrbStruct *t, NoStruct *z)
{
    while (z->parent->cor == RED){
        if (z->parent == z->parent->parent->left){
            NoStruct *y = z->parent->parent->right;
            if (y->cor == RED){
                z->parent->cor = BLACK;
                y->cor = BLACK;
                z->parent->parent->cor = RED;
                z = z->parent->parent;
            }else{
                if (z == z->parent->right){
                    z = z->parent;
                    leftRotate(t, z);
                }
                z->parent->cor = BLACK;
                z->parent->parent->cor = RED;
                rightRotate(t, z->parent->parent);
            }
        } else{
            NoStruct *y = z->parent->parent->left;
            if(y->cor == RED){
                z->parent->cor = BLACK;
                y->cor = BLACK;
                z->parent->parent->cor = RED;
                z = z->parent->parent;
            }else{
                if(z == z->parent->left){
                    z = z->parent;
                    rightRotate(t, z);
                }
                z->parent->cor = BLACK;
                z->parent->parent->cor = RED;
                leftRotate(t, z->parent->parent);
            }
        }
    }
    t->root->cor = BLACK;
}

void insert(SrbStruct *t, NoStruct *node)
{
    if(node == NULL){
        return;
    }
    NoStruct *y = t->nil;
    NoStruct *temp = t->root;
    while (temp != t->nil){
        y = temp;
        if (chaveMaiorOuIgual(t, node, temp)){
            // printf("\nMAIOR-node:%lf  temp: %lf\n", pontoX(node->ponto),pontoX(temp->ponto));
            temp = temp->right;
        }else{
            // printf("\nMENOR-node:%lf  temp: %lf\n", pontoX(node->ponto),  pontoX(temp->ponto));
            temp = temp->left;
        }
    }
    node->parent = y;
    if (y == t->nil){
        t->root = node;
    }else if (chaveMaiorOuIgual(t, node, y)){
        y->right = node;
    }else{
        y->left = node;
    }
    node->right = t->nil;
    node->left = t->nil;
}

void imprimirArvore(SrbStruct *t, NoStruct *node)
{
    if(node == NULL){
        return;
    }
    if(node->left != t->nil){
        imprimirArvore(t, node->left);
    }
    printf("x: %lf y: %lf cor: %d\n", pontoX(node->ponto), pontoY(node->ponto), node->cor);
    if(node->right != t->nil){
        imprimirArvore(t, node->right);
    }
}

NodeTree buscaNo(SrbStruct *t, double x, double y, NoStruct *node, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2)
{
    if (node == t->nil)
    {
        return NULL;
    }
    if (pontoX(node->ponto) == x && pontoY(node->ponto) == y)
    {
        return node;
    }
    if (pontoX(node->ponto) > x || pontoY(node->ponto) > y)
    {
        return buscaNo(t, x, y, node->left, mbbX1, mbbY1, mbbX2, mbbY2);
    }
    else
    {
        return buscaNo(t, x, y, node->right, mbbX1, mbbY1, mbbX2, mbbY2);
    }
    return NULL;
}

void rb_transplant(SrbStruct *t, NoStruct *u, NoStruct *v)
{
    if (u->parent == t->nil)
        t->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

NoStruct *minimum(SrbStruct *t, NoStruct *x)
{
    while (x->left != t->nil)
        x = x->left;
    return x;
}

void rb_delete_fixup(SrbStruct *t, NoStruct *x)
{
    while (x != t->root && x->cor == BLACK)
    {
        if (x == x->parent->left)
        {
            NoStruct *w = x->parent->right;
            if (w->cor == RED)
            {
                w->cor = BLACK;
                x->parent->cor = RED;
                leftRotate(t, x->parent);
                w = x->parent->right;
            }
            if (w->left->cor == BLACK && w->right->cor == BLACK)
            {
                w->cor = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->cor == BLACK)
                {
                    w->left->cor = BLACK;
                    w->cor = RED;
                    rightRotate(t, w);
                    w = x->parent->right;
                }
                w->cor = x->parent->cor;
                x->parent->cor = BLACK;
                w->right->cor = BLACK;
                leftRotate(t, x->parent);
                x = t->root;
            }
        }
        else
        {
            NoStruct *w = x->parent->left;
            if (w->cor == RED)
            {
                w->cor = BLACK;
                x->parent->cor = RED;
                rightRotate(t, x->parent);
                w = x->parent->left;
            }
            if (w->right->cor == BLACK && w->left->cor == BLACK)
            {
                w->cor = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->cor == BLACK)
                {
                    w->right->cor = BLACK;
                    w->cor = RED;
                    leftRotate(t, w);
                    w = x->parent->left;
                }
                w->cor = x->parent->cor;
                x->parent->cor = BLACK;
                w->left->cor = BLACK;
                rightRotate(t, x->parent);
                x = t->root;
            }
        }
    }
    x->cor = BLACK;
}

void dentroRetanguloInfos(SrbStruct *t, NoStruct *node, Lista l, double x, double y, double w, double h, double epsilon)
{
    if (node == t->nil)
    {
        return;
    }    
    if (pontoInternoRetangulo(pontoX(node->ponto), pontoY(node->ponto), x, y, w, h))
    {
        if(node->info != NULL){
            listInsert(node->info,l);
        }
    }    
    
    if(pontoX(node->ponto) > x || (modulo(pontoX(node->ponto) - x) <= epsilon && pontoY(node->ponto) > y))
    {
        dentroRetanguloInfos(t, node->left, l, x, y, w, h, epsilon);
        epsilon++;
    } 
    dentroRetanguloInfos(t, node->right, l, x, y, w, h, epsilon);
    epsilon++;
}

void percorreLargura(SrbStruct *t, NoStruct *node, Lista l, FvisitaNo f)
{
    if (node == t->nil)
    {
        return;
    }
    insertFinal(l, node->info);
    percorreLargura(t, node->left, l, f);
    percorreLargura(t, node->right, l, f);
}

void percorreSimetrico(SrbStruct *t, NoStruct *node, Lista l, FvisitaNo f)
{
    if (node == t->nil)
        return;
    percorreSimetrico(t, node->left, l, f);
    insertFinal(l, node->info);
    percorreSimetrico(t, node->right, l, f);
}

void percorreProfundidade(SrbStruct *t, NoStruct *node, Lista l, FvisitaNo f)
{
    if (node == t->nil)
        return;
    percorreProfundidade(t, node->left, l, f);
    percorreProfundidade(t, node->right, l, f);
    insertFinal(l, node->info);
}


/*Funcoes obrigatorias*/

SRbTree createSRb(double epsilon)
{
    SrbStruct *srb = (SrbStruct *)malloc(sizeof(SrbStruct));
    NoStruct *nil = (NoStruct *)malloc(sizeof(NoStruct));
    srb->epsilon = epsilon;
    nil->left = NULL;
    nil->right = NULL;
    nil->parent = NULL;
    nil->cor = BLACK;
    nil->info = 0;
    nil->energia = 0;
    srb->nil = nil;
    srb->root = srb->nil;

    return srb;
}

NodeTree insertSRb(SRbTree t, double x, double y, double mbbX1, double mbbY1, double mbbX2, double mbbY2, Info info)
{
    SrbStruct *srb = (SrbStruct *)t;
    NoStruct *node = (NoStruct *)malloc(sizeof(NoStruct));
    node->ponto = criaPonto(x, y);
    node->info = info;
    node->right = NULL;
    node->left = NULL;
    node->parent = NULL;
    node->energia = 0;
    node->cor = RED;
    node->mbbX1 = mbbX1;
    node->mbbY1 = mbbY1;
    node->mbbX2 = mbbX2;
    node->mbbY2 = mbbY2;
    insert(srb, node);
    insertion_fixup(srb, node);
    return node;
}

NodeTree insertBbSRb(SRbTree t, double mbbX1, double mbbY1, double mbbX2, double mbbY2, Info info)
{
    return insertSRb(t, mbbX1, mbbY1, mbbX1, mbbY1, mbbX2, mbbY2, info);
}

NodeTree getNodeSRb(SRbTree t, double xa, double ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2)
{
    if (t == NULL)
    {
        return NULL;
    }
    SrbStruct *srb = (SrbStruct *)t;
    return buscaNo(t, xa, ya, srb->root, mbbX1, mbbY1, mbbX2, mbbY2);
}

Info getInfoSRb(SRbTree t, NodeTree n, double *xa, double *ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2)
{
    if (n != NULL)
    {
        t=t;
        xa=xa;
        ya=ya;
        mbbX1=mbbX1;
        mbbY1=mbbY1;
        mbbX2=mbbX2;
        mbbY2=mbbY2;
        NoStruct *node = (NoStruct *)n;
        return node->info;
    }
    return NULL;
}

void updateInfoSRb(SRbTree t, NodeTree n, Info i)
{
    if (n != NULL)
    {
        t=t;
        NoStruct *node = (NoStruct *)n;
        node->info = i;
    }
}

void getBbPartSRb(SRbTree t, double x, double y, double w, double h, Lista resultado)
{
    SrbStruct *tree = (SrbStruct *)t;
    dentroRetanguloInfos(t, tree->root, resultado, x, y, x + w, y + h, 1);
}

void getBbSRb(SRbTree t, double x, double y, double w, double h, Lista resultado)
{
    SrbStruct *tree = (SrbStruct *)t;
    dentroRetanguloInfos(tree, tree->root, resultado, x, y, x + w, y + h, 1);
}

Info removeSRb(SRbTree t, double xa, double ya, double *mbbX1, double *mbbY1, double *mbbX2, double *mbbY2)
{
    SrbStruct *srb = (SrbStruct *)t;
    NodeTree *aux = buscaNo(srb, xa, ya, srb->root, mbbX1, mbbY1, mbbX2, mbbY2);
    if (aux == NULL){
        return NULL;
    }
    NoStruct *node = (NoStruct *)aux;
    Info info = node->info;
    NoStruct *y = node;
    NoStruct *x;
    enum nodeColor y_orignal_color = y->cor;
    if (node->left == srb->nil){
        x = node->right;
        rb_transplant(srb, node, node->right);
    }else if (node->right == srb->nil){
        x = node->left;
        rb_transplant(srb, node, node->left);
    }else{
        y = minimum(srb, node->right);
        y_orignal_color = y->cor;
        x = y->right;
        if (y->parent == node){
            x->parent = node;
        }else{
            rb_transplant(srb, y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        rb_transplant(srb, node, y);
        y->left = node->left;
        y->left->parent = y;
        y->cor = node->cor;
    }
    if (y_orignal_color == BLACK)
        rb_delete_fixup(srb, x);
    return info;
}

void printSRb(SRbTree t, char *nomeArq)
{
    SrbStruct *srb = (SrbStruct *)t;
    RBT_export_dot(srb, nomeArq, 1);
}

void percursoLargura(SRbTree t, FvisitaNo fVisita, void *aux)
{
    SrbStruct *srb = (SrbStruct *)t;
    Lista l = aux;
    puts("percursoLargura");
    percorreLargura(srb, srb->root, l, fVisita);
}

void percursoSimetrico(SRbTree t, FvisitaNo fVisita, void *aux)
{
    SrbStruct *srb = (SrbStruct *)t;
    Lista l = aux;
    puts("percursoSimetrico");
    percorreSimetrico(srb, srb->root, l, fVisita);
}

void percursoProfundidade(SRbTree t, FvisitaNo fVisita, void *aux)
{
    SrbStruct *srb = (SrbStruct *)t;
    Lista l = aux;
    puts("percursoProfundidade");
    percorreProfundidade(srb, srb->root, l, fVisita);
}

void killSRb(SRbTree t)
{
    SrbStruct *tree = (SrbStruct *)t;

    NoStruct *node = tree->root;
    if (tree->root != NULL)
    {

        liberaArvore_aux(tree, node);
    }
    free(tree->nil);
    free(tree);
}
