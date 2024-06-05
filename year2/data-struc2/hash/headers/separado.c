#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastro.h"
#include "separado.h"

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
    if (cont >= TAM) {
        printf("Erro: Tabela Hash Separada está cheia.\n");
        return;
    }

    int index = espalharSeparado(produto.id);
    inserirLista(&hash[index], produto);
    cont++;
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