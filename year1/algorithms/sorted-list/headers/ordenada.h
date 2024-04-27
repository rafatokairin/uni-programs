#ifndef ORDENADA_INCLUDED
#define ORDENADA_INCLUDED
#include <stdbool.h>

typedef struct no {
    int chave;
    struct no *prox;
} No;

typedef struct {
    No *inicio;
    int tam;
} Lista;

void criar(Lista *);

void imprimir(Lista *);

No *buscarOrd(Lista *, No **, int);

bool inserirOrd(Lista *, int);

bool remover(Lista *, int);

void reiniciar(Lista *);

void inverter(Lista *);

void menu(Lista *);

#endif