#ifndef SYNTATIC_H
#define SYNTATIC_H
#define MAXSTATES 1000
#define MAXTRANSITIONS 20
#define MAXAUTOMATA 20
#define DEBUG
#include <stdio.h>
#include "../headers/tokenizer.h"
#include "../headers/bool.h"

// Just the end of the rows
#define EOR_TRANSITION { FALSE, { RESERVED_WORD, "END OF ROW"}, EOR, SUBMACHINE_NULL }
#define EMPTY_VALUE ""
#define TRIGGER_NULL	0

void read_file(char* file_name);

typedef enum {
	SUBMACHINE_PROGRAM,
	SUBMACHINE_DEF_FUNCTION,
	SUBMACHINE_DECLARATION,
	SUBMACHINE_COMMANDS,
	SUBMACHINE_ATTRIBUTION,
	SUBMACHINE_CALL_FUNCTION,
	SUBMACHINE_IF_CONDITION,
	SUBMACHINE_ITERATION,
	SUBMACHINE_ARITH_EXP,
	SUBMACHINE_BOOL_EXP,
	SUBMACHINE_OUTPUT,
	SUBMACHINE_NULL
} sub_machine;

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
	Q6,
	Q7,
	Q8,
	Q9,
	Q10,
	Q11,
	QF,
	EOR
} SUB_MACHINE_STATES;

//Token definition for STRUCTURED_AUTOMATA
//Contains only the expected value and class
typedef struct {
	TOKEN_CLASS class;
	char *value;
} STRUCTURED_AUTOMATA_TOKEN;

//Transition is a struct represented by:
//	- Token that can trigger it
//	- identifier saying if is a submachine transition
//	- and a next state that can be any of the default states
//	- the ID of the next submachine to run (in case of a sub-machine transition)
typedef struct {
	BOOL is_submachine_transition;
	STRUCTURED_AUTOMATA_TOKEN trigger;
	SUB_MACHINE_STATES next_state;
	sub_machine next_submachime;
} STRUCTURED_AUTOMATA_TRANSITION;

//Structued automata is defined by
//	- current state number
//	- a table containg the transitions
typedef struct {
	int automata_id;
	int current_state;
	STRUCTURED_AUTOMATA_TRANSITION transitions[MAXSTATES][MAXTRANSITIONS];
} STRUCTURED_AUTOMATA;

typedef struct {
	sub_machine sm;
	int state;
} sm_stack_pair;

typedef struct stack {
	sm_stack_pair sm_pair;
	struct stack *next;
} node;

typedef node Stack;

// Function that calculates next state
BOOL run_automata(STRUCTURED_AUTOMATA **automata, TOKEN token, Stack **stack);

// function that compares a structured_automata_token and token
// return true if they are equals
BOOL compare_token_values(STRUCTURED_AUTOMATA_TOKEN t1, TOKEN t2);

void print_stack_pair(sm_stack_pair pair);
#endif
