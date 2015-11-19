#include <stdio.h>
#include "../headers/aux_char.h"
#include "../headers/bool.h"
#include <string.h>
#include <ctype.h>

/*
* POSSIBLE SYMBOLS
*/
POSSIBLE_SYMBOLS_TABLE SB_TABLE = {
	'>',
	'<',
	'=',
	';',
	'%',
	'+',
	'-',
	'/',
	'*',
	'!',
	'(',
	')',
	'[',
	']',
	',',
	'&',
	'|',
  '\\',
  '_',
  '-',
  ':',
  '.',
  '#'
};

BOOL isWhiteSpace(const unsigned char c) {
	if(isspace(c))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL isPossibleSymbol(const unsigned char c)
{
	int i;

	for(i = 0; i < SBSIZE; i++)
	{
		if (c == SB_TABLE[i])
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL isLetter(const unsigned char c)
{
	if((c >= UA && c <= UZ) || (c >= LA && c <= LZ))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL isNumber(const unsigned char c)
{
	if(c >= D0 && c <= D9)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
