#include <stdio.h>
#include <stdlib.h>

enum type {
    MIN, MAX
};

typedef struct {
    int pid;
    int prioridade;
    int tempoEspera;
} Processo;

void novoProcesso(Processo *proc, int* pid, int prioridade, int tempoEspera) 
{
    proc->pid = *pid;
    proc->prioridade = prioridade;
    proc->tempoEspera = tempoEspera;
    (*pid)++;
}

void substituir(Processo *a, Processo *b) 
{
    Processo x = *a;
    *a = *b;
    *b = x;
}

int heapVazio(int tam) 
{
    return (tam <= 0) ? 1 : 0;
}

void subirMax(Processo *heap, int i) 
{
    int pai = i / 2;
    if (pai >= 1) 
    {
        if (heap[i].prioridade > heap[pai].prioridade) 
        {
            substituir(&heap[i], &heap[pai]);
            subirMax(heap, pai);
        }
    }
}

void subirMin(Processo *heap, int i) 
{
    int pai = i / 2;
    if (pai >= 1) 
    {
        if (heap[i].tempoEspera < heap[pai].tempoEspera) 
        {
            substituir(&heap[i], &heap[pai]);
            subirMin(heap, pai);
        }
    }
}

void descerMax(Processo *heap, int i, int tam) 
{
    int maior = i;
    int esquerda = 2 * i;
    int direita = 2 * i + 1;

    if (esquerda <= tam && heap[esquerda].prioridade > heap[maior].prioridade)
        maior = esquerda;

    if (direita <= tam && heap[direita].prioridade > heap[maior].prioridade)
        maior = direita;

    if (maior != i) 
    {
        substituir(&heap[i], &heap[maior]);
        descerMax(heap, maior, tam);
    }
}

void descerMin(Processo *heap, int i, int tam) 
{
    int menor = i;
    int esquerda = 2 * i;
    int direita = 2 * i + 1;

    if (esquerda <= tam && heap[esquerda].tempoEspera < heap[menor].tempoEspera)
        menor = esquerda;

    if (direita <= tam && heap[direita].tempoEspera < heap[menor].tempoEspera)
        menor = direita;

    if (menor != i) 
    {
        substituir(&heap[i], &heap[menor]);
        descerMin(heap, menor, tam);
    }
}

void inserirProcesso(Processo **heap, Processo novo, int* tam, int tipo) 
{
    *tam += 1;
    *heap = (Processo *)realloc(*heap, sizeof(Processo) * (*tam + 1));
    (*heap)[*tam] = novo;

    if (tipo == MAX)
        subirMax(*heap, *tam);
    else    
        subirMin(*heap, *tam);
}

Processo removerProcessoTopo(Processo *heap, int *tam, int tipo) 
{
    Processo removido = heap[1];
    heap[1] = heap[*tam];
    *tam -= 1;
    if (tipo == MAX)
        descerMax(heap, 1, *tam);
    else    
        descerMin(heap, 1, *tam);

    return removido;
}

void imprimirProcesso(Processo *heapMax, Processo *heapMin, int tamMax, int tamMin) 
{
    printf("\nPrioridade:\nHeapMax:\n");
    for(int i = 1; i <= tamMax; i++) 
        printf("%d ", heapMax[i].prioridade);
    
    printf("\nHeapMin:\n");
    for(int i = 1; i <= tamMin; i++) 
        printf("%d ", heapMin[i].tempoEspera);

    printf("\n");
}

void construirHeapMax(Processo *heap, int tam) 
{
    int j = tam / 2;
    for (int i = j; i >= 1; i--)
        descerMax(heap, i, tam);
}

void construirHeapMin(Processo *heap, int tam) 
{
    int j = tam / 2;
    for (int i = j; i >= 1; i--)
        descerMin(heap, i, tam);
}

int main() 
{
    int tamMax = 0, tamMin = 0, pid = 1;
    Processo proc;
    Processo *heapMax = (Processo *)malloc(sizeof(Processo) * 1);
    Processo *heapMin = (Processo *)malloc(sizeof(Processo) * 1);

    int opcao, prioridade, tempoEspera;
    do
    {
        printf("\n1. Inserir\n2. Remover\n3. Imprimir\n4. Sair\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("Digite prioridade e tempo espera:\n");
            scanf("%d %d", &prioridade, &tempoEspera);
            novoProcesso(&proc, &pid, prioridade, tempoEspera);
            inserirProcesso(&heapMax, proc, &tamMax, MAX);
            inserirProcesso(&heapMin, proc, &tamMin, MIN);
            break;
        case 2:
            if (!heapVazio(tamMax)) {
                Processo removidoMax = removerProcessoTopo(heapMax, &tamMax, MAX);
                printf("\nProcesso removido do HeapMax:\nPrioridade: %d\n", removidoMax.prioridade);
            } else {
                printf("\nHeapMax está vazio.\n");
            }
            if (!heapVazio(tamMin)) {
                Processo removidoMin = removerProcessoTopo(heapMin, &tamMin, MIN);
                printf("Processo removido do HeapMin:\nTempo de Espera: %d\n", removidoMin.tempoEspera);
            } else {
                printf("HeapMin está vazio.\n");
            }
            break;
        case 3:
            imprimirProcesso(heapMax, heapMin, tamMax, tamMin);
            break;
        case 4:
            printf("Finalizando...\n");
            free(heapMax);
            free(heapMin);
            break;
        default:
            break;
        }
    } while (opcao != 4);
    return 0;
}