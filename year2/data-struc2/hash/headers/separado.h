#ifndef SEPARADO_INCLUDED
#define SEPARADO_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastro.h"

void iniLista(Lista *l);

void inserirLista(Lista *l, Produto prod);

No *buscarOrd(Lista *l, No **ant, int id);

void imprimirLista(Lista *l);

void iniSeparado(Lista *hash);

int espalharSeparado(int id);

void inserirSeparado(Lista *hash, Produto produto);

No *buscarSeparado(Lista *hash, int id);

void imprimirSeparado(Lista hash[]);

void removerSeparado(Lista *hash, int id);

void destruirLista(Lista *l);

void destruirSeparado(Lista *hash);

#endif