#include "automata.h"
#include "parser.h"
#include "state.h"

int charmapColumn(char character) {
    if (character >= '0' && character <= '9') return character - '0';
    if (character >= 'a' && character <= 'z') return character - 'a' + 10; 
    if (character >= 'A' && character <= 'Z') return character - 'A' + 36;
    if (character == ';') return 62;
    if (character == ',') return 63;
    if (character == ':') return 64;
    if (character == '.') return 65;
    if (character == '[') return 66;
    if (character == ']') return 67;
    if (character == '(') return 68;
    if (character == ')') return 69;
    if (character == '=') return 70;
    if (character == '>') return 71;
    if (character == '<') return 72;
    if (character == '+') return 73;
    if (character == '-') return 74;
    if (character == '*') return 75;
    if (character == '/') return 76;
    if (character == '_') return 77;
    if (character == '\"') return 78;
    if (character == '{') return 79;
    if (character == '}') return 80;
    if (character == '\n') return 81;  
    if (character == ' ') return 82;   
    if (character == '!') return 83;
    if (character == '?') return 84;
    if (character == '#') return 85;
    if (character == '@') return 86;
    if (character == '$') return 87;
    if (character == '&') return 88;
    if (character == '%') return 89;
    if (character == '|') return 90;
    return -1; 
}

bool isFinal(int current) {
    for (int i = 0; i < NUM_FINAL_STATES; i++) {
        if (FINAL_STATES[i] == current) return true;
    }
    return false;
}

void resetVariables(int *index, int indexToSet, int *backupIndex, int *end, int *currentState) {
    *index = indexToSet;
    *backupIndex = *index;
    *end = -1;
    *currentState = 1;
}

void printErroLexico(void *cadeia, char *input, int line, int column, bool *textBefore, bool *flagLexico, char *tokenContents) {
    if (*flagLexico) return;
    if (input[column] == 10 || input[column] == 32) return;
    if (*textBefore) printf("\n");
    printf("ERRO LEXICO. Linha: %d Coluna: %d -> '%c'", line, column + 1, input[column]);
    freeList(cadeia);
    free(input);
    free(tokenContents);
    *textBefore = true;
    *flagLexico = true;
    exit(-1);
}