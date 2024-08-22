#ifndef PARSER_H
#define PARSER_H
#include "automata.h"

typedef enum TokenType {
    ID = 2,
    NUM_INT = 3,
    NUM_REAL = 4,
    PONTO_VIRGULA = 5,
    VIRGULA = 6,
    DOIS_PONTOS = 7,
    PONTO = 8,
    ABRE_COLCHETE = 9,
    FECHA_COLCHETE = 10,
    ABRE_PARENTESES = 11,
    FECHA_PARENTESES = 12,
    IGUAL = 13,
    MAIOR = 14,
    MENOR = 15,
    MAIS = 16,
    MENOS = 17,
    VEZES = 18,
    DIVISAO = 19,
    ALGORITMO = 28,
    ATE = 30,
    DIFERENTE = 31,
    MAIOR_IGUAL = 32,
    MENOR_IGUAL = 33,
    ATRIBUICAO = 34,
    INICIO = 40,
    IMPRIMA = 46,
    FIM = 49,
    FUNCAO = 54,
    FACA = 57,
    FALSO = 60,
    VARIAVEIS = 69,
    VETOR = 73,
    VERDADEIRO = 81,
    INTEIRO = 86,
    REAL = 90,
    REPITA = 94,
    SE = 96,
    SENAO = 99,
    AND = 100,
    ENTAO = 104,
    ENQUANTO = 110,
    DE = 112,
    DIV = 114,
    OU = 116,
    NAO = 119,
    TIPO = 123,
    LEIA = 127,
    LOGICO = 132,
    MATRIZ = 138,
    CARACTERE = 147,
    PARA = 151,
    PASSO = 154,
    PROCEDIMENTO = 165,
    COMENT_LINHA = 166,
    STRING = 168,
    COMENT_BLOCO = 170,
    EOF_TOKEN = 171
} TokenType;

void AL(void *cadeia, int *tk, bool *textBefore, char *input);     

void PF(void *cadeia, int *tk, bool *textBefore, char *input);    

void DProc(void *cadeia, int *tk, bool *textBefore, char *input);     

void DF(void *cadeia, int *tk, bool *textBefore, char *input);        

void Param(void *cadeia, int *tk, bool *textBefore, char *input);     

void DParam(void *cadeia, int *tk, bool *textBefore, char *input);    

void BV(void *cadeia, int *tk, bool *textBefore, char *input);      

void DS(void *cadeia, int *tk, bool *textBefore, char *input);         

void DT(void *cadeia, int *tk, bool *textBefore, char *input);        

void DV(void *cadeia, int *tk, bool *textBefore, char *input);        

void DI(void *cadeia, int *tk, bool *textBefore, char *input);        

void VM(void *cadeia, int *tk, bool *textBefore, char *input);        

void DM(void *cadeia, int *tk, bool *textBefore, char *input);     

void TB(void *cadeia, int *tk, bool *textBefore, char *input);        

void BC(void *cadeia, int *tk, bool *textBefore, char *input);       

void LC(void *cadeia, int *tk, bool *textBefore, char *input);      

void C(void *cadeia, int *tk, bool *textBefore, char *input);       

void E(void *cadeia, int *tk, bool *textBefore, char *input);      

void ES(void *cadeia, int *tk, bool *textBefore, char *input);      

void OPR(void *cadeia, int *tk, bool *textBefore, char *input);   

void OPB(void *cadeia, int *tk, bool *textBefore, char *input);   

void T(void *cadeia, int *tk, bool *textBefore, char *input);     

void F(void *cadeia, int *tk, bool *textBefore, char *input);    

void V(void *cadeia, int *tk, bool *textBefore, char *input);      

void EI(void *cadeia, int *tk, bool *textBefore, char *input);    

void defineID(int *tk);

#endif