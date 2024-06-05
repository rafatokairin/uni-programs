#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastro.h"
#include "aberto.h"
#include "separado.h"

int cont = 0; // variavel global usando extern para multiplos arquivos

Produto cadastrarProduto(int id, char *descricao, float preco) {
    Produto novo;
    novo.id = id;
    strcpy(novo.descricao, descricao);
    novo.preco = preco;
    return novo;
}

void menu(Lista *tabelaSeparada, Produto *tabelaAberta) {
    int opcao, id;
    char descricao[20];
    float preco;

    do {
        printf("\n1. Inserir\n2. Buscar\n3. Remover\n4. Imprimir Hash com Encadeamento Separado\n5. Imprimir Hash com Encadeamento Aberto\n6. Sair\n");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                if (cont < TAM) {
                    printf("Digite o ID:\n");
                    scanf("%d", &id);
                    printf("Digite a descricao:\n");
                    scanf("%s", descricao);
                    printf("Digite o preco:\n");
                    scanf("%f", &preco);

                    if (preco < 200) {
                        inserirSeparado(tabelaSeparada, cadastrarProduto(id, descricao, preco));
                        printf("Produto inserido na Tabela Hash com Encadeamento Separado!\n");
                    } else {
                        inserirAberto(tabelaAberta, cadastrarProduto(id, descricao, preco));
                        printf("Produto inserido na Tabela Hash com Encadeamento Aberto!\n");
                    }
                } else {
                    printf("Numero maximo de elementos atingido!\n");
                }
                break;
            case 2:
                printf("Digite o ID:\n");
                scanf("%d", &id);
                {
                    No *indexSeparado = buscarSeparado(tabelaSeparada, id);
                    if (indexSeparado != NULL)
                        printf("Produto encontrado na Tabela Hash com Encadeamento Separado!\n");
                    else {
                        int indexAberto = buscarAberto(tabelaAberta, id);
                        if (indexAberto != -1)
                            printf("Produto encontrado na Tabela Hash com Encadeamento Aberto!\n");
                        else
                            printf("Produto nao encontrado!\n");
                    }
                }
                break;
            case 3:
                printf("Digite o ID:\n");
                scanf("%d", &id);
                removerSeparado(tabelaSeparada, id);
                removerAberto(tabelaAberta, id);
                break;
            case 4:
                printf("\nTabela Hash com Encadeamento Separado:\n");
                imprimirSeparado(tabelaSeparada);
                break;
            case 5:
                printf("\nTabela Hash com Encadeamento Aberto:\n");
                imprimirAberto(tabelaAberta);
                break;
            case 6:
                printf("Finalizando...\n");
                break;
            default:
                break;
        }
    } while (opcao != 6);
    destruirSeparado(tabelaSeparada);
}
