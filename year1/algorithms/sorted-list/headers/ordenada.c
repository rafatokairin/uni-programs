#include "ordenada.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void criar(Lista *p)
{
    p->inicio = NULL;
    p->tam = 0;
}

void imprimir(Lista *p)
{
    No *end = p->inicio;
    while (end != NULL)
    {
        printf("%d ", end->chave);
        end = end->prox;
    }
    printf("\n");
}

No *buscarOrd(Lista *p, No **ant, int chave)
{
    *ant = NULL;
    No *atual = p->inicio;
    while (atual != NULL && atual->chave < chave)
    {
        *ant = atual;
        atual = atual->prox;
    }
    if (atual != NULL && atual->chave == chave)
        return atual;
    return NULL;
}

bool inserirOrd(Lista *p, int chave)
{
    No *ant, *novo = buscarOrd(p, &ant, chave);
    if (novo != NULL)
        return false;
    novo = (No *)malloc(sizeof(No));
    novo->chave = chave;
    if (ant == NULL)
    {
        novo->prox = p->inicio;
        p->inicio = novo;
    }
    else
    {
        novo->prox = ant->prox;
        ant->prox = novo;
    }
    p->tam++;
    return true;
}

bool remover(Lista *p, int chave)
{
    No *ant, *rmv = buscarOrd(p, &ant, chave);
    if (rmv == NULL)
        return false;
    if (ant == NULL)
        p->inicio = rmv->prox;
    else
        ant->prox = rmv->prox;
    free(rmv);
    p->tam--;
    return true;
}

void reiniciar(Lista *p)
{
    No *end = p->inicio;
    while (end != NULL)
    {
        No *ant = end;
        end = end->prox;
        free(ant);
    }
    p->inicio = NULL;
}

void inverter(Lista *p)
{
    No *ant = NULL;
    No *prox, *atual = p->inicio;
    while (atual != NULL)
    {
        prox = atual->prox;
        atual->prox = ant;
        ant = atual;
        atual = prox;
    }
    p->inicio = ant;
}

void menu(Lista *p)
{
    int opcao, chave;
    No *ant;
    do
    {
        printf("\n1. Quantidade\n2. Exibir\n3. Buscar\n4. Inserir\n5. Excluir\n6. Reiniciar\n7. Inverter e sair\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("Tamanho da lista: %d\n", p->tam);
            break;
        case 2:
            imprimir(p);
            break;
        case 3:
            printf("Digite um valor:\n");
            scanf("%d", &chave);
            buscarOrd(p, &ant, chave);
            break;
        case 4:
            printf("Digite um valor:\n");
            scanf("%d", &chave);
            if (inserirOrd(p, chave) == true)
                printf("Inserido!\n");
            else
                printf("ERRO! Insira outro valor\n");
            break;
        case 5:
            printf("Digite um valor:\n");
            scanf("%d", &chave);
            if (remover(p, chave) == true)
                printf("Removido!\n");
            else
                printf("ERRO! Insira outro valor\n");
            break;
        case 6:
            reiniciar(p);
            break;
        case 7:
            inverter(p);
            imprimir(p);
            printf("\nFinalizando...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 7);
}