#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int u, v, peso;
} Aresta;

int menorDistancia(int dist[], bool interligado[], int V) {
    int min = INT_MAX / 2, min_index;
    for(int v = 0; v < V; v++) {
        if(!interligado[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void prim(int V, int grafo[][V]) {
    Aresta A[V]; // arvore geradora minima
    int dist[V]; // distancia minima
    int pai[V];  
    bool interligado[V]; 

    for(int v = 0; v < V; v++) {
        dist[v] = INT_MAX/2;
        pai[v] = -1;
        interligado[v] = false;
    }
    dist[0] = 0;

    for(int i = 0; i < V - 1; i++) {
        int u = menorDistancia(dist, interligado, V);
        interligado[u] = true;

        for(int v = 0; v < V; v++) {
            if(grafo[u][v] && !interligado[v] && grafo[u][v] < dist[v]) {
                pai[v] = u;
                dist[v] = grafo[u][v];
            }
        }
    }

    for(int i = 1; i < V; i++) {
        A[i].u = pai[i];
        A[i].v = i;
        A[i].peso = grafo[i][pai[i]];
    }
}