#ifndef TABLES_H
#define TABLES_H
  #include "tokenizer.h"

  #define TABLE_MAX_SIZE    1000
  #define STRING_MAX_SIZE   100
  #define SYMBOLS_TABLE_MAX 50

  #define SS_TABLE_SIZE 19
  #define RW_TABLE_SIZE 21
  #define TP_TABLE_SIZE 4

  // TABLE SEARCH FUNCTIONS
  int is_in_single_symbols_table(char symbol);
  int is_in_reserved_words_table(char* identifier);
  int is_in_types_table(char* identifier);
  int is_in_integers_table(char* integer);
  int is_in_floats_table(char* float_number);
  // int is_in_identifiers_table(char* identifier);
  // int is_in_variables_table(char* variable);
  int is_in_strings_table(char* string);
  int is_in_symbols_table(TOKEN_CLASS token_class, char* value);

  //INSERT INTO TABLE FUNCTIONS
  // int insert_into_identifiers_table(char* identifier);
  // int insert_into_variables_table(char* variable);
  int insert_into_symbols_table(TOKEN_CLASS token_class, char* value);
  int insert_into_strings_table(char* string);
  int insert_into_integers_table(char* integer);
  int insert_into_floats_table(char* float_number);

  //PRINT TABLE FUNCTIONS
  void print_reserved_words_table();
  void print_types_table();
  void print_single_symbols_table();
  // void print_identifiers_table();
  // void print_variables_table();
  void print_symbols_table();
  void print_strings_table();
  void print_integers_table();
  void print_floats_table();

  //TABLES GETTERS FUNCTIONS
  char* get_reserved_word(int table_index);
  char* get_type(int table_index);
  // char* get_identifier(int table_index);
  char* get_string(int table_index);
  // char* get_variable(int table_index);
  char* get_symbol(int table_index);
  char get_single_symbol(int table_index);
  char* get_integer(int table_index);
  char* get_float(int table_index);

  void set_current_symbols_table (int symbol_table);
  void increment_symbols_table_array_index(void);

  void initialize_symbol_table (int symbol_table);

#endif
