#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "ponto.h"
#include "lista.h"
#include "fila.h"
#include "linha.h"
#include "digraph.h"
#include <assert.h>
#include "extras.h"

typedef struct aresta Aresta;

typedef struct vertice
{
    Info info;
    char nome[40];
    int id,visited;
    int A;
    Aresta **adj;

}Vertice;

struct aresta{
    bool ativo, jaFoiAtivado;
    int from, to;
    Info info;
};

typedef struct Digraph {

    int V;
    Vertice **lista;

}DigraphStruct;


/*Funcoes Opcionais*/
bool jaVisitado(DigraphStruct *g, int id){
    Vertice *v = g->lista[id];
    if(v->visited == 1){
        return true;
    }
    return false;
}

void printGraph(Digraph g){
    DigraphStruct *graph = (DigraphStruct*)g;
    printf("Digraph{\n");
//     printf("%d\n", graph->V);
      for(int i = 1; i <= graph->V; i++){
            for (int j = 0; j < graph->lista[i]->A; j++){
                  printf("%d -> %d\n", graph->lista[i]->id, graph->lista[i]->adj[j]->to);
            
            }
      }
      printf("}\n");
}

/*Funcoes Obrigatorias*/

Digraph createGraph(int nVert){
    DigraphStruct *graph = (DigraphStruct*)malloc(sizeof(DigraphStruct));
    graph->V = nVert;
    graph->lista = calloc(nVert, sizeof(Vertice*));
      for(int i = 1; i <= nVert; i++){
            graph->lista[i] = (Vertice*)malloc(sizeof(Vertice));
            graph->lista[i]->id = i;
            graph->lista[i]->A = 0;
            graph->lista[i]->adj = calloc(nVert, sizeof(Aresta*));
            graph->lista[i]->info = NULL;
      }
    return graph;
}

Digraph cloneOnlyVertices(Digraph g, bool keepInfo){

      DigraphStruct *g1 = (DigraphStruct*)g;
      DigraphStruct *g2 = (DigraphStruct*)createGraph(g1->V);

      for(int i = 0; i < g1->V; i++){
            g2->lista[i] = (Vertice*)malloc(sizeof(Vertice));
            g2->lista[i]->id = g1->lista[i]->id;
            strcpy(g2->lista[i]->nome, g1->lista[i]->nome);
            g2->lista[i]->A = 0;
            

            if(g1->lista[i]->info != NULL && keepInfo == true){
                  g2->lista[i]->info = g1->lista[i]->info;
            }
            else{
                  g2->lista[i]->info = NULL;
      }
      }
      return g2;
}

Digraph cloneOnlyEnabled(Digraph g, bool keepInfo){
      DigraphStruct *g1 = (DigraphStruct*)g;
      DigraphStruct *g2 = (DigraphStruct*)createGraph(g1->V);

      for(int i = 0; i < g1->V; i++){
            g2->lista[i] = (Vertice*)malloc(sizeof(Vertice));
            g2->lista[i]->id = g1->lista[i]->id;
            g2->lista[i]->A = 0;
            

            if(g1->lista[i]->info != NULL && keepInfo == true){
                  g2->lista[i]->info = g1->lista[i]->info;
            }
            else{
                  g2->lista[i]->info = NULL;
            }
      }

      for(int i = 0; i < g1->V; i++){
          for(int j = 0; j < g1->lista[i]->A; j++){
              if(g1->lista[i]->adj[j]->ativo == true){
                  addEdge(g2, g1->lista[i]->adj[j]->from, g1->lista[i]->adj[j]->to, g1->lista[i]->adj[j]->info);
              }
          }
      }
      return g2;
}

Digraph cloneAll(Digraph g, bool keepInfo){
    DigraphStruct *g1 = (DigraphStruct*)g;
    DigraphStruct *g2 = (DigraphStruct*)createGraph(g1->V);
    for(int i = 1; i < g1->V; i++){
        g2->lista[i] = (Vertice*)malloc(sizeof(Vertice));
        g2->lista[i]->id = g1->lista[i]->id;
        g2->lista[i]->A = 0;
        for (int j = 0; j < g1->lista[i]->A; j++)
        {
            g2->lista[i]->adj[j]->ativo = g1->lista[i]->adj[j]->ativo;
            g2->lista[i]->adj[j]->jaFoiAtivado = g1->lista[i]->adj[j]->jaFoiAtivado;
            g2->lista[i]->adj[j]->from = g1->lista[i]->adj[j]->from;
            g2->lista[i]->adj[j]->to = g1->lista[i]->adj[j]->to;
        }
        if(g1->lista[i]->info != NULL && keepInfo == true){
            g2->lista[i]->info = g1->lista[i]->info;
        }
        else{
            g2->lista[i]->info = NULL;
        }
    }
    return g2;
}

void setNodeName(Digraph g, Node n, char *nome){
      int n1 = (int)n;
      DigraphStruct *g1 = (DigraphStruct*)g;
      strcpy(g1->lista[n1]->nome, nome);
}

void addVerticesNames(Digraph g, char *nomes[], int nNomes){
      DigraphStruct *g1 = (DigraphStruct*)g;
      if(g1->V >= nNomes){
      for (int i = 1; i < nNomes; i++){
            int id = stringToInt(nomes[i]);
            g1->lista[i]->id = id;
            strcpy(g1->lista[i]->nome, nomes[i]);
      }
    }
}

Node getNode(Digraph g,  char *nome){
      DigraphStruct *g1 = (DigraphStruct*)g;
      for(int i = 1; i <= g1->V; i++){
            if(strcmp(g1->lista[i]->nome, nome) == 0){
                  return g1->lista[i]->id;
            }
      }
      return -1;
}

Info getNodeInfo(Digraph g, Node node){
      int n1 = (int)node;
      DigraphStruct *g1 = (DigraphStruct*)g;
      for(int i = 1; i <= g1->V; i++){
            {
                  if(g1->lista[i]->id == n1){
                        return g1->lista[i]->info;
                  }
            }
      }
      return NULL;
}

void setNodeInfo(Digraph g, Node node, Info info){
      int n1 = (int)node;
      DigraphStruct *g1 = (DigraphStruct*)g;
      for(int i = 1; i <= g1->V; i++){
            {
                  if(g1->lista[i]->id == n1){
                        g1->lista[i]->info = info;
                        return;
                  }
            }
      }
}

Edge addEdge(Digraph g, Node from, Node to, Info info){
      int n1 = (int)from;
      int n2 = (int)to;
      if(g == NULL || n1 < 0 || n2 < 0){
            return NULL;
      }
      DigraphStruct *g1 = (DigraphStruct*)g;

      int arestas = g1->lista[n1]->A;
      g1->lista[n1]->adj[arestas] = (Aresta*)malloc(sizeof(Aresta));
      g1->lista[n1]->adj[arestas]->info = info;
      g1->lista[n1]->adj[arestas]->ativo = true;
      g1->lista[n1]->adj[arestas]->jaFoiAtivado = false;
      g1->lista[n1]->adj[arestas]->from = n1;
      g1->lista[n1]->adj[arestas]->to = n2;
      g1->lista[n1]->A++;
      return g1->lista[from]->adj[arestas];
}

Edge getEdge(Digraph g, Node from, Node to){
	int n1 = (int)from;
      int n2 = (int)to;
      if(g == NULL || n1 < 0 || n2 < 0){
            return NULL;
      }
	DigraphStruct *g1 = (DigraphStruct*)g;
	for(int i = 1; i < g1->V; i++){
		for(int j = 0; j<g1->lista[i]->A; j++)
		{
			if(g1->lista[i]->adj[j]->from == n1 && g1->lista[i]->adj[j]->to == n2){
                        Aresta *e = g1->lista[i]->adj[j];
				return e;
			}
		}
	}
	return NULL;
}

Node getFromNode(Digraph g, Edge e){
      DigraphStruct *g1 = (DigraphStruct*)g;
      Aresta *e1 = (Aresta*)e;
      for(int i = 1; i < g1->V; i++){
            for(int j = 0; j<g1->lista[i]->A; j++)
            {
                  if(g1->lista[i]->adj[j]->from == e1->from && g1->lista[i]->adj[j]->to == e1->to){
                        return g1->lista[i]->adj[j]->from;
                  }
            }
      }
      return -1;
}
 
Node getToNode(Digraph g, Edge e){
      DigraphStruct *g1 = (DigraphStruct*)g;
      Aresta *e1 = (Aresta*)e;
      for(int i = 1; i < g1->V; i++){
            for(int j = 0; j<g1->lista[i]->A; j++)
            {
                  if(g1->lista[i]->adj[j] == e1){
                        return g1->lista[i]->adj[j]->to;
                  }
            }
      }
      return -1;
}

Info getEdgeInfo(Digraph g, Edge e){
      DigraphStruct *g1 = (DigraphStruct*)g;
      Aresta *e1 = (Aresta*)e;
      for(int i = 0; i < g1->V; i++){
            for(int j = 0; j<g1->lista[i]->A; j++)
            {
                  if(g1->lista[i]->adj[j] == e1){
                        return g1->lista[i]->adj[j]->info;
                  }
            }
      }
      return NULL;
}  

void setEdgeInfo(Digraph g, Edge e, Info info){
      DigraphStruct *g1 = (DigraphStruct*)g;
      Aresta *e1 = (Aresta*)e;
      for(int i = 1; i < g1->V; i++){
            for(int j = 0; j<g1->lista[i]->A; j++)
            {
                  if(g1->lista[i]->adj[j] == e1){
                        g1->lista[i]->adj[j]->info = info;
                  }
            }
      }
}

void removeEdge(Digraph g, Edge e){
      if(g == NULL || e == NULL){
            return;
      }
      DigraphStruct *g1 = (DigraphStruct*)g;
      Aresta *e1 = (Aresta*)e;
      for(int i = 1; i < g1->V; i++){
            for(int j = 0; j<g1->lista[i]->A; j++)
            {
                  if(g1->lista[i]->adj[j]->from == e1->from && g1->lista[i]->adj[j]->to == e1->to){
                        free(g1->lista[i]->adj[j]);
                        g1->lista[i]->A--;
                  }
            }
      }
}

void disableEdge(Digraph g, Edge e){
      DigraphStruct *g1 = (DigraphStruct*)g;
      Aresta *e1 = (Aresta*)e;
      for(int i = 1; i < g1->V; i++){
            for(int j = 0; j<g1->lista[i]->A; j++)
            {
                  if(g1->lista[i]->adj[j]->from == e1->from && g1->lista[i]->adj[j]->to == e1->to){
                        g1->lista[i]->adj[j]->ativo = false;
                        g1->lista[i]->adj[j]->jaFoiAtivado = true;
                        return;
                  }
            }
      }
}

void enableEdge(Digraph g, Edge e){
      DigraphStruct *g1 = (DigraphStruct*)g;
      Aresta *e1 = (Aresta*)e;
      for(int i = 1; i < g1->V; i++){
           for(int j = 0; j<g1->lista[i]->A; j++)
            {
                  if(g1->lista[i]->adj[j]->from == e1->from && g1->lista[i]->adj[j]->to == e1->to){
                        g1->lista[i]->adj[j]->ativo = true;
                        return;
                  }
            }
      }
}

void enableAllEdges(Digraph g){
      DigraphStruct *g1 = (DigraphStruct*)g;
      for(int i = 1; i < g1->V; i++){
            for(int j = 0; j<g1->lista[i]->A; j++)
            {
                  if(g1->lista[i]->adj[j]->jaFoiAtivado == true){
                        g1->lista[i]->adj[j]->ativo = true;
                  }
            }
      }
}

bool isDisabled(Digraph g, Edge e){
      DigraphStruct *g1 = (DigraphStruct*)g;
      Aresta *e1 = (Aresta*)e;
      for(int i = 1; i < g1->V; i++){
            for(int j = 0; j<g1->lista[i]->A; j++)
            {
                  if(g1->lista[i]->adj[j] == e1){
                        if(g1->lista[i]->adj[j]->ativo == false){
                              return true;
                        }
                        return false;
                  }
            }
      }
      return false;
}

void delEdge(Edge e){
      free(e);
}

bool islistaacent(Digraph g, Node from, Node to){
      DigraphStruct *g1 = (DigraphStruct*)g;
      int from1 = (int)from;
      int to1 = (int)to;
      for(int i = 1; i < g1->V; i++){
            for(int j = 0; j<g1->lista[i]->A; j++)
            {
                  if(g1->lista[i]->adj[j]->from == from1 && g1->lista[i]->adj[j]->to == to1){
                        return true;
                  }
            }
      }
      return false;
}

void adjacentNodes(Digraph g, Node node, Lista noslistaacentes){
      DigraphStruct *g1 = (DigraphStruct*)g;
      int node1 = (int)node;
      for(int i = 1; i < g1->V; i++){
            for(int j = 0; j<g1->lista[i]->A; j++)
            {
                  if(g1->lista[i]->adj[j]->from == node1){
                        insertFinal(noslistaacentes, &g1->lista[i]->adj[j]->to);
                  }
            }
      }
}

void adjacentEdges(Digraph g, Node node, Lista arestaslistaacentes){
      DigraphStruct *g1 = (DigraphStruct*)g;
      int node1 = (int)node;
      for(int i = 1; i < g1->V; i++){
            for(int j = 0; j<g1->lista[i]->A; j++)
            {
                  if(g1->lista[i]->adj[j]->from == node1 && g1->lista[i]->adj[j]->ativo == true){
                        insertFinal(arestaslistaacentes, g1->lista[i]->adj[j]->info);
                  }
            }
      }
}

void  getNodeNames(Digraph g, Lista nomesNodes){
      DigraphStruct *g1 = (DigraphStruct*)g;
      for(int i = 1; i <= g1->V; i++){
            listInsert( g1->lista[i]->info, nomesNodes);
      }
}

void getEdges(Digraph g, Lista arestas){
      DigraphStruct *g1 = (DigraphStruct*)g;
      if(arestas == NULL && g1 == NULL){
            return;
      }
      for(int i = 1; i <= g1->V; i++){
            for(int j = 0; j<g1->lista[i]->A; j++)
            {
                  if(g1->lista[i]->adj[j] != NULL && g1->lista[i]->adj[j]->ativo == true){
                        listInsert(g1->lista[i]->adj[j]->info, arestas);
                  }
            }
      }
}

/*
   Faz percurso em profundidade sobre o grafo g, classificando as arestas do grafo em
   aresta de arvore, aresta de avanco, de retorno e cruzada-> No momento da classificacao,
   a respectiva funcao e' invocada (caso nao seja NULL)->
   "extra" e' um apontador que pode ser usado por qualquer uma das funcoes->
   A busca em profundidade, eventualmente, pode produzir uma floresta-> Neste caso,
   a funçao newTree e' invocada sempre que o percurso for retomado->
 */  
bool dfs(Digraph g, Node node, procEdge treeEdge, procEdge forwardEdge, procEdge returnEdge, procEdge crossEdge, dfsRestarted newTree, void *extra){
      g=g;
      node=node;
      treeEdge=treeEdge;
      forwardEdge=forwardEdge;
      returnEdge=returnEdge;
      crossEdge=crossEdge;
      newTree=newTree;
      extra=extra;
      return false;
}

bool bfs(Digraph g, Node node, procEdge discoverNode, void *extra){
      discoverNode=discoverNode;
	int startVertex = (int)node;
	DigraphStruct *graph = (DigraphStruct*)g;
	Fila q = createQueue();
	Lista l = createList();
      Lista edges = createList();
	enqueue (&startVertex, q);
	while (!queueIsEmpty(q)) {
    	FilaInfo aux = dequeue(q);
      int currentVertex = *(int*)aux;

        adjacentNodes(g, currentVertex, l);
        adjacentEdges(g, currentVertex, edges);
        for(Lista no = getFirst(edges); no != NULL; no = getNext(edges,no)){
            if(getInfos(no)!=NULL){
                listInsert(getInfos(no), extra);
            }
        }
            for(Lista no = getFirst(l); no != NULL; no = getNext(l, no)){
                if(getInfos(no)!=NULL && graph->lista[currentVertex]->visited == 0){
                    enqueue(getInfos(no), q);
                    graph->lista[currentVertex]->visited = 1;
                }  
            }
        }
    return true;
}