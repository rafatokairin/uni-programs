#include "criptografa.h"

uint64_t powMod(uint64_t base, uint64_t exp, uint64_t modulo)
{
    uint64_t resultado = 1;
    // reduz o expoente pela metade em cada iteracao
    while (exp > 0)
    {
        // se o bit menos significativo do expoente for 1, multiplica o resultado com a base
        if (exp & 1)
            resultado = (resultado * base) % modulo;
        // eleva a base ao quadrado e calcula o modulo
        base = (base * base) % modulo;
        // divide o expoente por 2 (desloca para a direita)
        exp >>= 1;
    }
    return resultado;
}

void criptografa(char *senha, uint64_t *senha_cript, uint64_t e, uint64_t n)
{
    for (int i = 0; i < strlen(senha); i++)
    {
        senha_cript[i] = powMod((int)senha[i], e, n);
        printf("%lu ", senha_cript[i]);
    }
}

void descriptografa(uint64_t *senha_cript, uint64_t d, uint64_t n, int tamanho)
{
    int senha_descript[tamanho];
    for (int i = 0; i < tamanho; i++)
    {
        senha_descript[i] = powMod(senha_cript[i], d, n);
        printf("%c", senha_descript[i]);
    }
}
