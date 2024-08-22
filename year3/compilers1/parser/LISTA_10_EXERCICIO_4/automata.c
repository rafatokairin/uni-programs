#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automata.h"
#include "state.h"

int isFinalState(int state) {
    for (int i = 0; i < NUM_FINAL_STATES; i++)
        if (FINAL_STATES[i] == state) return 1;
    return 0;
}

int charmapColumn(char character){ 
    if(character == '$') return 0;
    else if(character == '+') return 1;
    else if(character == '*') return 2;
    else if(character == '(') return 3;
    else if(character == ')') return 4;
    else if(character >= 'a' && character <= 'z') return (4 + (character - 96));
    else if(character >= '0' && character <= '9') return (30 + (character - 47));  
    else if(character == '\n') return 41;
    else return 42;
}

int transition(int currentState, char character){
    int index = charmapColumn(character);
    return edges[currentState][index];
}

int getFinalStateTokenType(int finalState, char currentChar){
    if (finalState == 0) return currentChar;  
    else return finalState - 2;
}

int getNextToken(){
    int lastFinalState = 0;
    int currentState = INITIAL_STATE;
    int acceptingCursor = 0;
    int readingCursor = 0;
    char currentChar;

    while(1){ 
        if(fread(&currentChar, 1, 1, stdin) != 1){ 
            if(readingCursor == 0) 
                return EOF_TOKEN;
            int offset = readingCursor - acceptingCursor;
            if(acceptingCursor == 0) 
                offset--;
            fseek(stdin, -offset, SEEK_CUR);
            return getFinalStateTokenType(lastFinalState, currentChar);
        }

        readingCursor++;
        currentState = transition(currentState, currentChar);
        if(currentState == 0){ 
            int offset = readingCursor - acceptingCursor;
            if(acceptingCursor == 0){
                if(readingCursor == 1 && (currentChar == ' '))
                    return getNextToken(); 
                else 
                    offset--;
            } 
            fseek(stdin, -offset, SEEK_CUR);
            return getFinalStateTokenType(lastFinalState, currentChar);
        }
        else if(isFinalState(currentState)){ 
            lastFinalState = currentState;
            acceptingCursor = readingCursor;
        }
    }
}