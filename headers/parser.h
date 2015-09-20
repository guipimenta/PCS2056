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

/*IDENTIFIER TOKEN PARSER*/
#define SIH 9		// State Identifier Hashtag
#define SIL 10		// State Identifier Any

/*IF TOKEN PARSER*/
#define SII 11
#define SIF 12

/*INTEGER PARSER*/
#define SNI 13
#define SND 14
#define SNF	15

/*DECLARE PARSER*/
#define SDD 16
#define SDE 17
#define SDC 18
#define SDL 19
#define SDA 20
#define SDR 21
#define SDEE 22

/*DEFINE FEND*/
#define SFF 24
#define SFE 25
#define SFN 26
#define SFD 27


BOOL parse_begin(WORD word);
BOOL parse_end(WORD word);
BOOL parse_identifier(WORD word);
BOOL parse_if(WORD word);
BOOL parse_number(WORD word);
BOOL parse_declare(WORD word);
BOOL parse_fend(WORD word);

#endif