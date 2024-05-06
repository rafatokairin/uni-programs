#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int vertices, arestas, **adj;
} Graph;

Graph *criarGrafo(int v) {
    Graph *gr = (Graph *)malloc(sizeof(Graph));
    gr->vertices = v;
    gr->arestas = 0;
    gr->adj = (int **)malloc(v * sizeof(int *));
    for (int i = 0; i < v; i++)
        gr->adj[i] = (int *)malloc(v * sizeof(int));
    return gr;
}

bool criarAresta(Graph *gr, int vi, int vf, int peso) {
    // add aresta and peso
    if (gr->adj[vi][vf] == 0) {
        gr->adj[vi][vf] = peso;
        gr->arestas++;
    } 
    return true;
}

bool removerAresta(Graph *gr, int vi, int vf) {
    // remove aresta and peso
    if (gr->adj[vi][vf] != 0) {
        gr->adj[vi][vf] = 0;
        gr->arestas--;
    }
    return true;
}

bool existeAresta(Graph *gr, int vi, int vf) {
    // check if exists aresta
    if (gr->adj[vi][vf] != 0)
        return true;
    return false;
}

bool temVizinho(Graph *gr, int v) {
    // check if v has neighbours
    for (int i = 0; i < gr->vertices; i++)
        if (gr->adj[v][i] != 0)
            return true;
    return false;
}

int grauVertice(Graph *gr, int v) {
    int grau = 0;
    // check if v has neighbours and grau++
    for (int i = 0; i < gr->vertices; i++)
        if (gr->adj[v][i] != 0)
            grau++;
    return grau;
}