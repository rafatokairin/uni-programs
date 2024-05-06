#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct adjacencia {
    int vf, peso;
    struct adjacencia *prox;
} Adj;

typedef struct vertice {
    Adj *cab;
} Vertice;

typedef struct grafo {
    int vertices, arestas;
    Vertice *adj;
} Grafo;

void iniD(Grafo *g, int *d, int *p, int s) {
    for (int v = 0; v < g->vertices; v++) {
        d[v] = INT_MAX / 2;
        p[v] = -1;
    }
    d[s] = 0;
}

void relax(Grafo *g, int *d, int *p, int u, int vf) {
    Adj *ad = g->adj[u].cab;
    while (ad && ad->vf != vf)
        ad = ad->prox;
    if (ad) {
        if (d[vf] > d[u] + ad->peso) {
            d[vf] = d[u] + ad->peso;
            p[vf] = u;
        }   
    }
}

bool existeAberto(Grafo *g, int *aberto) {
    for (int i = 0; i < g->vertices; i++)
        if (aberto[i])
            return true;
    return false;
}

int menorDist(Grafo *g, int *aberto, int *d) {
    int i;
    for (i = 0; i < g->vertices; i++)
        if (aberto[i])
            break;
    if (i == g->vertices)
        return -1;
    int menor = i;
    for (i - menor + 1; i < g->vertices; i++) {
        if (aberto[i] && d[menor] > d[i])
            menor = i;
    }
    return menor;
}

int *dijkstra(Grafo *g, int s) {
    int *d = (int *)malloc(g->vertices * sizeof(int));
    int p[g->vertices];
    bool aberto[g->vertices];
    iniD(g, d, p, s);
    for (int i = 0; i < g->vertices; i++) 
        aberto[i] = true;
    while (existeAberto(g, aberto)) {
        int u = menorDist(g, aberto, d);
        aberto[u] = false;
        Adj *ad = g->adj[u].cab;
        while (ad) {
            relax(g, d, p, u, ad->vf);
            ad = ad->prox;
        }
    }
    return d;
}