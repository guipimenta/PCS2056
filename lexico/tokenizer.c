#include <stdio.h>
#include "../headers/tokenizer.h"
#include "../headers/bool.h"
#include "../headers/aux_char.h"
#include "../headers/aux_number.h"
#include "../headers/automata.h"
#include <string.h>

extern TRANS_TABLE trans_table;

STATE next_state(STATE current, char current_char, char next_char, BOOL *end_of_token);

void tokenize(TOKEN_VALUE t_value, TOKEN_CLASS t_class);

//GLOBAL VARIABLES
char identifier_value[150];
int identifier_array_index;
char variable_value[150];
int variable_array_index;
TOKEN_VALUE token_value;
int token_array_index;
int float_decimal_count;
int integer_value;

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
	STATE next = S0;
	BOOL token_end = FALSE;

	while (1) {
		current_char = next_char;
		if(current_char == EOF)
			break;

		next_char = getc(f);
		if(current_char) {
			next = next_state(current, current_char, next_char, &token_end);
			// printf("current_state: %d, next_state: %d\n", current, next);
			// printf("current_char: %c, next_char: %c\n", current_char, next_char);
			if(next != -1) {
				if(token_end) {
					next_char = current_char;
					fseek(f, -1, SEEK_CUR); //go back 1 cursor position to read again char that ended the last token
				}
			}
			else {
				printf("ERRO!!\n");
				break;
			}
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

STATE next_state(STATE current, char current_char, char next_char, BOOL *end_of_token)
{
	int i = 0;
	while(trans_table[current].transitions[i].trigger != AN)
	{
		// printf("current_state: %d, next_state: %d\n", current, trans_table[current].transitions[i].next);
		// printf("current_char: %c, next_char: %c, trigger: %d\n", current_char, next_char, trans_table[current].transitions[i].trigger);
		if(trans_table[current].transitions[i].trigger == current_char ||
			trans_table[current].transitions[i].trigger == LETTER(current_char) ||
			trans_table[current].transitions[i].trigger == DIGIT(current_char) ||
			trans_table[current].transitions[i].trigger == UNARY(current_char) ||
			trans_table[current].transitions[i].trigger == WHITESPACE(current_char))
		{
			if(trans_table[current].transitions[i].action != NULL)
				*end_of_token = trans_table[current].transitions[i].action(current, trans_table[current].transitions[i].next, current_char, next_char);
			else
				*end_of_token = FALSE;
			return trans_table[current].transitions[i].next;
		}
		i++;
	}

	if(trans_table[current].transitions[i].action != NULL)
		*end_of_token = trans_table[current].transitions[i].action(current, trans_table[current].transitions[i].next, current_char, next_char);
	else
		*end_of_token = FALSE;

	return trans_table[current].transitions[i].next;
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

//IDENTIFIER ACTIONS
BOOL identifier_first_char(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("identifier_first_char\n");
	identifier_array_index = 0;
	identifier_value[identifier_array_index] = current_char;

	if(next_char == EOF) {
		identifier_value[++identifier_array_index] = '\0';
		tokenize(identifier_value, IDENTIFIER);
	}

	return FALSE;
}

BOOL identifier_loop(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("identifier_loop\n");
	identifier_value[++identifier_array_index] = current_char;

	if(next_char == EOF) {
		identifier_value[++identifier_array_index] = '\0';
		tokenize(identifier_value, IDENTIFIER);
	}

	return FALSE;
}

BOOL identifier_end(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("identifier_end\n");
	identifier_value[++identifier_array_index] = '\0';
	tokenize(identifier_value, IDENTIFIER);

	return TRUE;
}
//-----------END OF IDENTIFIER ACTIONS---------------------------------------------------------------------------------

// VARIABLE ACTIONS
BOOL variable_first_char(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("identifier_first_char\n");
	variable_array_index = 0;
	variable_value[variable_array_index] = current_char;

	if(next_char == EOF) {
		variable_value[++variable_array_index] = '\0';
		tokenize(variable_value, VARIABLE);
	}

	return FALSE;
}

BOOL variable_loop(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("identifier_loop\n");
	variable_value[++variable_array_index] = current_char;

	if(next_char == EOF) {
		variable_value[++variable_array_index] = '\0';
		tokenize(variable_value, VARIABLE);
	}

	return FALSE;
}

BOOL variable_end(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("identifier_end\n");
	variable_value[++variable_array_index] = '\0';
	tokenize(variable_value, VARIABLE);

	return TRUE;
}
//-----------END OF VARIABLE ACTIONS---------------------------------------------------------------------------------

// NUMBER ACTIONS
BOOL number_first_char(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("number_first_char\n");
	token_array_index = 0;
	token_value[token_array_index] = current_char;

	if(next_char == EOF) {
		token_value[++token_array_index] = '\0';
		tokenize(token_value, INTEGER);
	}

	return FALSE;
}

BOOL number_loop(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("number_loop\n");
	token_value[++token_array_index] = current_char;

	if(next_char == EOF){
		token_value[++token_array_index] = '\0';
		tokenize(token_value, INTEGER);
	}

	return FALSE;
}

BOOL integer_end(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("integer_end\n");
	token_value[++token_array_index] = '\0';
	tokenize(token_value, INTEGER);

	return TRUE;
}

BOOL float_number(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("float_number\n");

	token_value[++token_array_index] = current_char;

	return FALSE;
}

BOOL float_first_char(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("float_first_char\n");
	token_value[++token_array_index] = current_char;

	if(next_char == EOF){
		token_value[++token_array_index] = '\0';
		tokenize(token_value, FLOAT);
	}

	return FALSE;
}

BOOL float_loop(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("float_loop\n");
	token_value[++token_array_index] = current_char;

	if(next_char == EOF){
		token_value[++token_array_index] = '\0';
		tokenize(token_value, FLOAT);
	}

	return FALSE;
}

BOOL float_end(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("float_end\n");
	
	token_value[++token_array_index] = '\0';
	tokenize(token_value, FLOAT);

	return TRUE;
}
//-----------END OF NUMBER ACTIONS---------------------------------------------------------------------------------

// STRING ACTIONS
BOOL string_beginning(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("string_beginning\n");
	token_array_index = -1;

	if(next_char == EOF) {
		printf("ERRO DE STRING SEM FECHAR ASPAS!\n");
	}

	return FALSE;
}

BOOL string_loop(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("string_loop\n");
	token_value[++token_array_index] = current_char;

	if(next_char == EOF) {
		printf("ERRO DE STRING SEM FECHAR ASPAS!\n");
	}

	return FALSE;
}

BOOL string_escaped_char(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("string_escaped_char\n");
	token_value[++token_array_index] = current_char;

	if(next_char == EOF) {
		printf("ERRO DE STRING SEM FECHAR ASPAS!\n");
	}

	return FALSE;
}

BOOL string_end(STATE current_state, STATE next_state, char current_char, char next_char) {
	printf("string_end\n");
	
	token_value[++token_array_index] = '\0';
	tokenize(token_value, STRING);

	return FALSE; //doesn't return true because is string
}
//-----------END OF STRING ACTIONS---------------------------------------------------------------------------------
