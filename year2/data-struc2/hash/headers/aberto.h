#ifndef ABERTO_INCLUDED
#define ABERTO_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastro.h"

void iniAberto(Produto hash[]);

int espalharAberto(int cod);

int passoHash(int id);

void inserirAberto(Produto hash[], Produto produto);

int buscarAberto(Produto hash[], int id);

void imprimirAberto(Produto hash[]);

void removerAberto(Produto hash[], int id);

#endif