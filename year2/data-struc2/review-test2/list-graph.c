#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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

Graph *criarGrafo(int v) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    // init numbers of arestas, vertices and cab empty
    g->vertices = v;
    g->arestas = 0;
    g->adj = (Vertice *)malloc(v * sizeof(Vertice));
    for (int i = 0; i < v; i++)
        g->adj[i].cab = NULL;
    return g;
}

Adj *criarAdj(int vf, int peso) {
    Adj *temp = (Adj *)malloc(sizeof(Adj));
    // init vertice vf, peso and pointer to next
    temp->vf = vf;
    temp->peso = peso;
    temp->prox = NULL;
    return temp;
}

bool criarAresta(Graph *gr, int vi, int vf, int peso) {
    // insert list
    Adj *novo = criarAdj(vf, peso);
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab = novo;
    gr->arestas++;
    return true;
}

void imprimir(Graph *gr) {
    printf("Vertices: %d. Arestas: %d.\n", gr->vertices, gr->arestas);
    for (int i = 0; i < gr->vertices; i++) {
        printf("v%d: ", i);
        Adj *ad = gr->adj[i].cab;
        while (ad) {
            printf("v%d(%d) ", ad->vf, ad->peso);
            ad = ad->prox;
        }
        printf("\n");
    }   
}

int main() {
    Graph *gr = criarGrafo(5);
    criarAresta(gr, 0, 1, 2);
    criarAresta(gr, 1, 2, 4);
    criarAresta(gr, 2, 0, 12);
    criarAresta(gr, 2, 4, 40);
    criarAresta(gr, 3, 1, 3);
    criarAresta(gr, 4, 3, 8);

    imprimir(gr);
    return 0;
}