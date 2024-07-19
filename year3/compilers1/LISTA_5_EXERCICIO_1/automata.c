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
    if (character == '+') return 0;
    if (character == '-') return 1;
    if (character >= '0' && character <= '9') return 2 + (character - '0');
    if (character >= 'a' && character <= 'z') return 12 + (character - 'a');
    if (character == '\n') return 38;
    return -1;
}

int transition(int current_state, char character, int edges[][39]) {
    int index = charmapColumn(character);
    return (index == -1) ? -1 : edges[current_state][index];
}

void acceptAction(char *current_input, int accept_length) {
    if (accept_length > 0) {
        char aux = current_input[accept_length];
        current_input[accept_length] = '\0';
        printf("%s\n", current_input);
        current_input[accept_length] = aux;
    }
}