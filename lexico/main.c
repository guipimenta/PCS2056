#include "../headers/tokenizer.h"
#include "../headers/tables.h"
#include <stdio.h>

int main()
{
  printf("Hello World!\n");

  read_file("entrada.txt");

  print_reserved_words_table();
  print_single_symbols_table();
  print_double_symbols_table();
  print_identifiers_table();
  print_variables_table();
  print_strings_table();
  print_integers_table();
  print_floats_table();

  return 0;
}
