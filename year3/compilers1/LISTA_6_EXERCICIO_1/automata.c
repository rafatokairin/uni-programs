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
    if (character >= '0' && character <= '9') return character - '0' + 2;
    if (character == 'a') return 12;
    if (character == 'c') return 13;
    if (character == 'e') return 14;
    if (character == 'h') return 15;
    if (character == 'i') return 16;
    if (character == 'r') return 17;
    if (character == 's') return 18;
    if (character == 't') return 19;
    if (character == '\n') return 20;
    return -1;
}

int transition(int current_state, char character, int edges[][21]) {
    int index = charmapColumn(character);
    return (index == -1) ? -1 : edges[current_state][index];
}

void acceptAction(char *current_input, int accept_length, int last_final) {
    if (accept_length > 0) {
        char aux = current_input[accept_length];
        current_input[accept_length] = '\0';

        if(last_final == 3) 
            printf("ELE\n");
        else if(last_final == 6)
            printf("ELA\n");
        else if(last_final == 8)
            printf("DELE\n");
        else if(last_final == 10)
            printf("DELA\n");
        else if(last_final == 13)
            printf("GATO\n");
        else if(last_final == 15)
            printf("GATOS\n");
        else if(last_final == 14)
            printf("CARRO\n");
        else if(last_final == 16)
            printf("CARROS\n");
        else if(last_final == 17)
            printf("MAIS\n");
        else if(last_final == 18)
            printf("MENOS\n");
        else if(last_final == 19)
            printf("INTEIRO %s\n", current_input);
        else if(last_final == 22)
            printf("REAL %s\n", current_input);
        current_input[accept_length] = aux;
    }
}