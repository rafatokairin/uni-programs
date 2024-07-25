#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automata.h"
#include "state.h"

int main() {
    char input[1026];
    int first_output = 1;

    while (fgets(input, sizeof(input), stdin) != NULL) {
        int last_final = 0, current_state = INITIAL_STATE, accept_length = 0, cursor = 0;
        char *current_input = input;

        while (1) {
            char current_char = current_input[cursor++];
            current_state = transition(current_state, current_char, edges);

            if (current_state == -1) {
                if (!first_output) printf("\n");
                printf("ERRO");
                first_output = 0;
                current_input += cursor;
                current_state = INITIAL_STATE;
                cursor = accept_length = 0;
                continue;
            }
            if (current_state == 0) {
                if (*current_input == '\n' || *current_input == '\0') break;
                if (!first_output) printf("\n");
                acceptAction(current_input, accept_length, last_final);
                first_output = 0;
                current_input += accept_length;
                current_state = INITIAL_STATE;
                cursor = accept_length = last_final = 0;
            } else if (isFinalState(current_state)) {
                last_final = current_state;
                accept_length = cursor;
            }
        }

        if (*current_input != '\0' && *current_input != '\n') {
            if (!first_output) printf("\n");
            acceptAction(current_input, accept_length, last_final);
        }
    }

    return 0;
}