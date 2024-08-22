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
    if(character == '+') return 0;
    else if(character == '-') return 1;
    else if(character >= '0' && character <= '9') return (1 + (character - 47));
    else if(character == '=') return 12;
    else if(character == ';') return 13;
    else if(character >= 'd' && character <= 'i') return (13 + (character - 99));  
    else if(character == 't') return 20;
    else if(character == 'n') return 21;
    else if(character == 'l') return 22;
    else if(character == 's') return 23;
    else if(character == 'b') return 24;
    else if(character == 'p') return 25;
    else if(character == 'r') return 26;
    else if(character == '\n') return 27;
    else return 28;
}

int transition(int current_state, char character){
    int index = charmapColumn(character);
    return edges[current_state][index];
}

tokenType getFinalStateTokenType(int finalState){
    if (finalState == 0) return ERROR;  
    else return finalState - 19;
}

tokenType getNextToken(){
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
            return getFinalStateTokenType(lastFinalState);
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
            return getFinalStateTokenType(lastFinalState);
        }
        else if(isFinalState(currentState)){
            lastFinalState = currentState;
            acceptingCursor = readingCursor;
        }
    }
}