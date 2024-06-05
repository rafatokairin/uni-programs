#ifndef CADASTRO_H
#define CADASTRO_H
#define TAM 31
extern int cont;

typedef struct {
    int id;
    char descricao[20];
    float preco;
} Produto;

typedef struct No {
    Produto prod;
    struct No *prox;
} No;

typedef struct {
    No *ini;
} Lista;

Produto cadastrarProduto(int id, char *descricao, float preco);
void menu(Lista *tabelaSeparada, Produto *tabelaAberta);

#endif
