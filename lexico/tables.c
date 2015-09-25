#include <stdio.h>
#include <string.h>

#include "../headers/tables.h"
#include "../headers/bool.h"

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
  ','
};

/*
* DOUBLE SYMBOLS
*/
char* double_symbols_table[DS_TABLE_SIZE] = {
  "&&",
  "||",
  "<=",
  "==",
  ">=",
  "!="
};

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

int is_in_double_symbols_table(char* symbol) {
  int i = 0;
  int ret_value = -1;

  for(i=0; i < DS_TABLE_SIZE; i++) {
    if(strcmp(symbol, double_symbols_table[i]) == 0) {
      ret_value = i;
      break;
    }
  }

  return ret_value;
}

