#ifndef ESPARSA_INCLUDED
#define ESPARSA_INCLUDED

#define TAM 15

typedef struct no {
    int valor, col;
    struct no *prox;
} No;

typedef struct {
    No **arranjo;
    int lin, col;
} Matriz;

Matriz multiplicar(Matriz *, Matriz *, Matriz *);

Matriz somar(Matriz *, Matriz *, Matriz *);

void inserir(Matriz *, int, int, int);

void reiniciar(Matriz *);

void imprimir(Matriz *);

void criar(Matriz *);

void info(Matriz *);

int buscarValor(Matriz *, int, int);

int somaAbaixoDiag(Matriz *);

#endif