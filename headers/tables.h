#ifndef TABLES_H
#define TABLES_H
  #define TABLE_MAX_SIZE    1000
  #define STRING_MAX_SIZE   100

  #define SS_TABLE_SIZE 17
  #define DS_TABLE_SIZE 6
  #define RW_TABLE_SIZE 16


  // TABLE SEARCH FUNCTIONS
  int is_in_double_symbols_table(char* symbol);
  int is_in_single_symbols_table(char symbol);
  int is_in_reserved_words_table(char* identifier);
  int is_in_integers_table(int integer);
  int is_in_floats_table(float float_number);
  int is_in_identifiers_table(char* identifier);
  int is_in_variables_table(char* variable);
  int is_in_strings_table(char* string);

  //INSERT INTO TABLE FUNCTIONS
  int insert_into_identifiers_table(char* identifier);
  int insert_into_variables_table(char* variable);
  int insert_into_strings_table(char* string);
  int insert_into_integers_table(int integer);
  int insert_into_floats_table(float float_number);

  //PRINT TABLE FUNCTIONS
  void print_reserved_words_table();
  void print_single_symbols_table();
  void print_double_symbols_table();
  void print_identifiers_table();
  void print_variables_table();
  void print_strings_table();
  void print_integers_table();
  void print_floats_table();

  //TABLES GETTERS FUNCTIONS
  char* get_reserved_word(int table_index);
  char* get_identifier(int table_index);
  char* get_string(int table_index);
  char* get_variable(int table_index);
  char get_single_symbol(int table_index);
  char* get_double_symbol(int table_index);
  int get_integer(int table_index);
  float get_float(int table_index);

#endif
