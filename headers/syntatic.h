#ifndef SYNTATIC_H
#define SYNTATIC_H
#define MAXSTATES 1000
#define MAXTRANSITIONS 1000
#define MAXAUTOMATA 1000
#include <stdio.h>
#include "../headers/tokenizer.h"
#include "../headers/bool.h"
void read_file(char* file_name);

//Generic states for all automatas
//EOR: End of Row is a special state that represents
//	   an end of the transitions rows, so that we know 
//	   when no transition was found
typedef enum sub_machine_states {
	Q0,
	Q1,
	Q2,
	Q3,
	Q4,
	Q5,
	EOR
} SUB_MACHINE_STATES;

//Token definition for STRUCTURED_AUTOMATA
//Contains only the expected value and class
typedef struct {
	TOKEN_CLASS class;
	char value[WMAX];
} STRUCTURED_AUTOMATA_TOKEN;

//Transition is a struct represented by:
//	- Token that can trigger it
//	- identifier saying if is a submachine transition
//	- and a next state that can be any of the default states
typedef struct {
	STRUCTURED_AUTOMATA_TOKEN trigger;
	BOOL is_submachine_transition;
	SUB_MACHINE_STATES next_state;
} STRUCTURED_AUTOMATA_TRANSITION;

//Structued automata is defined by
//	- current state number
//	- a table containg the transitions
typedef struct {
	int current_state;
	STRUCTURED_AUTOMATA_TRANSITION transitions[MAXTRANSITIONS];
} STRUCTURED_AUTOMATA;



void run_automata(STRUCTURED_AUTOMATA automata, TOKEN token);

#endif
