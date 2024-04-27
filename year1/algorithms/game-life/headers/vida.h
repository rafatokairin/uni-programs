#ifndef VIDA_INCLUDED
#define VIDA_INCLUDED
#define TAM 30

#include <stdio.h>

typedef int **Matriz;

int vizinhos(Matriz, int, int);

void leitura(int, char *, Matriz *, Matriz *);

void imprimir(Matriz, Matriz, int);

void reiniciar(Matriz, Matriz);

#endif
