#include <stdio.h>
#include <aux_char.h>
#include <bool.h>
#include <string.h>

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
	">="
};

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