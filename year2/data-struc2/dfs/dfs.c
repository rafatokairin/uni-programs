#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ENT 703
#define STAR 42
#define EXIT 482

typedef struct Node {
    int dest;
    struct Node* next;
} Node;

typedef struct {
    int V;
    Node** adjList;
} Graph;

Graph* criaGrafo(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->adjList = (Node**)malloc(V * sizeof(Node*));
    for (int i = 0; i < V; i++)
        graph->adjList[i] = NULL;
    return graph;
}

void addAresta(Graph* graph, int v1, int v2) {
    // Adiciona v2 na lista de adjacencia de v1
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = v2;
    newNode->next = graph->adjList[v1];
    graph->adjList[v1] = newNode;

    // Adiciona v1 na lista de adjacencia de v2
    newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = v1;
    newNode->next = graph->adjList[v2];
    graph->adjList[v2] = newNode;
}

int ascii(const char* str) {
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++)
        sum += str[i];
    return sum;
}

int dfs(Graph* graph, int atual, int dest, bool* visited) {
    if (atual == dest)
        return 0; // Retorna 0 se chegou no destino
    visited[atual] = true; // Marca vertice atual como visitado
    int min_dist = -1; // Inicializa distancia minima como -1

    // Percorre a lista de adjacencia do vertice atual
    Node* curr = graph->adjList[atual];
    while (curr != NULL) {
        int v = curr->dest;
        if (!visited[v]) {
            int distance = dfs(graph, v, dest, visited);
            if (distance != -1) {
                if (min_dist == -1 || (distance + 1 < min_dist))
                    min_dist = distance + 1;
            }
        }
        curr = curr->next;
    }
    visited[atual] = false; // Desmarca o vertice como visitado (backtrack)
    return min_dist; // Retorna a distancia minima ate o destino
}

int main() {
    int pontos, ligacoes;
    printf("Insira valor P (4 <= P <= 4000) e L (4 <= L <= 5000):\n");
    scanf("%d %d", &pontos, &ligacoes);
    while (pontos < 4 || pontos > 4000 || ligacoes < 4 || ligacoes > 5000)
    {
        printf("Insira valor P (4 <= P <= 4000) e L (4 <= L <= 5000):\n");
        scanf("%d %d", &pontos, &ligacoes);
    }

    int V = pontos * 255;
    Graph* graph = criaGrafo(V);

    char v1[50], v2[50];
    printf("\nInsira origem (String) e destino (String):\n");
    for (int i = 0; i < ligacoes; i++) {
        scanf("%s %s", v1, v2);
        addAresta(graph, ascii(v1), ascii(v2));
    }

    bool* visited = (bool*)calloc(V, sizeof(bool));

    int ent_to_star = dfs(graph, ENT, STAR, visited);
    int star_to_exit = dfs(graph, STAR, EXIT, visited);
    int total_dist = ent_to_star + star_to_exit;

    printf("\nDistancia minima:\n%d\n", total_dist);

    free(visited);
    for (int i = 0; i < V; i++) {
        Node* curr = graph->adjList[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->adjList);
    free(graph);
    return 0;
}
