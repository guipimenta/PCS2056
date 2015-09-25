#include <stdio.h>
#include "../headers/tokenizer.h"
#include "../headers/bool.h"
#include "../headers/aux_char.h"
#include "../headers/automata.h"
#include <string.h>

extern TRANS_TABLE trans_table;

STATE next_state(STATE current, char current_char, char next_char);

void tokenize(TOKEN_VALUE t_value, TOKEN_CLASS t_class);

//GLOBAL VARIABLES
char identifier_value[150];
int identifier_array_index;

void read_file(char* file_name) {

	FILE *f;
	f = fopen("entrada.txt", "r");
	if (f == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
	}
	char current_char = 0;
	char next_char = 0;
	STATE current = S0;
	STATE next;

	while (1) {
		current_char = next_char;
		if(current_char == EOF)
			break;

		next_char = getc(f);
		if(current_char) {
			next = next_state(current, current_char, next_char);
			// if(token_found) {
			// 	fseek(f, -1, SEEK_CUR); //go back 1 cursor position to read again char that ended the last token
			// }
		}
		current = next;
	}

	fclose(f);
}


/*
* NEXT_STATE
*	PARAMS:
*		current: current state ID
*		c:		 char to search for transactions on TRANS_TABLE
*
* Will search on the TRANS_TABLE for the current state transitions
*
* Triggering transitions means that we the current state has a VALID
* transition rule for the given char c.
* If a vaid transition is triggeres, next_state will return the NEXT
* State ID
*
* The macro DIGIT takes a char c and returns either is a DD or a LL
* (all defined in aux_char) so that special rules, like:
* 	#[a-zA-Z]+
* can be created without adding many transactions on TRANS_TABLE
*/

STATE next_state(STATE current, char current_char, char next_char)
{
	int i = 0;
	while(trans_table[current].transitions[i].trigger != AN)
	{
		if(trans_table[current].transitions[i].trigger == current_char ||
			trans_table[current].transitions[i].trigger == LETTER(current_char) )
		{
			if(trans_table[current].transitions[i].action != NULL)
				trans_table[current].transitions[i].action(current, trans_table[current].transitions[i].next, current_char, next_char);
			return trans_table[current].transitions[i].next;
		}
		i++;
	}
	return S0;
}


/*
* PARAMETERS: a single WORD for lexical analysis
* RETURNS:	  a TOKEN of the parsed WORD or error token ISERR
*
* TOKENIZE
*
* Reads work char by char, and keep track of the current and next state
* when next_state returns  ISERR, an invalid WORD was found.
* When next is ISF, a final state was reached, so no more parsing, returns
* the valid token.
*/
void tokenize(TOKEN_VALUE t_value, TOKEN_CLASS t_class)
{
	printf("t_class: %d, t_value: %s\n", t_class, t_value);

	switch(t_class) {
		case VARIABLE:

			break;
		case IDENTIFIER:

			break;
		case RESERVED_WORD:

			break;
		case INTEGER:

			break;
		case FLOAT:

			break;
		case STRING:

			break;
		case SIMPLE_OPERATOR:

			break;
		case DOUBLE_OPERATOR:

			break;
	}
}

// ACTIONS FUNCTIONS
void identifier_first_char(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("identifier_first_char\n");
	identifier_array_index = 0;
	identifier_value[identifier_array_index] = current_char;

	if(next_char == EOF) {
		identifier_value[++identifier_array_index] = '\0';
		tokenize(identifier_value, IDENTIFIER);
	}
}

void identifier_loop(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("identifier_loop\n");
	identifier_value[++identifier_array_index] = current_char;

	if(next_char == EOF) {
		identifier_value[++identifier_array_index] = '\0';
		tokenize(identifier_value, IDENTIFIER);
	}
}

// void identifier_end(STATE current_state, STATE next_state, char current_char, char next_char) {
// 	printf("identifier_end\n");
// 	identifier_value[++identifier_array_index] = '\0';
// 	tokenize(identifier_value, IDENTIFIER);

// 	return TRUE;
// }
