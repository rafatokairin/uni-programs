#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 31
int cont = 0;

typedef struct {
    int id;
    char descricao[20];
    float preco;
} Produto;

typedef struct no {
    struct no *prox;
    Produto prod;
} No;

typedef struct {
    No *ini;
} Lista;

Produto cadastrarProduto(int id, char *descricao, float preco) {
    Produto novo;
    novo.id = id;
    strcpy(novo.descricao, descricao);
    novo.preco = preco;
    return novo;
}

void iniLista(Lista *l) {
    l->ini = NULL;
}

void inserirLista(Lista *l, Produto prod) {
    No *novo = malloc(sizeof(No));
    novo->prod = prod;
    novo->prox = l->ini;
    l->ini = novo;
}

No *buscarOrd(Lista *l, No **ant, int id) {
    *ant = NULL;
    No *atual = l->ini;
    while (atual != NULL && atual->prod.id != id) {
        *ant = atual;
        atual = atual->prox;
    }
    if (atual != NULL && atual->prod.id == id)
        return atual;
    return NULL;
}

void imprimirLista(Lista *l) {
    No *aux = l->ini;
    while (aux) {
        printf("%2d ", aux->prod.id);
        aux = aux->prox;
    }
}

void iniSeparado(Lista *hash) {
    for (int i = 0; i < TAM; i++)
        iniLista(&hash[i]);
}

int espalharSeparado(int id) {
    return id % TAM;
}

void inserirSeparado(Lista *hash, Produto produto) {
    int index = espalharSeparado(produto.id);
    inserirLista(&hash[index], produto);
}

No *buscarSeparado(Lista *hash, int id) {
    No *ant;
    int index = espalharSeparado(id);
    return buscarOrd(&hash[index], &ant, id);
}

void imprimirSeparado(Lista hash[]) {
    for (int i = 0; i < TAM; i++) {
        printf("[%2d] = ", i);
        imprimirLista(&hash[i]);
        printf("\n");
    }
}

void removerSeparado(Lista *hash, int id) {
    int index = espalharSeparado(id);
    No *ant, *rmv = buscarOrd(&hash[index], &ant, id);
    No *atual = hash[index].ini;
    if (rmv == NULL)
        return;
    if (ant == NULL)
        hash[index].ini = rmv->prox;
    else
        ant->prox = rmv->prox;
    free(rmv);
    cont--;
}

void destruirLista(Lista *l) {
    No *atual = l->ini;
    No *proximo = NULL;
    while (atual) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    l->ini = NULL;
}

void destruirSeparado(Lista *hash) {
    for (int i = 0; i < TAM; i++)
        destruirLista(&hash[i]);
}

void iniAberto(Produto hash[]) {
    for (int i = 0; i < TAM; i++)
        hash[i].id = -1;
}

int espalharAberto(int cod) {
    int part1 = cod >> 10;
    int part2 = cod & (TAM - 1);
    return part1 ^ part2;
}

int passoHash(int id) {
    return 1 + (id % (TAM - 1));
}

void inserirAberto(Produto hash[], Produto produto) {
    int index = espalharAberto(produto.id);
    int passo = passoHash(produto.id);

    while (hash[index].id != -1) {
        index = (index + passo) % TAM;
    }
    hash[index] = produto;
}

int buscarAberto(Produto hash[], int id) {
    int index = espalharAberto(id);
    int passo = passoHash(id);

    while (hash[index].id != -1) {
        if (hash[index].id == id)
            return index;
        index = (index + passo) % TAM;
    }
    return -1;
}

void imprimirAberto(Produto hash[]) {
    for (int i = 0; i < TAM; i++) {
        if (hash[i].id == -1)
            printf("[%2d] = \n", i, hash[i].id);
        else
            printf("[%2d] = %2d\n", i, hash[i].id);
    }
}

void removerAberto(Produto hash[], int id) {
    int index = buscarAberto(hash, id);
    if (index == -1)
        return;
    hash[index].id = -1;
    cont--;
}

int main() {
    Lista tabelaSeparada[TAM];
    Produto tabelaAberta[TAM];

    iniSeparado(tabelaSeparada);
    iniAberto(tabelaAberta);

    int opcao, id;
    char descricao[20];
    float preco;

    do {
        printf("1. Inserir\n2. Buscar\n3. Remover\n4. Imprimir Hash com Encadeamento Separado\n5. Imprimir Hash com Encadeamento Aberto\n6. Sair\n");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                if (cont < TAM) {
                    printf("Digite o ID:\n");
                    scanf("%d", &id);
                    printf("Digite a descricao:\n");
                    scanf("%s", descricao);
                    printf("Digite o preco:\n");
                    scanf("%f", &preco);

                    if (preco < 200) {
                        inserirSeparado(tabelaSeparada, cadastrarProduto(id, descricao, preco));
                        printf("Produto inserido na Tabela Hash com Encadeamento Separado!\n");
                        cont++;
                    } else {
                        inserirAberto(tabelaAberta, cadastrarProduto(id, descricao, preco));
                        printf("Produto inserido na Tabela Hash com Encadeamento Aberto!\n");
                        cont++;
                    }
                } else {
                    printf("Numero maximo de elementos atingido!\n");
                }
                break;
            case 2:
                printf("Digite o ID:\n");
                scanf("%d", &id);
                    No *indexSeparado = buscarSeparado(tabelaSeparada, id);
                    if (indexSeparado != NULL)
                        printf("Produto encontrado na Tabela Hash com Encadeamento Separado!\n");
                    else {
                        int indexAberto = buscarAberto(tabelaAberta, id);
                        if (indexAberto != -1)
                            printf("Produto encontrado na Tabela Hash com Encadeamento Aberto!\n");
                        else
                            printf("Produto nao encontrado!\n");
                    }
                break;
            case 3:
                printf("Digite o ID:\n");
                scanf("%d", &id);
                removerSeparado(tabelaSeparada, id);
                removerAberto(tabelaAberta, id);
                break;
            case 4:
                printf("\nTabela Hash com Encadeamento Separado:\n");
                imprimirSeparado(tabelaSeparada);
                break;
            case 5:
                printf("\nTabela Hash com Encadeamento Aberto:\n");
                imprimirAberto(tabelaAberta);
                break;
            case 6:
                printf("Finalizando...\n");
                break;
            default:
                break;
        }
    } while (opcao != 6);

    destruirSeparado(tabelaSeparada);
    return 0;
}
