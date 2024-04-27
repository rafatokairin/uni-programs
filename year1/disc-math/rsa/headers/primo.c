#include "primo.h"

bool ehPrimo(int num)
{
    if (num < 2) 
        return false;
    for (int i = 2; i <= num / 2; i++)
        if (num % i == 0)
            return false;
    return true;
}

int geraPrimo(int valor_min, int valor_max)
{
    int primo = rand() % (valor_max - valor_min + 1) + valor_min;
    while (!ehPrimo(primo))
        primo = rand() % (valor_max - valor_min + 1) + valor_min;
    return primo;
}