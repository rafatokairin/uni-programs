#include "rb_aux.h"
#include "rb.h"

void printDOT(FILE *dotFile, Raiz *T, No *z)
{
    if (z != T->nil) 
    {
        if (z->cor == RED)
            fprintf(dotFile, "%d [fontcolor=white, fillcolor=red, style=filled];\n", z->chave);
        else
            fprintf(dotFile, "%d [fontcolor=white, fillcolor=black, style=filled];\n", z->chave);

        if (z->esquerda != T->nil) 
        {
            fprintf(dotFile, "%d -> %d;\n", z->chave, z->esquerda->chave);
            printDOT(dotFile, T, z->esquerda);
        }
        if (z->direita != T->nil) 
        {
            fprintf(dotFile, "%d -> %d;\n", z->chave, z->direita->chave);
            printDOT(dotFile, T, z->direita);
        }
    }
}

void gerarDot(Raiz *T, const char *filename)
{
    FILE *dotFile = fopen(filename, "w");
    if (dotFile == NULL) 
    {
        printf("ERRO ao abrir DOT!\n");
        return;
    }
    fprintf(dotFile, "digraph Tree {\n");
    printDOT(dotFile, T, T->raiz);
    fprintf(dotFile, "}\n");
    fclose(dotFile);
}

No* buscar(Raiz *T, No* z, int chave, int *cmp) 
{
    if (z == T->nil || z->chave == chave) 
    {
        (*cmp)++;
        return z;
    }
    (*cmp)++;
    if (chave < z->chave)
        return buscar(T, z->esquerda, chave, cmp);
    else
        return buscar(T, z->direita, chave, cmp);
}

void calcAltura(Raiz *T, No* z, int *altura, int *altura_b)
{
    int altura_L, altura_R, altura_b_L, altura_b_R;
    if (z == T->nil)
    {
        *altura = 0;
        *altura_b = 0;
        return;
    }
    calcAltura(T, z->esquerda, &altura_L, &altura_b_L);
    calcAltura(T, z->direita, &altura_R, &altura_b_R);
    if (altura_L > altura_R)
        *altura = 1 + altura_L;
    else
        *altura = 1 + altura_R;
    if (z->cor == BLACK)
    {
        if (altura_b_L > altura_b_R)
            *altura_b = 1 + altura_b_L;
        else
            *altura_b = 1 + altura_b_R;
    }
    else
    {
        if (altura_b_L > altura_b_R)
            *altura_b = altura_b_L;
        else 
            *altura_b = altura_b_R;
    }
}

void contarRB(Raiz *T, No* z, int* rubro, int* negro) 
{
    if (z == T->nil) return;
    if (z->cor == RED) (*rubro)++;
    else (*negro)++;
    contarRB(T, z->esquerda, rubro, negro);
    contarRB(T, z->direita, rubro, negro);
}

void percRB(Raiz* T) 
{
    int rubro = 0, negro = 0;
    contarRB(T, T->raiz, &rubro, &negro);
    int total = rubro + negro;
    double perc_rubro = (double)rubro / total * 100;
    double perc_negro = (double)negro / total * 100;
    printf("Porcentagem RUBRO: %.2lf; Porcentagem NEGRO: %.2lf;\n", perc_rubro, perc_negro);
}

void menu(Raiz* T)
{
    int opcao, chave, cmp = 0, altura = 0, altura_b = 0;
    do
    {
        printf("\n1. Inserir\n2. Imprimir Ordem\n3. Buscar\n4. Infos\n5. Remover\n6. Sair\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("Digite um valor:\n");
            scanf("%d", &chave);
            inserir(T, criar(T, chave));
            gerarDot(T, "rbTree.dot");
            break;
        case 2:
            imprimir(T, T->raiz);
            break;
        case 3:
            printf("Digite um valor:\n");
            scanf("%d", &chave);
            No* busca = buscar(T, T->raiz, chave, &cmp);
            printf(busca != T->nil ? "Encontrado! Comparacoes: %d\n" : "Nao encontrado! Comparacoes: %d\n", cmp);
            break;
        case 4:
            percRB(T);
            calcAltura(T, T->raiz, &altura, &altura_b);
            printf("Altura: %d; Altura NEGRA: %d;\n", altura, altura_b);
            break;
        case 5:
            printf("Digite um valor:\n");
            scanf("%d", &chave);
            remover(T, T, chave);
            gerarDot(T, "rbTree.dot");
            break;
        case 6:
            destruirArvore(T);
            printf("Finalizando...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 6);
}