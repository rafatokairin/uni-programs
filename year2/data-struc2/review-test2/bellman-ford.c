#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct adj {
    int vf, peso;
    struct adj* prox;
} Adj;

typedef struct {
    Adj *cab;
} Vertice;

typedef struct {
    int vertices, arestas;
    Vertice *adj;
} Grafo;

void inicializarBF(Grafo *grafo, int *d, int *p, int s) {
    for(int v = 0; v < grafo->vertices; v++) {
        d[v] = INT_MAX / 2;
        p[v] = -1;
    }
    d[s] = 0;
}

void relaxar(Grafo* grafo, int *d, int *p, int u, int v) {
    Adj *ad = grafo->adj[u].cab;
    while(ad && ad->vf != v) 
        ad = ad->prox;
    if(ad) {
        if(d[v] > d[u] + ad->peso) {
            d[v] = d[u] + ad->peso;
            p[v] = u;
        }
    }
}

int *bellmanFord(Grafo *grafo, int s) {
    int *d = malloc(grafo->vertices * sizeof(int));
    int p[grafo->vertices];
    inicializarBF(grafo, d, p, s);

    for(int i = 1; i <= grafo->vertices - 1; i++) {
        for(int u = 0; u < grafo->vertices; u++) {
            Adj *ad = grafo->adj[u].cab;
            while(ad) {
                relaxar(grafo, d, p, u, ad->vf);
                ad = ad->prox;
            }
        }
    }

    for(int u = 0; u < grafo->vertices; u++) {
        Adj *ad = grafo->adj[u].cab;
        while(ad) {
            if(d[ad->vf] > d[u] + ad->peso) { 
                free(d);
                return NULL;
            }
            ad = ad->prox;
        }
    }
    return d;
}
