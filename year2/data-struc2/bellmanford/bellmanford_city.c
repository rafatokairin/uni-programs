#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct adjacencia {
    int vertice, peso;
    struct adjacencia *prox;
} Adjacencia;

typedef struct vertice {
    Adjacencia *cab;
} Vertice;

typedef struct grafo {
    int vertices, arestas;
    Vertice *adj;
} Grafo;

void inicializa(Grafo *g, int *d, int *p, int s) {
    for (int v = 0; v < g->vertices; v++) {
        d[v] = INT_MAX;
        p[v] = -1;
    }
    d[s] = 0;
}

bool relaxa(int *d, int u, int v, int peso) {
    if (d[u] != INT_MAX && d[v] > d[u] + peso) {
        d[v] = d[u] + peso;
        return true; // Houve relaxamento
    }
    return false;
}

bool bellmanFord(Grafo *g, int s, int *d, int *p) {
    inicializa(g, d, p, s);
    // Relaxar arestas repetidamente
    for (int i = 0; i < g->vertices - 1; i++) {
        bool houve_relaxamento = false;
        for (int u = 0; u < g->vertices; u++) {
            Adjacencia *ad = g->adj[u].cab;
            while (ad != NULL) {
                if (relaxa(d, u, ad->vertice, ad->peso)) {
                    p[ad->vertice] = u;
                    houve_relaxamento = true;
                }
                ad = ad->prox;
            }
        }
        if (!houve_relaxamento)
            break; // Nenhuma mudanca nas distancias, parar
    }

    // Verificar se ha ciclo de custo negativo alcancavel a partir de s
    for (int u = 0; u < g->vertices; u++) {
        Adjacencia *ad = g->adj[u].cab;
        while (ad != NULL) {
            if (d[u] != INT_MAX && d[ad->vertice] > d[u] + ad->peso) {
                return true; // Houve deteccao de ciclo de custo negativo
            }
            ad = ad->prox;
        }
    }
    return false;
}

// Funcao utilitaria para adicionar uma aresta ao grafo
void adicionaAresta(Grafo *g, int u, int v, int peso) {
    Adjacencia *nova = (Adjacencia *)malloc(sizeof(Adjacencia));
    nova->vertice = v;
    nova->peso = peso;
    nova->prox = g->adj[u].cab;
    g->adj[u].cab = nova;
}

int main() {
    int cidades, rotas, origem, destino, custo, partida;
    printf("Digite a quantidade de cidades e rotas:\n");
    scanf("%d %d", &cidades, &rotas);

    Grafo g;
    g.vertices = cidades;
    g.adj = (Vertice *)malloc(cidades * sizeof(Vertice));

    // Inicializar grafo com nenhuma aresta
    for (int i = 0; i < cidades; i++)
        g.adj[i].cab = NULL;

    for (int i = 0; i < rotas; i++) {
        printf("\nRota %d:\n", i);
        printf("Digite origem:\n");
        scanf("%d", &origem);
        printf("Digite destino:\n");
        scanf("%d", &destino);
        printf("Digite custo:\n");
        scanf("%d", &custo);
        adicionaAresta(&g, origem, destino, custo);
    }

    // Definir a cidade de origem
    printf("\nDigite cidade de partida:\n");
    scanf("%d", &partida);

    // Vetores de distancia e predecessores
    int *distancias = (int *)malloc(cidades * sizeof(int));
    int *predecessores = (int *)malloc(cidades * sizeof(int));

    // Executar o algoritmo de Bellman-Ford
    bool ciclo_negativo = bellmanFord(&g, partida, distancias, predecessores);

    if (ciclo_negativo)
        printf("\nExiste ciclo de custo negativo alcancavel a partir da cidade de partida.\n");
    else {
        printf("\nMenores distancias a partir da cidade de partida %d:\n", partida);
        for (int i = 0; i < cidades; i++)
            printf("Para a cidade %d: Distancia = %d\n", i, distancias[i]);
    }

    // Liberar memoria alocada
    for (int i = 0; i < cidades; i++) {
        Adjacencia *ad = g.adj[i].cab;
        while (ad != NULL) {
            Adjacencia *temp = ad;
            ad = ad->prox;
            free(temp);
        }
    }
    free(g.adj);
    free(distancias);
    free(predecessores);
    return 0;
}