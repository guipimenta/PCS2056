CC=gcc
AR=ar
CFLAGS=-I.
# lexical_error: lexico/lexical_error.c aux_char/aux_char.c lexico/transdutor.c lexico/lexical.c
# 	$(CC) -o bin/lexical aux_char/aux_char.c  lexico/lexical_error.c lexico/transdutor.c lexico/lexical.c -I./headers/

tokenizer: sintatico/syntatic.c lexico/main.c lexico/tables.c lexico/tokenizer.c aux_char/aux_char.c
	$(CC) -std=c99 -o bin/compiler sintatico/syntatic.c lexico/main.c lexico/tables.c lexico/tokenizer.c aux_char/aux_char.c -I./headers/