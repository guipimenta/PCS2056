#ifndef TABLES_H
#define TABLES_H
  #define TABLE_MAX_SIZE    1000
  #define STRING_MAX_SIZE   100

  #define SS_TABLE_SIZE 17
  #define DS_TABLE_SIZE 6
  #define RW_TABLE_SIZE 16


  int integers_table[TABLE_MAX_SIZE][1];
  float floats_table[TABLE_MAX_SIZE][1];
  char variables_table[TABLE_MAX_SIZE][STRING_MAX_SIZE];
  char strings_table[TABLE_MAX_SIZE][STRING_MAX_SIZE];
  char identifiers_table[TABLE_MAX_SIZE][STRING_MAX_SIZE];

  static int integers_table_index = 0;
  static int floats_table_index = 0;
  static int variables_table_index = 0;
  static int strings_table_index = 0;
  static int identifiers_table_index = 0;

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

#endif
