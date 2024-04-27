#include "../headers/extenso.h"
#include <stdio.h>

int main()
{
    double valor;
    printf("Digite um numero (0. Sair): ");
    scanf("%lf", &valor);
    while (valor != 0)
    {
        extenso(valor);
        printf("Digite um numero (0. Sair): ");
        scanf("%lf", &valor);
    }
    return 0;
}