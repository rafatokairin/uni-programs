#ifndef CRIPTOGRAFA_INCLUDED
#define CRIPTOGRAFA_INCLUDED
#define MAX_SENHA 8
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// calcula (base^exp) % modulo
uint64_t powMod(uint64_t, uint64_t, uint64_t);

void criptografa(char *, uint64_t *, uint64_t, uint64_t);

void descriptografa(uint64_t *, uint64_t, uint64_t, int);

#endif