#include "phi_n.h"

uint64_t mdc(uint64_t a, uint64_t b)
{
    uint64_t temp;
    while (b != 0)
    {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

uint64_t coprimo(uint64_t phi)
{
    uint64_t e;
    srand(time(NULL));
    do {
        e = rand() % (phi - 3) + 3;
    } while (mdc(e, phi) != 1);
    return e;
}

uint64_t inversoMod(uint64_t e, uint64_t phi)
{
    for (uint64_t d = 3; d < phi; d++)
        if ((e * d) % phi == 1) 
            return d;
    exit(EXIT_FAILURE);
}