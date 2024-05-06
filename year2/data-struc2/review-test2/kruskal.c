#include <stdio.h> 
#define MAX 100

typedef struct { 
    int u, v, peso; 
} Aresta; 

int cmp(const void *a, const void *b) { 
    return ((Aresta *)a)->peso - ((Aresta *)b)->peso; 
} 

void kruskal(Aresta *E, int arestas, int vertices, Aresta *A) { 
    int C[MAX]; // conjunto de componentes conexos
    int k, count = 0; 

    // ordena as arestas por peso
    qsort(E, arestas, sizeof(Aresta), cmp); 

    // inicializa o conjunto de componentes conexos
    for(int i = 0; i < vertices; i++) 
        C[i] = i; 

    // para cada aresta (u,v) em E, em ordem de peso
    for(int i = 0; i < arestas; i++) { 
        // se os vertices 'u' e 'v' nao estao na mesma componente conexa
        if(C[E[i].u] != C[E[i].v]) { 
            A[count++] = E[i]; // adiciona a aresta (u,v) na arvore geradora minima A
            k = C[E[i].u]; // armazena o identificador da componente conexa de 'u'
            // para cada vertice em C
            for(int j = 0; j < vertices; j++) {
                // se o vertice pertence a mesma componente conexa que 'u'
                if(C[j] == k) 
                    C[j] = C[E[i].v]; // atualiza o identificador da componente conexa para o de 'v'
            }
        } 
    } 
}