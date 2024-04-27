#ifndef RB_AUX_INCLUDED
#define RB_AUX_INCLUDED
#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

void printDOT(FILE *dotFile, Raiz *T, No *z);
void gerarDot(Raiz *T, const char *filename);
No* buscar(Raiz *T, No* z, int chave, int *cmp);
void calcAltura(Raiz *T, No* z, int *altura, int *altura_b);
void contarRB(Raiz *T, No* z, int* rubro, int* negro);
void percRB(Raiz* T);
void menu(Raiz* T);

#endif