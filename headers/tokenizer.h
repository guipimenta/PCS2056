#ifndef TOKENIZER_H
#define TOKENIZER_H
#include "bool.h"
#define TMAX 1000
#define SMAX 1000
#define WMAX 1000

typedef char  TOKEN_VALUE[WMAX];

typedef enum {
  VARIABLE,
  IDENTIFIER,
  RESERVED_WORD,
  INTEGER,
  FLOAT,
  STRING,
  SINGLE_SYMBOL
} TOKEN_CLASS;



/*
* Tokens contains a single identification number
* and it's value, string representation for a token
* TOKEN ID  |   TOKEN VALUE
* ------------------------------------------------------
*     ISBN    |    begin
*   ISED    |    end
*   ISIS    |    #<identifier> (any sequence of letters)
*   ISERR   |    <error state> (not part of language)
*/
typedef struct {
  TOKEN_CLASS token_class;
  int table_index;
    int row;
    int column;
} TOKEN;

typedef enum states {
  S0,       //initial state
  SVAR,     //variable state
  SIDENT,   //identifier state
  SINT,     //integer state 1
  SFLOAT1,  //float state 1
  SFLOAT2,  //float state 2
  SCOMM1,   // comment state 1
  SCOMM2,   //comment state 2
  SSTR1,    //string state 1
  SSTR2,    //string state 2
  SSYMB1,   //symbol state 1
  SERROR
} STATE;

typedef struct {
  int trigger;
  STATE next;
  BOOL (*action)(STATE, STATE, char, char, BOOL *);
} TRANSITION;

typedef struct {
  STATE id;
  TRANSITION transitions[TMAX];
} AUTOMATA;

typedef AUTOMATA TRANS_TABLE[SMAX];

BOOL get_token(FILE *f, TOKEN *token_found, BOOL *endOfProgram);
void print_token(TOKEN token);
char* get_token_value(TOKEN_CLASS token_class, int table_index);

#endif
