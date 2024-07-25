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

int charmapColumn(char character) {
    if (character == ' ') return 0;
    if (character >= 'a' && character <= 'z') return character - 'a' + 1;
    if (character >= '0' && character <= '9') return character - '0' + 27;
    if (character == '.') return 37;
    if (character == '-') return 38;
    if (character == '\n') return 39;
    return 40;
}

int transition(int current_state, char character, int edges[][41]) {
    int index = charmapColumn(character);
    return (index == -1) ? -1 : edges[current_state][index];
}

void acceptAction(char *current_input, int accept_length, int last_final) {
    if (accept_length > 0) {
        char aux = current_input[accept_length];
        current_input[accept_length] = '\0';

        if (last_final == 2 || last_final == 4) 
            printf("%s ID", current_input);
        else if (last_final == 3)
            printf("IF");
        else if (last_final == 5 || last_final == 9 || last_final == 13)
            printf("%s error", current_input);
        else if (last_final == 6 || last_final == 8)
            printf("%s REAL", current_input);
        else if (last_final == 7)
            printf("%s NUM", current_input);
        else if (last_final == 11) {
            current_input[accept_length - 1] = '\0';
            printf("%s comment", current_input);
            current_input[accept_length - 1] = aux;
        }
        else if (last_final == 12)
            printf("white space");

        current_input[accept_length] = aux;
    }
}