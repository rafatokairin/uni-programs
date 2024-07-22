#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automata.h"
#include "state.h"

int main() {
    char input[1026];
    int first_token = 1;

    while (fgets(input, sizeof(input), stdin) != NULL) {
        int last_final = 0, current_state = INITIAL_STATE, accept_length = 0, cursor = 0;
        char *current_input = input;

        while (1) {
            char current_char = current_input[cursor++];
            if (current_char == '\0') break;
            current_state = transition(current_state, current_char, edges);

            if (current_state == -1) {
                if (accept_length > 0) {
                    acceptAction(current_input, accept_length, last_final);
                    current_input += accept_length;
                    cursor = accept_length = 0;
                    current_state = INITIAL_STATE;
                } else {
                    if (*current_input != ' ') { // ignore blank space
                        if (first_token)
                            first_token = 0;
                        printf("ERRO\n");
                    }
                    current_input += 1;
                    cursor = accept_length = 0;
                    current_state = INITIAL_STATE;
                }
                continue;
            }

            if (current_state == 0) {
                if (*current_input == '\n' || *current_input == '\0') break;
                if (accept_length > 0) {
                    acceptAction(current_input, accept_length, last_final);
                    current_input += accept_length;
                    cursor = accept_length = 0;
                    current_state = INITIAL_STATE;
                } else {
                    if (*current_input != ' ') { // ignore blank space
                        if (first_token)
                            first_token = 0;
                        printf("ERRO\n");
                    }
                    current_input += 1;
                    cursor = accept_length = 0;
                    current_state = INITIAL_STATE;
                }
            } else if (isFinalState(current_state)) {
                last_final = current_state;
                accept_length = cursor;
            }
        }

        if (accept_length > 0) {
            acceptAction(input, accept_length, last_final);
        }
    }
    return 0;
}