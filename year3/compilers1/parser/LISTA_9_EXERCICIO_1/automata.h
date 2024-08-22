#ifndef AUTOMATA_H
#define AUTOMATA_H

typedef enum tokenType {
    IF,
    THEN,
    ELSE,
    END,
    BEGIN,
    PRINT,
    SEMICOL,
    EQ,
    NUM,
    NEW_LINE,
    ERROR,      
    EOF_TOKEN    
} tokenType;

int isFinalState(int state);

int charmapColumn(char character);

int transition(int current_state, char character);

tokenType getFinalStateTokenType(int finalState);

tokenType getNextToken();

#endif