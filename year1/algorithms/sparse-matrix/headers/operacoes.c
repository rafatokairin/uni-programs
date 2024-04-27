#include "esparsa.h"
#include "operacoes.h"
#include <stdio.h>
#include <stdlib.h>

void operacoes(Matriz *A, Matriz *B, Matriz *C)
{
    printf("Matriz A condensada:\n");
    info(A);
    printf("\nSoma abaixo diagonal principal matriz A: %d\n", somaAbaixoDiag(A));
    printf("\nMatriz A completa:\n");
    imprimir(A);
    printf("Matriz B condensada:\n");
    info(B);
    printf("\nSoma abaixo diagonal principal matriz B: %d\n", somaAbaixoDiag(B));
    printf("\nMatriz B completa:\n");
    imprimir(B);
    printf("Soma matriz A e B:\n");
    somar(A, B, C);
    info(C);
    printf("\nSoma abaixo diagonal principal soma: %d\n", somaAbaixoDiag(C));
    reiniciar(C);
    printf("\nMultiplicacao matriz A e B:\n");
    multiplicar(A, B, C);
    info(C);
    printf("\nSoma abaixo diagonal principal multiplicacao: %d\n", somaAbaixoDiag(C));
    reiniciar(A); reiniciar(B); reiniciar(C);
}

void lerMatrizes(Matriz *A, Matriz *B)
{
    int valor;
    FILE *arquivo = fopen("../compile/matrizes.txt", "r");
    // le matriz A
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
        {
            fscanf(arquivo, "%d", &valor);
            if (valor != 0)
                inserir(A, valor, i, j);
        }
    // le matriz B
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
        {
            fscanf(arquivo, "%d", &valor);
            if (valor != 0)
                inserir(B, valor, i, j);
        }
    fclose(arquivo);
}