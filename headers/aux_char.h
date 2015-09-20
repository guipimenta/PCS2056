/*
	AUXILIARY CHAR FUNCTIONS
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


/*FUNCTIONS HEADERS*/
BOOL isLetter(const unsigned char c);
BOOL isNumber(const unsigned char c);

#endif