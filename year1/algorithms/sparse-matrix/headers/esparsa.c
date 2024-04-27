#include "esparsa.h"
#include <stdio.h>
#include <stdlib.h>

void criar(Matriz *p)
{
    p->lin = TAM;
    p->col = TAM;
    p->arranjo = (No **)calloc(TAM, sizeof(No *));
    for (int lin = 0; lin < TAM; lin++)
        p->arranjo[lin] = NULL;
}

void inserir(Matriz *p, int valor, int lin, int col)
{
    // busca
    No *ant = NULL;
    No *atual = p->arranjo[lin];
    while (atual != NULL && atual->col < col)
    {
        ant = atual;
        atual = atual->prox;
    }
    // coluna do arranjo existe? senao cria nova coluna
    if (atual != NULL && atual->col == col)
    {
        if (valor == 0)
        {
            // primeira coluna?
            if (ant == NULL)
                p->arranjo[lin] = atual->prox;
            else
                ant->prox = atual->prox;
            // exclui coluna
            free(atual);
        }
        else
            atual->valor = valor;
    }
    else
    {
        No *novo = (No *)malloc(sizeof(No));
        novo->col = col;
        novo->valor = valor;
        novo->prox = atual;
        if (ant == NULL)
            p->arranjo[lin] = novo;
        else
            ant->prox = novo;
    }
}

int buscarValor(Matriz *p, int lin, int col)
{
    No *atual = p->arranjo[lin];
    while (atual != NULL && atual->col < col)
        atual = atual->prox;
    if (atual != NULL && atual->col == col)
        return atual->valor;
    return 0;
}

void info(Matriz *p)
{
    for (int lin = 0; lin < p->lin; lin++)
    {
        No *end = p->arranjo[lin];
        while (end != NULL)
        {   
            printf("%d [%d][%d]\n", end->valor, lin, end->col);
            end = end->prox;
        }
    }
}

void imprimir(Matriz *p)
{
    for (int i = 0; i < p->lin; i++)
    {
        for (int j = 0; j < p->col; j++)
            printf("%d ", buscarValor(p, i, j));
        printf("\n");
    }
    printf("\n");
}

Matriz somar(Matriz *A, Matriz *B, Matriz *C)
{
    for (int i = 0; i < A->lin; i++)
        for (int j = 0; j < A->col; j++)
        {
            int soma = buscarValor(A, i, j) + buscarValor(B, i, j);
            if (soma != 0)
                inserir(C, soma, i, j);
        }
    return *C;
}

Matriz multiplicar(Matriz *A, Matriz *B, Matriz *C)
{
    for (int i = 0; i < A->lin; i++)
        for (int j = 0; j < B->col; j++)
        {
            int soma = 0;
            for (int k = 0; k < A->col; k++)
                soma += buscarValor(A, i, k) * buscarValor(B, k, j);
            if (soma != 0)
                inserir(C, soma, i, j);
        }
    return *C;
}

int somaAbaixoDiag(Matriz *p)
{
    int soma = 0;
    for (int lin = 0; lin < p->lin; lin++)
    {
        No *atual = p->arranjo[lin];
        while (atual != NULL && atual->col < lin)
        {
            soma += atual->valor;
            atual = atual->prox;
        }
    }
    return soma;
}

void reiniciar(Matriz *p)
{
    for (int lin = 0; lin < p->lin; lin++)
    {
        No *end = p->arranjo[lin];
        while (end != NULL)
        {
            No *ant = end;
            end = end->prox;
            free(ant);
        }
        p->arranjo[lin] = NULL;
    }
}