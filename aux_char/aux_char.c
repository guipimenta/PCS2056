#include <stdio.h>
#include "../headers/aux_char.h"
#include "../headers/bool.h"
#include <string.h>
#include <ctype.h>

/*
* UNIARY OPERATORS
*/
UNARY_TABLE OP_UN_TABLE = {
	'>',
	'<',
	'=',
	';',
	'%',
	'+',
	'-',
	'/',
	'*',
	'!'
};

/*
* BINARY OPERATORS
*/
BINARY_TABLE BO_OP_TABLE = {
	"&&",
	"||",
	"<=",
	"==",
	">=",
	"!="
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

BOOL isOperator(const unsigned char c)
{
	int i;

	for(i = 0; i < OPSIZE; i++)
	{
		if (c == OP_UN_TABLE[i])
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
