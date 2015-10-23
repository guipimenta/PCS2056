#include <stdio.h>
#include "../headers/tokenizer.h"
#include "../headers/bool.h"
#include "../headers/aux_char.h"
#include "../headers/tables.h"
#include <string.h>
#include <stdlib.h>

STATE next_state(STATE current, char current_char, char next_char, BOOL *end_of_token, BOOL *endOfProgram);

TOKEN tokenize(TOKEN_VALUE t_value, TOKEN_CLASS t_class);
TOKEN make_token(TOKEN_CLASS token_class, int table_index, int row, int column);
// void print_token(TOKEN token);

// ACTIONS FUNCITONS

// IDENTIFIER ACTIONS
BOOL identifier_first_char(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL identifier_loop(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL identifier_end(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);

// VARIABLE ACTIONS
BOOL variable_first_char(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL variable_loop(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL variable_end(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);

// NUMBER ACTIONS
BOOL number_first_char(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL number_loop(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL integer_end(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL float_number(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL float_first_char(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL float_loop(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL float_end(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);

// STRING ACTIONS
BOOL string_beginning(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL string_loop(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL string_escaped_char(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL string_end(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);

// SYMBOL ACTIONS
BOOL symbol_first_char(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL single_symbol_end(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL double_symbol(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL double_symbol_end(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);
BOOL symbol_error(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram);

/*
* TRANSITIONS TABLE
*
* A table containg a simple structure:
* 	       identified by state id, contains transition struct
*		  that contains a id of the state and a list of possible
*         transitions.
*
* TRANSITION
*
* A tuple that contains a char that triggers the transition and
* the id of the next state.
*
* STATES
*
* They are integers that indexes the TRANSITION TABLE.
* Special States:
*	- ISF: Identifier State Final: after a VALID command, a '\n' will
*		   trigger a transition to the final state, so that we know
*			that the WORD parsed is VALID
*	- ISERR: if the char doesn't trigger any transition, the TEND
*			 transition will be triggered, and automata will go to
*			 a invalid state, called ISERR
*
* SPECIAL KEY CODES
*
* In case we need a special keycode (like, identifiers, that accept)
* any digit, we use aux_char library, that brings up LL and DD. This
* special codes, will allow our automata to track down digits and letters
* so that we can build-up identifiers and numbers
*/

TRANS_TABLE trans_table = {
/*	[<ROW NUMBER>] {<STATEID>, { {TRIGGER, NEXT_STATE}, ... }}*/
	[S0]   			= {S0,  			{ {'#', SVAR, variable_first_char}, {DD, SINT, number_first_char},   {LL, SIDENT, identifier_first_char}, {'/', SCOMM1}, {'"', SSTR1, string_beginning}, {SB, SSYMB1, symbol_first_char}, {WS, S0}, {AN, SERROR, symbol_error} }},
	[SVAR]  		= {SVAR, 			{ {DD, SVAR, variable_loop}, {LL, SVAR, variable_loop},   {AN, S0, variable_end}  		  							}},
	[SIDENT]  	= {SIDENT, 		{ {LL, SIDENT, identifier_loop}, {DD, SIDENT, identifier_loop}, {AN, S0, identifier_end} 									}},
	[SINT]  		= {SINT, 			{ {DD, SINT, number_loop}, {'.', SFLOAT1, float_number},  {AN, S0, integer_end}  									}},
	[SFLOAT1]  	= {SFLOAT1,		{ {DD, SFLOAT2, float_first_char}, {AN, SERROR}			   										}},
	[SFLOAT2]  	= {SFLOAT2, 	{ {DD, SFLOAT2, float_loop}, {AN, S0, float_end}			   										}},
	[SCOMM1]  	=	{SCOMM1, 		{ {'/', SCOMM2}, {AN, S0}													}},
	[SCOMM2]  	=	{SCOMM2, 		{ {'\n', S0},  {AN, SCOMM2}													}},
	[SSTR1]  		=	{SSTR1, 		{ {'"', SSTR3},  {'\\', SSTR2}, {AN, SSTR1, string_loop}										}},
	[SSTR2]  		=	{SSTR2, 		{ {AN, SSTR1, string_escaped_char}															}},
	[SSTR3]			= {SSTR3,			{ {AN, S0, string_end}											}},
	[SSYMB1]  	=	{SSYMB1, 		{ {SB, SSYMB2, double_symbol}, {LL, S0, single_symbol_end}, {DD, S0, single_symbol_end}, {WS, S0, single_symbol_end}, {AN, S0, symbol_error}													}},
	[SSYMB2] 		=	{S0,  			{ {AN, S0, double_symbol_end}																}},
	[SERROR]	=	{SERROR, {{AN, S0}}}
};

//GLOBAL VARIABLES
TOKEN_VALUE token_value;
TOKEN global_token;
BOOL tokenFound;
int token_array_index;
int current_row = 0;
int current_column = 0;
char current_char = 0;
char next_char = 0;

BOOL get_token(FILE *f, TOKEN *token_found, BOOL *endOfProgram) {

	STATE current = S0;
	STATE next = S0;
	BOOL token_end = FALSE;

	tokenFound = FALSE;

	while (!tokenFound) {
		current_char = next_char;
		if(current_char == EOF) {
			*endOfProgram = TRUE;
			break;
		}

		next_char = getc(f);
		if(current_char) {
			current_column++;
			// printf("current_state: %d, next_state: %d\n", current, next);
			// printf("current_char: %c, next_char: %c, token_end: %d\n", current_char, next_char, token_end);
			next = next_state(current, current_char, next_char, &token_end, endOfProgram);
			if(next != SERROR) {
				if(token_end) {
					next_char = current_char;
					if(current_char == '\n') {
						current_column = 0;
						current_row++;
					}
					current_column--;
					fseek(f, -1, SEEK_CUR); //go back 1 cursor position to read again char that ended the last token
				}
			}
		}
		current = next;

		if(tokenFound) {
			// printf("\n");
			// printf("TOKEN VALUE: %d\n", global_token.table_index);
			// printf("TOKEN CLASS: %d\n", global_token.token_class);
			// printf("TOKEN LINE: %d\n", global_token.row);
			// printf("TOKEN COLUMN: %d\n", global_token.column);
			// printf("\n");
			token_found->token_class = global_token.token_class;
			token_found->table_index = global_token.table_index;
			token_found->row = global_token.row;
			token_found->column = global_token.column;
		}
	}

	return tokenFound;
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

STATE next_state(STATE current, char current_char, char next_char, BOOL *end_of_token, BOOL *endOfProgram)
{
	int i = 0;
	while(trans_table[current].transitions[i].trigger != AN)
	{
		// printf("current_state: %d, next_state: %d\n", current, trans_table[current].transitions[i].next);
		// printf("current_char: %c, next_char: %c, trigger: %d\n", current_char, next_char, trans_table[current].transitions[i].trigger);
		if(trans_table[current].transitions[i].trigger == current_char ||
			trans_table[current].transitions[i].trigger == LETTER(current_char) ||
			trans_table[current].transitions[i].trigger == DIGIT(current_char) ||
			trans_table[current].transitions[i].trigger == SYMBOL(current_char) ||
			trans_table[current].transitions[i].trigger == WHITESPACE(current_char))
		{
			if(trans_table[current].transitions[i].action != NULL)
				*end_of_token = trans_table[current].transitions[i].action(current, trans_table[current].transitions[i].next, current_char, next_char, endOfProgram);
			else
				*end_of_token = FALSE;
			return trans_table[current].transitions[i].next;
		}
		i++;
	}

	if(trans_table[current].transitions[i].action != NULL)
		*end_of_token = trans_table[current].transitions[i].action(current, trans_table[current].transitions[i].next, current_char, next_char, endOfProgram);
	else
		*end_of_token = FALSE;

	return trans_table[current].transitions[i].next;
}

TOKEN make_token(TOKEN_CLASS token_class, int table_index, int row, int column) {
	TOKEN result_token;

	result_token.token_class = token_class;
	result_token.table_index = table_index;
	result_token.row = row;
	result_token.column = column;

	return result_token;
}

void print_token(TOKEN token) {
	char token_class[50];
	TOKEN_VALUE token_value;
	switch(token.token_class) {
		case VARIABLE:
			strcpy(token_class, "Variable");
			strcpy(token_value, get_variable(token.table_index));
			break;
		case IDENTIFIER:
			strcpy(token_class, "Identifier");
			strcpy(token_value, get_identifier(token.table_index));
			break;
		case RESERVED_WORD:
			strcpy(token_class, "Reserved Word");
			strcpy(token_value, get_reserved_word(token.table_index));
			break;
		case INTEGER:
			strcpy(token_class, "Integer");
			sprintf(token_value, "%d", get_integer(token.table_index));
			break;
		case FLOAT:
			strcpy(token_class, "Float");
			printf("%f\n", get_float(token.table_index));
			sprintf(token_value, "%f", get_float(token.table_index));
			break;
		case STRING:
			strcpy(token_class, "String");
			strcpy(token_value, get_string(token.table_index));
			break;
		case SINGLE_SYMBOL:
			strcpy(token_class, "Single Symbol");
			token_value[0] = get_single_symbol(token.table_index);
			token_value[1] = '\0';
			break;
		case DOUBLE_SYMBOL:
			strcpy(token_class, "Double Symbol");
			strcpy(token_value, get_double_symbol(token.table_index));
			break;
	}

	printf("TOKEN CLASS: %s\n", token_class);
	printf("TOKEN VALUE: %s\n", token_value);
	printf("TOKEN LINE: %d\n", token.row);
	printf("TOKEN COLUMN: %d\n", token.column);


	printf("\n\n");

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
TOKEN tokenize(TOKEN_VALUE t_value, TOKEN_CLASS t_class)
{
	int table_index = -1;
	TOKEN token_read;
	char token_class[50];

	switch(t_class) {
		case VARIABLE:
			table_index = insert_into_variables_table(t_value);
			strcpy(token_class, "Variable");
			break;
		case IDENTIFIER:
			table_index = insert_into_identifiers_table(t_value);
			strcpy(token_class, "Identifier");
			break;
		case RESERVED_WORD:
			table_index = is_in_reserved_words_table(t_value);
			strcpy(token_class, "Reserved Word");
			break;
		case INTEGER:
			table_index = insert_into_integers_table(strtol(t_value, NULL, 0));
			strcpy(token_class, "Integer");
			break;
		case FLOAT:
			table_index = insert_into_floats_table(strtof(t_value, NULL));
			strcpy(token_class, "Float");
			break;
		case STRING:
			table_index = insert_into_strings_table(t_value);
			strcpy(token_class, "String");
			break;
		case SINGLE_SYMBOL:
			table_index = is_in_single_symbols_table(t_value[0]);
			strcpy(token_class, "Single Symbol");
			break;
		case DOUBLE_SYMBOL:
			table_index = is_in_double_symbols_table(t_value);
			strcpy(token_class, "Double Symbol");
			break;
	}

	token_read = make_token(t_class, table_index, current_row, current_column - token_array_index - 1);

	// printf("\n");
	// printf("TOKEN VALUE: %d\n", table_index);
	// printf("TOKEN CLASS: %s\n", token_class);
	// printf("TOKEN LINE: %d\n", current_row);
	// printf("TOKEN COLUMN: %d\n", current_column - token_array_index - 1	);
	// printf("\n");

	return token_read;
}

// ACTIONS FUNCTIONS

//IDENTIFIER ACTIONS
BOOL identifier_first_char(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_array_index = 0;
	token_value[token_array_index] = current_char;

	if(next_char == EOF) {
		*endOfProgram = TRUE;
		current_column++;
		token_value[++token_array_index] = '\0';
		if(is_in_reserved_words_table(token_value) > -1)
			tokenize(token_value, RESERVED_WORD);
		else
			tokenize(token_value, IDENTIFIER);
		tokenFound = TRUE;
	}

	return FALSE;
}

BOOL identifier_loop(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_value[++token_array_index] = current_char;

	if(next_char == EOF) {
		*endOfProgram = TRUE;
		current_column++;
		token_value[++token_array_index] = '\0';
		if(is_in_reserved_words_table(token_value) > -1)
			global_token = tokenize(token_value, RESERVED_WORD);
		else
			global_token = tokenize(token_value, IDENTIFIER);
		tokenFound = TRUE;
	}

	return FALSE;
}

BOOL identifier_end(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_value[++token_array_index] = '\0';
	if(is_in_reserved_words_table(token_value) > -1)
		global_token = tokenize(token_value, RESERVED_WORD);
	else
		global_token = tokenize(token_value, IDENTIFIER);
	tokenFound = TRUE;

	return TRUE;
}
//-----------END OF IDENTIFIER ACTIONS---------------------------------------------------------------------------------

// VARIABLE ACTIONS
BOOL variable_first_char(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_array_index = 0;
	token_value[token_array_index] = current_char;

	if(next_char == EOF) {
		*endOfProgram = TRUE;
		current_column++;
		token_value[++token_array_index] = '\0';
		global_token = tokenize(token_value, VARIABLE);
		tokenFound = TRUE;
	}

	return FALSE;
}

BOOL variable_loop(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_value[++token_array_index] = current_char;

	if(next_char == EOF) {
		*endOfProgram = TRUE;
		current_column++;
		token_value[++token_array_index] = '\0';
		global_token = tokenize(token_value, VARIABLE);
		tokenFound = TRUE;
	}

	return FALSE;
}

BOOL variable_end(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_value[++token_array_index] = '\0';
	global_token = tokenize(token_value, VARIABLE);
	tokenFound = TRUE;

	return TRUE;
}
//-----------END OF VARIABLE ACTIONS---------------------------------------------------------------------------------

// NUMBER ACTIONS
BOOL number_first_char(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_array_index = 0;
	token_value[token_array_index] = current_char;

	if(next_char == EOF) {
		*endOfProgram = TRUE;
		current_column++;
		token_value[++token_array_index] = '\0';
		global_token = tokenize(token_value, INTEGER);
		tokenFound = TRUE;
	}

	return FALSE;
}

BOOL number_loop(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_value[++token_array_index] = current_char;

	if(next_char == EOF){
		current_column++;
		token_value[++token_array_index] = '\0';
		global_token = tokenize(token_value, INTEGER);
		tokenFound = TRUE;
	}

	return FALSE;
}

BOOL integer_end(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_value[++token_array_index] = '\0';
	global_token = tokenize(token_value, INTEGER);
	tokenFound = TRUE;

	return TRUE;
}

BOOL float_number(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_value[++token_array_index] = current_char;

	return FALSE;
}

BOOL float_first_char(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_value[++token_array_index] = current_char;

	if(next_char == EOF){
		current_column++;
		token_value[++token_array_index] = '\0';
		global_token = tokenize(token_value, FLOAT);
		tokenFound = TRUE;
	}

	return FALSE;
}

BOOL float_loop(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_value[++token_array_index] = current_char;

	if(next_char == EOF){
		current_column++;
		token_value[++token_array_index] = '\0';
		global_token = tokenize(token_value, FLOAT);
		tokenFound = TRUE;
	}

	return FALSE;
}

BOOL float_end(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_value[++token_array_index] = '\0';
	global_token = tokenize(token_value, FLOAT);
	tokenFound = TRUE;

	return TRUE;
}
//-----------END OF NUMBER ACTIONS---------------------------------------------------------------------------------

// STRING ACTIONS
BOOL string_beginning(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_array_index = -1;

	if(next_char == EOF) {
		*endOfProgram = TRUE;
		printf("STRING ERROR: STRING QUOTES NOT CLOSED!\n");
	}

	return FALSE;
}

BOOL string_loop(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_value[++token_array_index] = current_char;

	if(next_char == EOF) {
		*endOfProgram = TRUE;
		printf("STRING ERROR: STRING QUOTES NOT CLOSED!\n");
	}

	return FALSE;
}

BOOL string_escaped_char(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_value[++token_array_index] = current_char;

	if(next_char == EOF) {
		*endOfProgram = TRUE;
		printf("STRING ERROR: STRING QUOTES NOT CLOSED!\n");
	}

	return FALSE;
}

BOOL string_end(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_value[++token_array_index] = '\0';
	global_token = tokenize(token_value, STRING);
	tokenFound = TRUE;

	return FALSE; //doesn't return true because is string
}
//-----------END OF STRING ACTIONS---------------------------------------------------------------------------------

// SYMBOL ACTIONS
BOOL symbol_first_char(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	token_array_index = 0;
	token_value[token_array_index] = current_char;

	if(next_char == EOF) {
		*endOfProgram = TRUE;
		current_column++;
		if(is_in_single_symbols_table(token_value[token_array_index]) > -1) {
			token_value[++token_array_index] = '\0';
			global_token = tokenize(token_value, SINGLE_SYMBOL);
			tokenFound = TRUE;
		} else {
			printf("SYMBOL ERROR: %c IS NOT IN SINGLE SYMBOLS TABLE!\n", token_value[token_array_index]);
		}
	}

	return FALSE;
}

BOOL single_symbol_end(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {

	if(is_in_single_symbols_table(token_value[token_array_index]) > -1) {
		token_value[++token_array_index] = '\0';
		global_token = tokenize(token_value, SINGLE_SYMBOL);
		tokenFound = TRUE;
	} else {
		printf("SYMBOL ERROR: %c IS NOT IN SINGLE SYMBOLS TABLE!\n", token_value[token_array_index]);
	}

	return TRUE;
}

BOOL double_symbol(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	char single_symbol_aux[2];
	token_value[++token_array_index] = current_char;

	if(next_char == EOF) {
		*endOfProgram = TRUE;
		current_column++;
		token_value[++token_array_index] = '\0';
		if(is_in_double_symbols_table(token_value) > -1) {
			global_token = tokenize(token_value, DOUBLE_SYMBOL);
			tokenFound = TRUE;
		} //in case there are two single symbols next to each other
		else if((is_in_single_symbols_table(token_value[0]) > -1) &&
							(is_in_single_symbols_table(token_value[1]) > -1)) {
			single_symbol_aux[0] = token_value[0];
			single_symbol_aux[1] = '\0';
			global_token = tokenize(single_symbol_aux, SINGLE_SYMBOL);
			current_column++;
			single_symbol_aux[0] = token_value[1];
			single_symbol_aux[1] = '\0';
			global_token = tokenize(single_symbol_aux, SINGLE_SYMBOL);
			tokenFound = TRUE;
		}
		else {
			printf("SYMBOL ERROR: %s IS NOT IN DOUBLE SYMBOLS TABLE!\n", token_value);
		}
	}

	return FALSE;
}

BOOL double_symbol_end(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {
	char single_symbol_aux[2];

	token_value[++token_array_index] = '\0';
	if(is_in_double_symbols_table(token_value) > -1) {
		global_token = tokenize(token_value, DOUBLE_SYMBOL);
		tokenFound = TRUE;
	} //in case there are two single symbols next to each other
	else if((is_in_single_symbols_table(token_value[0]) > -1) &&
						(is_in_single_symbols_table(token_value[1]) > -1)) {
		single_symbol_aux[0] = token_value[0];
		single_symbol_aux[1] = '\0';
		global_token = tokenize(single_symbol_aux, SINGLE_SYMBOL);
		current_column++;
		single_symbol_aux[0] = token_value[1];
		single_symbol_aux[1] = '\0';
		global_token = tokenize(single_symbol_aux, SINGLE_SYMBOL);
		tokenFound = TRUE;
	}
	else {
		printf("SYMBOL ERROR: %s IS NOT IN DOUBLE SYMBOLS TABLE!\n", token_value);
	}

	return TRUE;
}

BOOL symbol_error(STATE current_state, STATE next_state, char current_char, char next_char, BOOL *endOfProgram) {

	printf("SYMBOL ERROR: %c IS NOT A POSSIBLE SYMBOL OF THE LANGUAGE!\n", current_char);

	return FALSE; //doesn't return true because is string
}
//-----------END OF SYMBOL ACTIONS---------------------------------------------------------------------------------

