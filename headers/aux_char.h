/*
	AUXILIARY CHAR FUNCTIONS

	Defined to help build-up a TRANSITION TABLE
*/

#ifndef AUX_CHAR_H
#define AUX_CHAR_H
#include "bool.h"


#define OPSIZE  10
#define BOPSIZE 5

/*DEFINE SPECIAL OPERATORS*/

/*ASCII CODE TABLE*/
#define UA 65
#define UZ 90
#define LA 97
#define LZ 122

/*DECIMAL*/
#define D0 48
#define D9 57

/*LETTER CODE*/
#define LL 300
#define NL 301
#define DD 302
#define ND 303

/*LETTER CODE*/
#define WS 304
#define NW 305

/*OPERATOR CODE*/
#define OP 306
#define NO 307

/*ANY CODE*/
#define AN 320

typedef char UNARY_OPERATOR;
typedef UNARY_OPERATOR UNARY_TABLE[OPSIZE];

typedef char* BINARY_OPERATOR;
typedef BINARY_OPERATOR BINARY_TABLE[OPSIZE];



/*
* DIGIT
*
* A macro that creates a new symbol LL
* Given a char X, DIGIT will return if X is a Letter (LL)
*/
#define LETTER(X) 	(isLetter(X) 	? LL : NL)
#define DIGIT(X)  	(isNumber(X) 	? DD : ND)
#define UNARY(X) 	(isOperator(X) 	? OP : NO)
#define WHITESPACE(X)  (isWhiteSpace(X)  ? WS : NW)

/*FUNCTIONS HEADERS*/
BOOL isLetter(const unsigned char c);
BOOL isNumber(const unsigned char c);
BOOL isOperator(const unsigned char c);
BOOL isWhiteSpace(const unsigned char c);

#endif