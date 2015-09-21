#include <stdio.h>
#include <aux_char.h>
#include <bool.h>

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