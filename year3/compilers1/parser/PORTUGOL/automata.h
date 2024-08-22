#ifndef AUTOMATA_H
#define AUTOMATA_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

int charmapColumn(char character);

bool isFinal(int current);

void resetVariables(int *index, int indexToSet, int *backupIndex, int *end, int *currentState);

void printErroLexico(void *cadeia, char *input, int line, int column, bool *textBefore, bool *flagLexico, char *tokenContents);

#endif