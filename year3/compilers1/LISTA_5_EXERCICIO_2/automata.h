#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "state.h"

int isFinalState(int state);

int charmapColumn(char character);

int transition(int current_state, char character, int edges[][41]);

void acceptAction(char *current_input, int accept_length, int last_final);