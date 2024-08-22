#ifndef AUTOMATA_H
#define AUTOMATA_H

typedef enum tokenType {
    DOLLAR,
    PLUS,
    TIMES,
    L_PAREN,
    R_PAREN,
    ID,
    NEW_LINE,
    EOF_TOKEN   
} tokenType;

int isFinalState(int state);

int charmapColumn(char character);

int transition(int currentState, char character);

int getFinalStateTokenType(int finalState, char currentChar);

int getNextToken();

#endif