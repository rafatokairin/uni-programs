#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/automata.h"
#include "../headers/state.h"

int main() {
    char input[1026];
    while (fgets(input, sizeof(input), stdin) != NULL) {
        int last_final = 0, current_state = INITIAL_STATE, accept_length = 0, cursor = 0;
        char *current_input = input;

        while (1) {
            char current_char = current_input[cursor++];
            current_state = transition(current_state, current_char, edges);
            
            if (current_state == -1) {
                printf("ERRO\n");
                current_input += cursor;
                current_state = INITIAL_STATE;
                cursor = accept_length = 0;
                continue;
            }
            if (current_state == 0) {
                if (*current_input == '\n' || *current_input == '\0') break;
                acceptAction(current_input, accept_length, last_final);
                current_input += accept_length;
                current_state = INITIAL_STATE;
                cursor = accept_length = last_final = 0;
            } else if (isFinalState(current_state)) {
                last_final = current_state;
                accept_length = cursor;
            }
        }
    }
    return 0;
}