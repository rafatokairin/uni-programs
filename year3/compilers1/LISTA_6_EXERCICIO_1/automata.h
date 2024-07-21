#ifndef AUTOMATA_INCLUDED
#define AUTOMATA_INCLUDED

int isFinalState(int state);

int charmapColumn(char character);

int transition(int current_state, char character, int edges[][21]);

void acceptAction(char *current_input, int accept_length, int last_final);

#endif