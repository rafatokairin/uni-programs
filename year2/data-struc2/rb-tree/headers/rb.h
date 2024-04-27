#ifndef RB_INCLUDED
#define RB_INCLUDED

enum type {
    RED, BLACK
};

typedef struct no {
    enum type cor;
    int chave;
    struct no *direita;
    struct no *esquerda;
    struct no *p;
} No;

typedef struct {
    No *raiz;
    No *nil;
} Raiz;

No *criar(Raiz *T, int chave);
void rotacaoL(Raiz *T, No *x);
void rotacaoR(Raiz *T, No *x);
void inserirFixup(Raiz* T, No* z);
void inserir(Raiz* T, No* z);
void removerFixup(Raiz * T, No *x);
void remover(Raiz  *T, Raiz *auxT, int chave);
void imprimir(Raiz *T, No *z);
void destruirAux(Raiz *T, No *z);
void destruirArvore(Raiz *T);

#endif