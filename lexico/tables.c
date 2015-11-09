#include <stdio.h>
#include <string.h>

#include "../headers/tables.h"
#include "../headers/bool.h"

typedef struct {
  char value[STRING_MAX_SIZE];
  TOKEN_CLASS token_class;
} SYMBOL;

typedef SYMBOL SYMBOLS_TABLE[TABLE_MAX_SIZE];

char integers_table[TABLE_MAX_SIZE][STRING_MAX_SIZE];
char floats_table[TABLE_MAX_SIZE][STRING_MAX_SIZE];
// char variables_table[TABLE_MAX_SIZE][STRING_MAX_SIZE];
char strings_table[TABLE_MAX_SIZE][STRING_MAX_SIZE];
// char identifiers_table[TABLE_MAX_SIZE][STRING_MAX_SIZE];
SYMBOLS_TABLE symbols_table;

int integers_table_index = 0;
int floats_table_index = 0;
// int variables_table_index = 0;
int strings_table_index = 0;
// int identifiers_table_index = 0;
int symbols_table_index = 0;

/*
* SINGLE SYMBOLS
*/
char single_symbols_table[SS_TABLE_SIZE] = {
  '>',
  '<',
  '=',
  ';',
  '%',
  '+',
  '-',
  '/',
  '*',
  '!',
  '(',
  ')',
  '{',
  '}',
  '[',
  ']',
  ',',
  '"',
  '|',
  '&'
};

/*
* DOUBLE SYMBOLS
*/
// char* double_symbols_table[DS_TABLE_SIZE] = {
//   "&&",
//   "||",
//   "<=",
//   "==",
//   ">=",
//   "!="
// };

/*
* RESERVED WORDS SYMBOLS
*/
char* reserved_words_table[RW_TABLE_SIZE] = {
  "program",
  "declare",
  "begin",
  "end",
  "boolean",
  "integer",
  "float",
  "string",
  "void",
  "if",
  "fend",
  "else",
  "lend",
  "def",
  "while",
  "wend",
  "input",
  "output",
  "then",
  "TRUE",
  "FALSE",
  "break",
  "return"
};

// TABLE SEARCH FUNCTIONS
int is_in_single_symbols_table(char symbol) {
  int i;
  int ret_value = -1;

  for(i=0; i < SS_TABLE_SIZE; i++) {
    if(symbol == single_symbols_table[i]) {
      ret_value = i;
      break;
    }
  }

  return ret_value;
}

int is_in_reserved_words_table(char* identifier) {
  int i = 0;
  int ret_value = -1;

  for(i=0; i < RW_TABLE_SIZE; i++) {
    if(strcmp(identifier, reserved_words_table[i]) == 0) {
      ret_value = i;
      break;
    }
  }

  return ret_value;
}

int is_in_integers_table(char* integer) {
  int i = 0;
  int ret_value = -1;

  for(i=0; i < integers_table_index; i++) {
    if(strcmp(integer, integers_table[i]) == 0) {
      ret_value = i;
      break;
    }
  }

  return ret_value;
}

int is_in_floats_table(char* float_number) {
  int i = 0;
  int ret_value = -1;

  for(i=0; i < floats_table_index; i++) {
    if(strcmp(float_number, floats_table[i]) == 0) {
      ret_value = i;
      break;
    }
  }

  return ret_value;
}

int is_in_symbols_table(TOKEN_CLASS token_class, char* value) {
  int i = 0;
  int ret_value = -1;

  for(i=0; i < symbols_table_index; i++) {
    if(symbols_table[i].token_class == token_class && strcmp(value, symbols_table[i].value) == 0) {
      ret_value = i;
      break;
    }
  }

  return ret_value;
}

// int is_in_identifiers_table(char* identifier) {
//   int i = 0;
//   int ret_value = -1;

//   for(i=0; i < identifiers_table_index; i++) {
//     if(strcmp(identifier, identifiers_table[i]) == 0) {
//       ret_value = i;
//       break;
//     }
//   }

//   return ret_value;
// }

// int is_in_variables_table(char* variable) {
//   int i = 0;
//   int ret_value = -1;

//   for(i=0; i < variables_table_index; i++) {
//     if(strcmp(variable, variables_table[i]) == 0) {
//       ret_value = i;
//       break;
//     }
//   }

//   return ret_value;
// }

int is_in_strings_table(char* string) {
  int i = 0;
  int ret_value = -1;

  for(i=0; i < strings_table_index; i++) {
    if(strcmp(string, strings_table[i]) == 0) {
      ret_value = i;
      break;
    }
  }

  return ret_value;
}

//INSERT INTO TABLE FUNCTIONS
int insert_into_symbols_table(TOKEN_CLASS token_class, char* value) {
  int ret_value;


  ret_value = is_in_symbols_table(token_class, value);
  if(ret_value == -1) {
    symbols_table[symbols_table_index].token_class = token_class;
    strcpy(symbols_table[symbols_table_index].value, value);
    ret_value = symbols_table_index;
    symbols_table_index++;
  }

  return ret_value;
}

// int insert_into_identifiers_table(char* identifier) {
//   int ret_value;


//   ret_value = is_in_identifiers_table(identifier);
//   if(ret_value == -1) {
//     strcpy(identifiers_table[identifiers_table_index], identifier);
//     ret_value = identifiers_table_index;
//     identifiers_table_index++;
//   }

//   return ret_value;
// }

// int insert_into_variables_table(char* variable) {
//   int ret_value;


//   ret_value = is_in_variables_table(variable);
//   if(ret_value == -1) {
//     strcpy(variables_table[variables_table_index], variable);
//     ret_value = variables_table_index;
//     variables_table_index++;
//   }

//   return ret_value;
// }

int insert_into_strings_table(char* string) {
  int ret_value;


  ret_value = is_in_strings_table(string);
  if(ret_value == -1) {
    strcpy(strings_table[strings_table_index], string);
    ret_value = strings_table_index;
    strings_table_index++;
  }

  return ret_value;
}

int insert_into_integers_table(char* integer) {
  int ret_value;


  ret_value = is_in_integers_table(integer);
  if(ret_value == -1) {
    strcpy(integers_table[integers_table_index], integer);
    ret_value = integers_table_index;
    integers_table_index++;
  }

  return ret_value;
}

int insert_into_floats_table(char* float_number) {
  int ret_value;


  ret_value = is_in_floats_table(float_number);
  if(ret_value == -1) {
    strcpy(floats_table[floats_table_index], float_number);
    ret_value = floats_table_index;
    floats_table_index++;
  }

  return ret_value;
}

//PRINT TABLE FUNCTIONS
void print_reserved_words_table() {
  int i;

  printf("-----RESERVED WORDS TABLE-----\n");

  for(i=0; i < RW_TABLE_SIZE; i++) {
    printf("    %2d  -  %s\n", i, reserved_words_table[i]);
  }
  printf("\n\n");
}

void print_single_symbols_table() {
  int i;

  printf("-----SINGLE SYMBOLS TABLE-----\n");

  for(i=0; i < SS_TABLE_SIZE; i++) {
    printf("    %2d  -  %c\n", i, single_symbols_table[i]);
  }
  printf("\n\n");
}

void print_symbols_table() {
  int i = 0;
  int count = 0;

  printf("-----IDENTIFIERS TABLE-----\n");

  for(i=0; i < symbols_table_index; i++) {
    if (symbols_table[i].token_class == IDENTIFIER) {
      printf("    %3d  -  %s\n", count, symbols_table[i].value);
      count++;
    }
  }
  printf("\n\n");

  printf("-----VARIABLES TABLE-----\n");
  count = 0;
  for(i=0; i < symbols_table_index; i++) {
    if (symbols_table[i].token_class == VARIABLE) {
      printf("    %3d  -  %s\n", count, symbols_table[i].value);
      count++;
    }
  }
  printf("\n\n");
}

// void print_identifiers_table() {
//   int i;

//   printf("-----IDENTIFIERS TABLE-----\n");

//   for(i=0; i < identifiers_table_index; i++) {
//     printf("    %3d  -  %s\n", i, identifiers_table[i]);
//   }
//   printf("\n\n");
// }

// void print_variables_table() {
//   int i;

//   printf("-----VARIABLES TABLE-----\n");

//   for(i=0; i < variables_table_index; i++) {
//     printf("    %3d  -  %s\n", i, variables_table[i]);
//   }
//   printf("\n\n");
// }

void print_strings_table() {
  int i;

  printf("-----STRINGS TABLE-----\n");

  for(i=0; i < strings_table_index; i++) {
    printf("    %3d  -  %s\n", i, strings_table[i]);
  }
  printf("\n\n");
}

void print_integers_table() {
  int i;

  printf("-----INTEGERS TABLE-----\n");

  for(i=0; i < integers_table_index; i++) {
    printf("    %3d  -  %s\n", i, integers_table[i]);
  }
  printf("\n\n");
}

void print_floats_table() {
  int i;

  printf("-----FLOATS TABLE-----\n");

  for(i=0; i < floats_table_index; i++) {
    printf("    %3d  -  %s\n", i, floats_table[i]);
  }
  printf("\n\n");
}

//TABLES GETTERS FUNCTIONS
char* get_reserved_word(int table_index) {
  return reserved_words_table[table_index];
}

// char* get_identifier(int table_index) {
//   return identifiers_table[table_index];
// }

char* get_symbol(int table_index) {
  return symbols_table[table_index].value;
}

char* get_string(int table_index) {
  return strings_table[table_index];
}

// char* get_variable(int table_index) {
//   return variables_table[table_index];
// }

char get_single_symbol(int table_index) {
  return single_symbols_table[table_index];
}

char* get_integer(int table_index) {
  return integers_table[table_index];
}

char* get_float(int table_index) {
  return floats_table[table_index];
}
