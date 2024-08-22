#ifndef LEXER_H
#define LEXER_H
#include "state.h"
#include "queue.h"
#include "automata.h"

#define INITIAL_STATE 1
extern const int FINAL_STATES[];
extern const int NUM_FINAL_STATES;
extern int edges[][43];
int getNextToken();

#endif