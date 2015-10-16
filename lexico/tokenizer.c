#include <stdio.h>
#include "../headers/tokenizer.h"
#include "../headers/bool.h"
#include "../headers/aux_char.h"
#include "../headers/aux_number.h"
#include "../headers/automata.h"
#include "../headers/tables.h"
#include <string.h>
#include <stdlib.h>

extern TRANS_TABLE trans_table;



STATE next_state(STATE current, char current_char, char next_char, BOOL *end_of_token);

void tokenize(TOKEN_VALUE t_value, TOKEN_CLASS t_class);
TOKEN make_token(TOKEN_CLASS token_class, int table_index, int row, int column);
// void print_token(TOKEN token);

//GLOBAL VARIABLES
TOKEN_VALUE token_value;
int token_array_index;
int current_row;
int current_column;

void read_file(char* file_name) {

	FILE *f;
	f = fopen(file_name, "r");
	if (f == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
	}
	char current_char = 0;
	char next_char = 0;
	STATE current = S0;
	STATE next = S0;
	BOOL token_end = FALSE;

	current_row = 0;
	current_column = 0;

	while (TRUE) {
		current_char = next_char;
		if(current_char == EOF)
			break;

		next_char = getc(f);
		if(current_char) {
			current_column++;
			// printf("current_state: %d, next_state: %d\n", current, next);
			// printf("current_char: %c, next_char: %c, token_end: %d\n", current_char, next_char, token_end);
			next = next_state(current, current_char, next_char, &token_end);
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
			trans_table[current].transitions[i].trigger == SYMBOL(current_char) ||
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

TOKEN make_token(TOKEN_CLASS token_class, int table_index, int row, int column) {
	TOKEN result_token;

	result_token.token_class = token_class;
	result_token.table_index = table_index;
	result_token.row = row;
	result_token.column = column;

	return result_token;
}

// void print_token(TOKEN token) {
// 	char token_class[50];
// 	TOKEN_VALUE token_value;
// 	printf("\n");
// 	printf("%d\n", token.table_index);
// 	switch(token.token_class) {
// 		case VARIABLE:
// 			strcpy(token_class, "Variable");
// 			strcpy(token_value, get_variable(token.table_index));
// 			break;
// 		case IDENTIFIER:
// 			strcpy(token_class, "Identifier");
// 			strcpy(token_value, get_identifier(token.table_index));
// 			break;
// 		case RESERVED_WORD:
// 			strcpy(token_class, "Reserved Word");
// 			strcpy(token_value, get_reserved_word(token.table_index));
// 			break;
// 		case INTEGER:
// 			strcpy(token_class, "Integer");
// 			printf("%d\n", get_integer(token.table_index));
// 			sprintf(token_value, "%d", get_integer(token.table_index));
// 			break;
// 		case FLOAT:
// 			strcpy(token_class, "Float");
// 			printf("%f\n", get_float(token.table_index));
// 			sprintf(token_value, "%f", get_float(token.table_index));
// 			break;
// 		case STRING:
// 			strcpy(token_class, "String");
// 			strcpy(token_value, get_string(token.table_index));
// 			break;
// 		case SINGLE_SYMBOL:
// 			strcpy(token_class, "Single Symbol");
// 			token_value[0] = get_single_symbol(token.table_index);
// 			token_value[1] = '\0';
// 			break;
// 		case DOUBLE_SYMBOL:
// 			strcpy(token_class, "Double Symbol");
// 			strcpy(token_value, get_double_symbol(token.table_index));
// 			break;
// 	}

// 	printf("TOKEN CLASS: %s\n", token_class);
// 	printf("TOKEN VALUE: %s\n", token_value);

// 	printf("\n\n");

// }


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

	printf("\n");
	printf("TOKEN VALUE: %s\n", t_value);
	printf("TOKEN CLASS: %s\n", token_class);
	printf("TOKEN LINE: %d\n", current_row);
	printf("TOKEN COLUMN: %d\n", current_column - token_array_index - 1	);
	printf("\n");

	//TODO: pass token to syntatic part
}

// ACTIONS FUNCTIONS

//IDENTIFIER ACTIONS
BOOL identifier_first_char(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_array_index = 0;
	token_value[token_array_index] = current_char;

	if(next_char == EOF) {
		current_column++;
		token_value[++token_array_index] = '\0';
		if(is_in_reserved_words_table(token_value) > -1)
			tokenize(token_value, RESERVED_WORD);
		else
			tokenize(token_value, IDENTIFIER);
	}

	return FALSE;
}

BOOL identifier_loop(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_value[++token_array_index] = current_char;

	if(next_char == EOF) {
		current_column++;
		token_value[++token_array_index] = '\0';
		if(is_in_reserved_words_table(token_value) > -1)
			tokenize(token_value, RESERVED_WORD);
		else
			tokenize(token_value, IDENTIFIER);
	}

	return FALSE;
}

BOOL identifier_end(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_value[++token_array_index] = '\0';
	if(is_in_reserved_words_table(token_value) > -1)
			tokenize(token_value, RESERVED_WORD);
		else
			tokenize(token_value, IDENTIFIER);

	return TRUE;
}
//-----------END OF IDENTIFIER ACTIONS---------------------------------------------------------------------------------

// VARIABLE ACTIONS
BOOL variable_first_char(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_array_index = 0;
	token_value[token_array_index] = current_char;

	if(next_char == EOF) {
		current_column++;
		token_value[++token_array_index] = '\0';
		tokenize(token_value, VARIABLE);
	}

	return FALSE;
}

BOOL variable_loop(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_value[++token_array_index] = current_char;

	if(next_char == EOF) {
		current_column++;
		token_value[++token_array_index] = '\0';
		tokenize(token_value, VARIABLE);
	}

	return FALSE;
}

BOOL variable_end(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_value[++token_array_index] = '\0';
	tokenize(token_value, VARIABLE);

	return TRUE;
}
//-----------END OF VARIABLE ACTIONS---------------------------------------------------------------------------------

// NUMBER ACTIONS
BOOL number_first_char(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_array_index = 0;
	token_value[token_array_index] = current_char;

	if(next_char == EOF) {
		current_column++;
		token_value[++token_array_index] = '\0';
		tokenize(token_value, INTEGER);
	}

	return FALSE;
}

BOOL number_loop(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_value[++token_array_index] = current_char;

	if(next_char == EOF){
		current_column++;
		token_value[++token_array_index] = '\0';
		tokenize(token_value, INTEGER);
	}

	return FALSE;
}

BOOL integer_end(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_value[++token_array_index] = '\0';
	tokenize(token_value, INTEGER);

	return TRUE;
}

BOOL float_number(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_value[++token_array_index] = current_char;

	return FALSE;
}

BOOL float_first_char(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_value[++token_array_index] = current_char;

	if(next_char == EOF){
		current_column++;
		token_value[++token_array_index] = '\0';
		tokenize(token_value, FLOAT);
	}

	return FALSE;
}

BOOL float_loop(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_value[++token_array_index] = current_char;

	if(next_char == EOF){
		current_column++;
		token_value[++token_array_index] = '\0';
		tokenize(token_value, FLOAT);
	}

	return FALSE;
}

BOOL float_end(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_value[++token_array_index] = '\0';
	tokenize(token_value, FLOAT);

	return TRUE;
}
//-----------END OF NUMBER ACTIONS---------------------------------------------------------------------------------

// STRING ACTIONS
BOOL string_beginning(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_array_index = -1;

	if(next_char == EOF) {
		printf("STRING ERROR: STRING QUOTES NOT CLOSED!\n");
	}

	return FALSE;
}

BOOL string_loop(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_value[++token_array_index] = current_char;

	if(next_char == EOF) {
		printf("STRING ERROR: STRING QUOTES NOT CLOSED!\n");
	}

	return FALSE;
}

BOOL string_escaped_char(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_value[++token_array_index] = current_char;

	if(next_char == EOF) {
		printf("STRING ERROR: STRING QUOTES NOT CLOSED!\n");
	}

	return FALSE;
}

BOOL string_end(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_value[++token_array_index] = '\0';
	tokenize(token_value, STRING);

	return FALSE; //doesn't return true because is string
}
//-----------END OF STRING ACTIONS---------------------------------------------------------------------------------

// SYMBOL ACTIONS
BOOL symbol_first_char(STATE current_state, STATE next_state, char current_char, char next_char) {
	token_array_index = 0;
	token_value[token_array_index] = current_char;

	if(next_char == EOF) {
		current_column++;
		if(is_in_single_symbols_table(token_value[token_array_index]) > -1) {
			token_value[++token_array_index] = '\0';
			tokenize(token_value, SINGLE_SYMBOL);
		} else {
			printf("SYMBOL ERROR: %c IS NOT IN SINGLE SYMBOLS TABLE!\n", token_value[token_array_index]);
		}
	}

	return FALSE;
}

BOOL single_symbol_end(STATE current_state, STATE next_state, char current_char, char next_char) {

	if(is_in_single_symbols_table(token_value[token_array_index]) > -1) {
		token_value[++token_array_index] = '\0';
		tokenize(token_value, SINGLE_SYMBOL);
	} else {
		printf("SYMBOL ERROR: %c IS NOT IN SINGLE SYMBOLS TABLE!\n", token_value[token_array_index]);
	}

	return TRUE;
}

BOOL double_symbol(STATE current_state, STATE next_state, char current_char, char next_char) {
	char single_symbol_aux[2];
	token_value[++token_array_index] = current_char;

	if(next_char == EOF) {
		current_column++;
		token_value[++token_array_index] = '\0';
		if(is_in_double_symbols_table(token_value) > -1) {
			tokenize(token_value, DOUBLE_SYMBOL);
		} //in case there are two single symbols next to each other
		else if((is_in_single_symbols_table(token_value[0]) > -1) &&
							(is_in_single_symbols_table(token_value[1]) > -1)) {
			single_symbol_aux[0] = token_value[0];
			single_symbol_aux[1] = '\0';
			tokenize(single_symbol_aux, SINGLE_SYMBOL);
			current_column++;
			single_symbol_aux[0] = token_value[1];
			single_symbol_aux[1] = '\0';
			tokenize(single_symbol_aux, SINGLE_SYMBOL);
		}
		else {
			printf("SYMBOL ERROR: %s IS NOT IN DOUBLE SYMBOLS TABLE!\n", token_value);
		}
	}

	return FALSE;
}

BOOL double_symbol_end(STATE current_state, STATE next_state, char current_char, char next_char) {
	char single_symbol_aux[2];

	token_value[++token_array_index] = '\0';
	if(is_in_double_symbols_table(token_value) > -1) {
		tokenize(token_value, DOUBLE_SYMBOL);
	} //in case there are two single symbols next to each other
	else if((is_in_single_symbols_table(token_value[0]) > -1) &&
						(is_in_single_symbols_table(token_value[1]) > -1)) {
		single_symbol_aux[0] = token_value[0];
		single_symbol_aux[1] = '\0';
		tokenize(single_symbol_aux, SINGLE_SYMBOL);
		current_column++;
		single_symbol_aux[0] = token_value[1];
		single_symbol_aux[1] = '\0';
		tokenize(single_symbol_aux, SINGLE_SYMBOL);
	}
	else {
		printf("SYMBOL ERROR: %s IS NOT IN DOUBLE SYMBOLS TABLE!\n", token_value);
	}

	return TRUE;
}

BOOL symbol_error(STATE current_state, STATE next_state, char current_char, char next_char) {

	printf("SYMBOL ERROR: %c IS NOT A POSSIBLE SYMBOL OF THE LANGUAGE!\n", current_char);

	return FALSE; //doesn't return true because is string
}
//-----------END OF SYMBOL ACTIONS---------------------------------------------------------------------------------

