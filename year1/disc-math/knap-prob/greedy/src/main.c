#include "../headers/item.h"
#include "../headers/greedy.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 3)
        exit(EXIT_FAILURE);
    FILE *file = stdout;
    heuristica(argc, argv, file);
    if (file != stdout)
        fclose(file);
    exit(EXIT_SUCCESS);
}