#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// queue
typedef struct no {
    int dado;
    struct no *prox;
} No;

typedef struct fila {
    No *ini, *fim;
} Fila;

void criarFila(Fila *f) {
    f->ini = NULL;
    f->fim = NULL;
}

void inserirFila(Fila *f, int dado) {
    No *novo = (No*)malloc(sizeof(No));
    novo->dado = dado;
    novo->prox = NULL;
    if (f->ini == NULL)
        f->ini = novo;
    else 
        f->fim->prox = novo;
    f->fim = novo;
}

void removerFila(Fila *f, int *dado) {
    if (f->ini == NULL)
        return;
    *dado = f->ini->dado;
    No *temp = f->ini;
    f->ini = f->ini->prox;
    free(temp);
    if (f->ini == NULL)
        f->fim = NULL;
}

// bfs
#define WHITE 0
#define YELLOW 1

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

void visitaL(Graph *g, int i, int *cor) {
    Fila f;
    criarFila(&f);
    cor[i] = YELLOW;
    inserirFila(&f, i);
    while (f.ini != NULL) {  
        removerFila(&f, &i);
        Adj *v = g->adj[i].cab;
        while (v) {
            if (cor[v->vf] == WHITE) {
                cor[v->vf] = YELLOW;
                inserirFila(&f, v->vf);
            }
            v = v->prox;
        }
    }
}

void largura(Graph *g) {
    int cor[g->vertices];
    for (int i = 0; i < g->vertices; i++)
        cor[i] = WHITE;
    for (int i = 0; i < g->vertices; i++) 
        if (cor[i] == WHITE)
            visitaL(g, i, cor);
}
