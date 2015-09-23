/*
	AUXILIARY CHAR FUNCTIONS

	Defined to help build-up a TRANSITION TABLE
*/

#ifndef AUX_CHAR_H
#define AUX_CHAR_H
#include <bool.h>


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


/*
* DIGIT
*
* A macro that creates a new symbol LL
* Given a char X, DIGIT will return if X is a Letter (LL)
*/
#define LETTER(X) (isLetter(X) ? LL : NL)

/*FUNCTIONS HEADERS*/
BOOL isLetter(const unsigned char c);
BOOL isNumber(const unsigned char c);

#endif