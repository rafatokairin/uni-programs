#ifndef ITEM_INCLUDED
#define ITEM_INCLUDED
#define MAX_LINHA 128
#include <stdio.h>

typedef struct {
    int peso, valor;
} Item;

double razaoItem(Item);

void quicksortRazao(Item *, int);

void quicksortPeso(Item *, int);

void quicksortValor(Item *, int);

int numLinhas(FILE *);

void lerArquivo(int, char *, int *, int *, Item **);

#endif