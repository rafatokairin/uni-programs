#ifndef UTILS_H
#define UTILS_H
#include "parser.h"

void eat(void *cadeia, bool *textBefore, char *input);

void getToken(void *cadeia, int tokenAnalisado, int *tk, bool *textBefore, char *input);

void printResult(char *result, bool *textBefore);

void printError(void *cadeia);

void Start(void *cadeia, int *tk, bool *textBefore, char *input); 

void DSrec(void *cadeia, int *tk, bool *textBefore, char *input);

void DIrec(void *cadeia, int *tk, bool *textBefore, char *input);

void DMrec(void *cadeia, int *tk, bool *textBefore, char *input);

void LCrec(void *cadeia, int *tk, bool *textBefore, char *input);

void Crec1(void *cadeia, int *tk, bool *textBefore, char *input);

void Crec2(void *cadeia, int *tk, bool *textBefore, char *input);

void Crec3(void *cadeia, int *tk, bool *textBefore, char *input);

void Erec(void *cadeia, int *tk, bool *textBefore, char *input);

void ESrec(void *cadeia, int *tk, bool *textBefore, char *input);

void Trec(void *cadeia, int *tk, bool *textBefore, char *input);

void Frec(void *cadeia, int *tk, bool *textBefore, char *input);

void Vrec(void *cadeia, int *tk, bool *textBefore, char *input);

void EIrec(void *cadeia, int *tk, bool *textBefore, char *input);

void parse();

#endif