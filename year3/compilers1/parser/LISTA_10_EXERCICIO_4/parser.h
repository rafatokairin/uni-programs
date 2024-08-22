#ifndef PARSER_H
#define PARSER_H
#include "state.h"
#include "queue.h"
#include "automata.h"

void cleanQueue();

char* getToken(int tokenType);

void printNewLine();

void printLexicalError(char character);

void printSyntaxError(int readToken, char* expectedToken);

void ignoreString();

void advance();

int getProduction(char nonT, int T);

int match();

void derive(int matchWasSuccessful);

void queuePushToken(int token);

void S();

void E();

void Ef();

void T();

void Tf();

void F();

int parse();

#endif