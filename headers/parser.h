#ifndef PARSER_H
#define PARSER_H
#include <bool.h>

#define COMMAND_END '\n'

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

/*DEFINE ELSE*/
#define SLE 28
#define SLL 29
#define SLS 30
#define SLEE 31

/*LEND*/
#define SENL 32
#define SENE 33
#define SENN 34
#define SEND 35

/*WHILE*/
#define SWW 33
#define SWH 34
#define SWI 35
#define SWL 36
#define SWE 37

/*WEND*/
#define SWEW 38
#define SWEE 39
#define SWEN 40
#define SWED 41

/*@READ*/
#define SRAT 42
#define SRR	 43
#define SRE  44
#define SRA  45
#define SRD  46

/*WRITE*/
#define SWAT 47
#define SWRW 48
#define SWRR 49
#define SWRI 50
#define SWRT 51
#define SWRE 52

/*COMMENT*/
#define SCS1 55
#define SCS2 56

/*UNDEFINED STATES*/
/*COULD BE ELSE OR END*/
#define SUE	100
/*COULD BE WHILE OR WEND*/
#define SUW 101
/*@ is command*/
#define SUAT 102


BOOL parse_begin(WORD word);
BOOL parse_end(WORD word);
BOOL parse_identifier(WORD word);
BOOL parse_if(WORD word);
BOOL parse_number(WORD word);
BOOL parse_declare(WORD word);
BOOL parse_fend(WORD word);
BOOL parse_else(WORD word);
BOOL parse_lend(WORD word);
BOOL parse_while(WORD word);
BOOL parse_wend(WORD word);
BOOL parse_read(WORD word);
BOOL parse_write(WORD word);
BOOL parse_comment(WORD word);

#endif