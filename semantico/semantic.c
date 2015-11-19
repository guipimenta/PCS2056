#include <stdio.h>
#include <string.h>

#include "../headers/tables.h"
#include "../headers/bool.h"

void initialize_symbols_table(void) {
  increment_symbols_table_array_index();

  initialize_symbol_table(0);

  set_current_symbols_table(0);
}

void semantico_tbd(void) {
  printf("TODO\n");
}
