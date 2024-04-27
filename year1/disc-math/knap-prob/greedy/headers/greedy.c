#include "greedy.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int greedy(Item *item, int num_item, int peso, char *ordenacao)
{
    if (strcmp(ordenacao, "weight") == 0)
        quicksortPeso(item, num_item);
    else if (strcmp(ordenacao, "value") == 0)
        quicksortValor(item, num_item);
    else if (strcmp(ordenacao, "ratio") == 0)
        quicksortRazao(item, num_item);
    else
    {
        fprintf(stderr, "Ordenacao invalida!\n");
        exit(EXIT_FAILURE);
    }

    int sol = 0;
    for (int i = 0; i < num_item; i++)
        if (item[i].peso <= peso)
        {
            sol += item[i].valor;
            peso -= item[i].peso;
        }
    return sol;
}

void heuristica(int argc, char **argv, FILE *file)
{
    Item *item;
    int num_item, peso, sol;
    clock_t begin_clock, end_clock;
    lerArquivo(argc, argv[1], &num_item, &peso, &item);
    fprintf(file, "Capacidade: %d\n", peso);
    begin_clock = clock();
    sol = greedy(item, num_item, peso, argv[2]);
    end_clock = clock();
    fprintf(file, "Solucao: %d\n", sol);
    fprintf(file, "Tempo de execucao: %fs\n", (double)(end_clock - begin_clock) / CLOCKS_PER_SEC);
    free(item);
}