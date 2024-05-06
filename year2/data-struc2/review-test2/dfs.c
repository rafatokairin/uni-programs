#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define WHITE 0
#define YELLOW 1
#define RED 2

typedef struct adj {
    int vf, peso;
    struct adj *prox;
} Adj;

typedef struct vertice {
    Adj *cab;
} Vertice;

typedef struct graph {
    int vertices, arestas;
    Vertice *adj;
} Graph;

void visitaP(Graph *g, int i, int *cor) {
    cor[i] = YELLOW;
    Adj *v = g->adj[i].cab;
    while (v) {
        if (cor[v->vf] == WHITE)
            visitaP(g, v->vf, cor);
        v = v->prox;
    }
    cor[i] = RED;
}

void profundidade(Graph *g) {
    int cor[g->vertices];
    for (int i = 0; i < g->vertices; i++)
        cor[i] = WHITE;
    for (int i = 0; i < g->vertices; i++) 
        if (cor[i] == WHITE)
            visitaP(g, i, cor);
}