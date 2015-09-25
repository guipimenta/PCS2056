#ifndef TABLES_H
#define TABLES_H
  #define TABLE_MAX_SIZE    1000
  #define STRING_MAX_SIZE   100
  
  #define SS_TABLE_SIZE 17
  #define DS_TABLE_SIZE 6


  int integers_table[TABLE_MAX_SIZE][1];
  float floats_table[TABLE_MAX_SIZE][1];
  char variables_table[TABLE_MAX_SIZE][STRING_MAX_SIZE];
  char strings_table[TABLE_MAX_SIZE][STRING_MAX_SIZE];
  char identifiers_table[TABLE_MAX_SIZE][STRING_MAX_SIZE];

  int integers_table_index;
  int floats_table_index;
  int variables_table_index;
  int strings_table_index;
  int identifiers_table_index;

  int is_in_double_symbols_table(char* symbol);
  int is_in_single_symbols_table(char symbol);

#endif