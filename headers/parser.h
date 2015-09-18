#ifndef PARSER_H
#define PARSER_H
#include <bool.h>

#define COMMAND_END '\0'

/*BEGIN TOKEN PARSER*/
#define SBB 1
#define SBE 2
#define SBG 3
#define SBI 4
#define SBN 5

/*END TOKEN PARSER*/
#define SEE 6
#define SEN 7
#define SED 8

BOOL parse_begin(WORD word);
BOOL parse_end(WORD word);

#endif