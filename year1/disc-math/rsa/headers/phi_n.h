#ifndef PHI_N_INCLUDED
#define PHI_N_INCLUDED
#include <time.h>
#include <stdint.h>
#include <stdlib.h>

// calcula maximo divisor comum
uint64_t mdc(uint64_t a, uint64_t b);

uint64_t coprimo(uint64_t phi);

uint64_t inversoMod(uint64_t e, uint64_t phi);

#endif