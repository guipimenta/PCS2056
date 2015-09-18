CC=gcc
CFLAGS=-I.
lexical: lexico/transdutor.c aux_char/aux_char.c
	$(CC) -o bin/lexical aux_char/aux_char.c lexico/transdutor.c -I.