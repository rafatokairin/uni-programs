#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

No *criar(Raiz *T, int chave) 
{
    No *novo = (No *)malloc(sizeof(No));
    novo->chave = chave;
    novo->esquerda = T->nil;
    novo->direita = T->nil;
    novo->p = T->nil;
    novo->cor = RED;
    return novo;
}

void rotacaoL(Raiz *T, No *x) 
{
    No *y = x->direita;
    x->direita = y->esquerda;
    if (y->esquerda != T->nil)
        y->esquerda->p = x;
    y->p = x->p;
    if (x->p == T->nil)
        T->raiz = y;
    else if (x == x->p->esquerda)
        x->p->esquerda = y;
    else
        x->p->direita = y;
    y->esquerda = x;
    x->p = y;
}

void rotacaoR(Raiz *T, No *x) 
{
    No *y = x->esquerda;
    x->esquerda = y->direita;
    if (y->direita != T->nil)
        y->direita->p = x;
    y->p = x->p;
    if (x->p == T->nil)
        T->raiz = y;
    else if (x == x->p->direita)
        x->p->direita = y;
    else
        x->p->esquerda = y;
    y->direita = x;
    x->p = y;
}

void inserirFixup(Raiz* T, No* z)
{
    while (z != T->raiz && z->p->cor == RED)
    {
        if (z->p == z->p->p->esquerda)
        {
            No* y = z->p->p->direita;
            if (y != T->nil && y->cor == RED)
            {
                z->p->cor = BLACK;
                printf("Pai ficou NEGRO;\n");
                y->cor = BLACK;
                printf("Tio ficou NEGRO;\n");
                z->p->p->cor = RED;
                printf("Avo ficou RUBRO;\n");
                z = z->p->p;
            } 
            else
            {
                if (z == z->p->direita)
                {
                    z = z->p;
                    rotacaoL(T, z);
                    printf("Pai rotacionou ESQUERDA;\n");
                }
                z->p->cor = BLACK;
                printf("Pai ficou NEGRO;\n");
                z->p->p->cor = RED;
                printf("Avo ficou RUBRO;\n");
                rotacaoR(T, z->p->p);
                printf("Avo rotacionou DIREITA;\n");
            }
        } 
        else
        {
            No* y = z->p->p->esquerda;
            if (y != T->nil && y->cor == RED)
            {
                z->p->cor = BLACK;
                printf("Pai ficou NEGRO;\n");
                y->cor = BLACK;
                printf("Tio ficou NEGRO;\n");
                z->p->p->cor = RED;
                printf("Avo ficou RUBRO;\n");
                z = z->p->p;
            } 
            else
            {
                if (z == z->p->esquerda)
                {
                    z = z->p;
                    rotacaoR(T, z);
                    printf("Pai rotacionou DIREITA;\n");
                }
                z->p->cor = BLACK;
                printf("Pai ficou NEGRO;\n");
                z->p->p->cor = RED;
                printf("Avo ficou RUBRO;\n");
                rotacaoL(T, z->p->p);
                printf("Avo rotacionou ESQUERDA;\n");
            }
        }
    }
    T->raiz->cor = BLACK;
    printf("Raiz permanece NEGRA;\n");
}

void inserir(Raiz* T, No* z)
{
    No* y = T->nil;
    No* x = T->raiz;
    while (x != T->nil) 
    {
        y = x;
        if (z->chave < x->chave)
            x = x->esquerda;
        else if (z->chave > x->chave) 
            x = x->direita;
        else
        {
            printf("Valor ja inserido!\n");
            return;
        }
    }
    z->p = y;
    if (y == T->nil) 
    {
        T->raiz = z;
        z->cor = BLACK;
    } 
    else
    {
        if (z->chave < y->chave)
            y->esquerda = z;
        else y->direita = z;
    }
    inserirFixup(T, z);
}

void removerFixup(Raiz * T, No *x) 
{
    while(x != T->raiz && x->cor == BLACK) 
    {
        if(x == x->p->esquerda) 
        {
            No *w = x->p->direita;
            if(w->cor == RED) 
            {
                w->cor = BLACK;
                printf("Irmao ficou NEGRO;\n");
                x->p->cor = RED;
                printf("Pai ficou RUBRO;\n");
                rotacaoL(T, x->p);
                printf("Pai rotacionou ESQUERDA;\n");
                w = x->p->direita;
            }
            if(w != T->nil && (w->esquerda == T->nil || w->esquerda->cor == BLACK) && (w->direita == T->nil || w->direita->cor == BLACK)) 
            {
                printf("Irmao ficou RUBRO;\n");
                w->cor = RED;
                x = x->p;
            }
            else 
            {
                if(w != T->nil && (w->direita == T->nil || w->direita->cor == BLACK)) 
                {
                    w->esquerda->cor = BLACK;
                    printf("Sobrinho ESQUERDO ficou NEGRO;\n");
                    w->cor = RED;
                    printf("Irmao ficou RUBRO;\n");
                    rotacaoR(T, w);
                    printf("Irmao rotacionou DIREITA;\n");
                    w = x->p->direita;
                }
                w->cor = x->p->cor;
                printf("Irmao ficou RUBRO;\n");
                x->p->cor = BLACK;
                printf("Pai ficou NEGRO;\n");
                w->direita->cor = BLACK;
                printf("Sobrinho DIREITO ficou NEGRO;\n");
                rotacaoL(T, x->p);
                printf("Pai rotacionou ESQUERDA;\n");
                x = T->raiz;
            }
        
        } 
        else 
        {
            No *w = x->p->esquerda; 
            if(w->cor == RED) 
            {
                w->cor = BLACK;
                printf("Irmao ficou NEGRO;\n");
                x->p->cor = RED;
                printf("Pai ficou RUBRO;\n");
                rotacaoR(T, x->p);
                printf("Pai rotacionou DIREITA;\n");
                w = x->p->esquerda;
            }
            if(w != T->nil && (w->direita == T->nil || w->direita->cor == BLACK) && (w->esquerda == T->nil || w->esquerda->cor == BLACK)) 
            {
                w->cor = RED;
                printf("Irmao ficou RUBRO;\n");
                x = x->p;
            } 
            else 
            {
                if(w != T->nil && (w->esquerda == T->nil || w->esquerda->cor == BLACK)) 
                {
                    w->direita->cor = BLACK;
                    printf("Sobrinho DIREITO ficou NEGRO;\n");
                    w->cor = RED;
                    printf("Irmao ficou RUBRO;\n");
                    rotacaoL(T, w);
                    printf("Irmao rotacionou ESQUERDA;\n");
                    w = x->p->esquerda;
                }
                w->cor = x->p->cor;
                printf("Irmao ficou RUBRO;\n");
                x->p->cor = BLACK;
                printf("Pai ficou NEGRO;\n");
                w->esquerda->cor = BLACK;
                printf("Sobrinho ESQUERDO ficou NEGRO;\n");
                rotacaoR(T, x->p);
                printf("Pai rotacionou DIREITA;\n");
                x = T->raiz;
            }
        }
    }
    x->cor = BLACK;
} 

void remover(Raiz  *T, Raiz *auxT, int chave) 
{
    No *aux = auxT->raiz;
    if(aux->chave == chave && aux->esquerda == T->nil && aux->direita == T->nil && aux->p == T->nil) 
    {
        free(aux);
        T->raiz = T->nil;
        return;
    }
    while(aux != T->nil && aux->chave != chave) 
    {
        if(chave < aux->chave)   
            aux = aux->esquerda;
        else
            aux = aux->direita;
    }
    if(aux == T->nil) 
    {
        printf("Matricula nao encontrada!\n");
        return;
    }
    if(aux->esquerda == T->nil && aux->direita == T->nil) 
    {
        if(aux->cor == BLACK)
            removerFixup(T, aux);
        
        if(aux == aux->p->esquerda)
            aux->p->esquerda = T->nil;
        else
            aux->p->direita = T->nil;
        free(aux);
    } 
    else 
    {
        No *sucessor;
        Raiz Tsucessor;
        if(aux->esquerda != T->nil) 
        {
            sucessor = aux->esquerda;
            while (sucessor->direita != T->nil)
                sucessor = sucessor->direita;
            aux->chave = sucessor->chave;
            sucessor->chave = chave;
            Tsucessor.raiz = aux->esquerda;
        }
        else 
        {
            sucessor = aux->direita;
            while (sucessor->esquerda != T->nil)
                sucessor = sucessor->esquerda;
            aux->chave = sucessor->chave;
            sucessor->chave = chave;
            Tsucessor.raiz = aux->direita;
        }
        remover(T, &Tsucessor, chave);
    }
}  

void imprimir(Raiz *T, No *z) 
{
    if (z != T->nil) 
    {
        imprimir(T, z->esquerda);
        printf("%d ", z->chave);
        imprimir(T, z->direita);
    }
}

void destruirAux(Raiz *T, No *z)
{
    if (z != T->nil)
    {
        destruirAux(T, z->esquerda);
        destruirAux(T, z->direita);
        free(z);
    }
}

void destruirArvore(Raiz *T)
{
    destruirAux(T, T->raiz);
    free(T->nil);
}