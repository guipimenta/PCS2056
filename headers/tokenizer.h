#include "../headers/automata.h"

#ifndef TOKENIZER_H
#define TOKENIZER_H

#define WMAX	1000

typedef char 	TOKEN_VALUE[WMAX];

typedef enum {VARIABLE,
              IDENTIFIER,
              RESERVED_WORD,
              INTEGER,
              FLOAT,
              STRING,
              SIMPLE_OPERATOR,
              DOUBLE_OPERATOR} TOKEN_CLASS;

/*
* Tokens contains a single identification number
* and it's value, string representation for a token
*	TOKEN ID  |   TOKEN VALUE
*	------------------------------------------------------
*     ISBN 	  |    begin
*	  ISED	  |	   end 
*	  ISIS	  |	   #<identifier> (any sequence of letters)
*	  ISERR   |	   <error state> (not part of language)
*/
typedef struct {
		TOKEN_CLASS id;
		int table_index;
} TOKEN;

void read_file(char* file_name);

// ACTIONS FUNCITONS
void identifier_first_char(STATE current_state, STATE next_state, char current_char, char next_char);
void identifier_loop(STATE current_state, STATE next_state, char current_char, char next_char);


#endif