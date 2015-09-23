CC=gcc
AR=ar
CFLAGS=-I.
# lexical_error: lexico/lexical_error.c aux_char/aux_char.c lexico/transdutor.c lexico/lexical.c
# 	$(CC) -o bin/lexical aux_char/aux_char.c  lexico/lexical_error.c lexico/transdutor.c lexico/lexical.c -I./headers/

tokenizer: aux_char/aux_char.c lexico/tokenizer.c lexico/automata.c
	$(CC) -o bin/lexico aux_char/aux_char.c  lexico/tokenizer.c lexico/automata.c -I./headers/