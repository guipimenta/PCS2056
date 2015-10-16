CC=gcc
AR=ar
CFLAGS=-I.
# lexical_error: lexico/lexical_error.c aux_char/aux_char.c lexico/transdutor.c lexico/lexical.c
# 	$(CC) -o bin/lexical aux_char/aux_char.c  lexico/lexical_error.c lexico/transdutor.c lexico/lexical.c -I./headers/

tokenizer: aux_char/aux_char.c lexico/main.c lexico/tables.c lexico/tokenizer.c lexico/automata.c
	$(CC) -o bin/lexico lexico/main.c lexico/tables.c aux_char/aux_char.c aux_char/aux_number.c  lexico/tokenizer.c lexico/automata.c -I./headers/