#ifndef PARSER_H
#define PARSER_H

char* getToken(int tokenType);

void printNewLine();

void printError(int readToken, char* expectedToken);

void ignoreString();

void advance();

void eat(int t);

void L();

void E();

int parse();

#endif