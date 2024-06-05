#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastro.h"
#include "aberto.h"

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
    if (cont >= TAM) {
        printf("Erro: Tabela Hash Aberta está cheia.\n");
        return;
    }

    int index = espalharAberto(produto.id);
    int passo = passoHash(produto.id);

    while (hash[index].id != -1) {
        index = (index + passo) % TAM;
    }
    hash[index] = produto;
    cont++;
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
            printf("[%2d] = \n", i);
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