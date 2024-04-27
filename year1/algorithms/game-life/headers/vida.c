#include "vida.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int vizinhos(Matriz M, int i, int j)
{
    int conta = 0;
    if (i - 1 >= 0 && j - 1 >= 0)
        if (M[i - 1][j - 1] >= 1)
            conta++;
    if (i - 1 >= 0)
        if (M[i - 1][j] >= 1)
            conta++;
    if (i - 1 >= 0 && j + 1 < TAM)
        if (M[i - 1][j + 1] >= 1)
            conta++;
    if (j - 1 >= 0)
        if (M[i][j - 1] >= 1)
            conta++;
    if (j + 1 < TAM)
        if (M[i][j + 1] >= 1)
            conta++;
    if (i + 1 < TAM && j - 1 >= 0)
        if (M[i + 1][j - 1] >= 1)
            conta++;
    if (i + 1 < TAM)
        if (M[i + 1][j] >= 1) 
            conta++;
    if (i + 1 < TAM && j + 1 < TAM)
        if (M[i + 1][j + 1] >= 1)
            conta++;
    return conta;
}

void leitura(int argc, char *file_name, Matriz *matriz, Matriz *geracao)
{
    if (argc != 3)
    {
        printf("Quantidade de argumentos invalida!\n");
        exit(1);
    }

    *matriz = (Matriz)calloc(TAM, sizeof(int *));
    *geracao = (Matriz)calloc(TAM, sizeof(int *));
    for (int i = 0; i < TAM; i++)
    {
        (*matriz)[i] = (int *)calloc(TAM, sizeof(int));
        (*geracao)[i] = (int *)calloc(TAM, sizeof(int));
    }

    FILE *quadro = NULL;
    if (!(quadro = fopen(file_name, "r")))
        return;

    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (!feof(quadro))
                fscanf(quadro, "%d", &(*matriz)[i][j]);
    fclose(quadro);
}

void imprimir(Matriz matriz, Matriz geracao, int num_geracao)
{
    for (int qtde_geracao = 0; qtde_geracao < num_geracao; ++qtde_geracao)
    {
        for (int i = 0; i < TAM; ++i)
        {
            for (int j = 0; j < TAM; ++j)
            {
                if (matriz[i][j] == 1)
                    printf("# ");
                else
                    printf(". ");
                // matriz com a respectiva quantidade de vizinhos de cada célula
                geracao[i][j] = vizinhos(matriz, i, j);
            }
            printf("\n");
        }
        printf("\n\n");
        // analisa se a celula vai viver ou morrer de acordo com a quantidade de seus vizinhos
        for (int i = 0; i < TAM; ++i)
        {
            for (int j = 0; j < TAM; ++j)
            {
                if (matriz[i][j] >= 1)
                {
                    if (geracao[i][j] <= 1 || geracao[i][j] >= 4)
                        matriz[i][j] = 0;
                }
                else if (geracao[i][j] == 3)
                    matriz[i][j] = 1;
            }
        }
        sleep(1);
    }
}

void reiniciar(Matriz matriz, Matriz geracao)
{
    for (int i = 0; i < TAM; i++)
    {
        free(matriz[i]);
        free(geracao[i]);
    }
}
