#include <stdio.h>
#include <string.h>
#include <transdutor.h>
#include <aux_char.h>
#include <lexical_error.h>
#include <parser.h>

// Test Lexical Interpreter
int main() 
{
	WORD to_token;
	TOKEN t;
	while(1) {
		printf(">> ");
		scanf("%s", to_token);
		if(to_token[0] != '\n')
			t = tokenizer(to_token);
	}
	return 0;
}

TOKEN tokenizer(WORD word)
{
	int  i 	= 0;
	char c 	= word[i];
	STATE current = S0;
	TOKEN tokenized;
	while(TRUE)
	{
		switch(c)
		{
			case 'b':
				if(current == S0)
				{
					if(parse_begin(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TOKENS_ID.TBEGIN);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_BEGIN_CODE);
					}
					return tokenized;
				}
				break;
			case 'd':
				if(current == S0)
				{
					if(parse_declare(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TOKENS_ID.TDE);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_DECLARE_CODE);
					}
					return tokenized;
				}
				break;
			case 'e':
				if(current == S0)
				{
					current = SEE;
				}
				break;
			case 'n':
				if(current == SEE)
				{
					if(parse_end(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TOKENS_ID.TEND);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_END_CODE);
					}
					return tokenized;
				}
				break;
			case '#':
				if(current == S0)
				{
					if(parse_identifier(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TOKENS_ID.TEND);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_IDENTIFICATION_CODE);
					}
					return tokenized;
				}
				break;
			case 'i':
				if(current == S0)
				{
					if(parse_number(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TOKENS_ID.TIN);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_NUMBER_CODE);
					}
					return tokenized;
				}
				break;
			case BREAKLINE:
				break;
			default:
				if(isNumber(c) == TRUE)
				{
					if(parse_number(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TOKENS_ID.TIF);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_NUMBER_CODE);
					}
					return tokenized;
				}
				throw_lexical_error(LEX_ERROR_UNKOWN_CODE);
				return tokenized;
				break;

		}
		i++;
		c = word[i];
	} 
}

BOOL parse_begin(WORD word)
{
	int i = 0;
	unsigned char c	= word[i];
	STATE current = S0;
	while(TRUE)
	{
		switch(c)
		{
			case 'b':
				if(current == S0) {
					current = SBB;
					break;
				} 
				else 
				{
					return FALSE;
				}
			case 'e':
				if(current == SBB) {
					current = SBE;
					break;
				}
				else
				{
					return FALSE;
				}
			case 'g':
				if(current == SBE) {
					current = SBG;
					break;
				}
				else {
					return FALSE;
				}
			case 'i':
				if(current == SBG) {
					current = SBI;
					break;
				}
				else
				{
					return FALSE;
				}
			case 'n':
				if(current == SBI) {
					current = SBN;
					break;
				}
				else
				{
					return FALSE;
				}
			case COMMAND_END:
				if(current == SBN)
					return TRUE;
			default:
				return FALSE;
		}
		i++;
		c = word[i];
	}
}

BOOL parse_end(WORD word)
{
	int i = 0;
	unsigned char c	= word[i];
	STATE current = S0;
	while(TRUE)
	{
		switch(c)
		{
			case 'e':
				if(current == S0) {
					current = SEE;
					break;
				}
				else 
				{
					return FALSE;
				}
			case 'n':
				if(current == SEE) {
					current = SEN;
					break;
				}
				else 
				{
					return FALSE;
				}
			case 'd':
				if(current == SEN) {
					current = SED;
					break;
				}
				else 
				{
					return FALSE;
				}
			case COMMAND_END:
				if(current == SED)
					return TRUE;
			default:
				return FALSE;
		}
		i++;
		c = word[i];
	}
}

BOOL parse_identifier(WORD word)
{
	int i = 0;
	unsigned char c	= word[i];
	STATE current = S0;
	while(TRUE)
	{
		switch(c)
		{
			case '#':
				if(current == S0) {
					current = SIH;
					break;
				}
				else 
				{
					return FALSE;
				}
			case COMMAND_END:
				if(current == SIH)
					return TRUE;
			default:
				if(current == SIH)
				{
					if(!isLetter(c) == TRUE)
					{
						return FALSE;
					}
				}
		}
		i++;
		c = word[i];
	}
}

BOOL parse_if(WORD word) 
{
	int i = 0;
	unsigned char c	= word[i];
	STATE current = S0;
	while(TRUE)
	{
		switch(c)
		{
			case 'i':
				if(current == S0) 
				{
					current = SII;
					break;
				}
				else 
				{
					return FALSE;
				}
				break;
			case 'f':
				if(current == SII)
				{
					current = SIF;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case COMMAND_END:
				if(current == SIF)
					return TRUE;
			default:
				return FALSE;
		}
		i++;
		c = word[i];
	}
	return FALSE;
}

BOOL parse_number(WORD word)
{
	int i = 0;
	unsigned char c	= word[i];
	STATE current = S0;
	while(TRUE)
	{
		switch(c)
		{
			case '.':
				if(current == SNI) 
				{
					current = SND;
					break;
				}
				else 
				{
					return FALSE;
				}
				break;
			case COMMAND_END:
				if(current == SNF || current == SNI)
					return TRUE;
				break;
			default:
				if(isNumber(c) == TRUE)
				{
					if(current == SND)
					{
						current = SNF;
					}
					if(current == S0)
					{
						current = SNI;
					}
				}
				else
					return FALSE;
		}
		i++;
		c = word[i];
	}
	return FALSE;
}

BOOL parse_declare(WORD word) 
{
	int i = 0;
	unsigned char c	= word[i];
	STATE current = S0;
	while(TRUE)
	{
		switch(c)
		{
			printf("%d\n", c);
			case 'd':
				if(current == S0) 
				{
					current = SDD;
					break;
				}
				else 
				{
					return FALSE;
				}
				break;
			case 'e':
				if(current == SDD)
				{
					current = SDE;
					break;
				}
				else if(current == SDR)
				{
					current = SDEE;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'c':
				if(current == SDE)
				{
					current = SDC;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'l':
				if(current == SDC)
				{
					current = SDL;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'a':
				if(current == SDL)
				{
					current = SDA;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'r':
				if(current == SDA)
				{
					current = SDR;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case COMMAND_END:
				if(current == SDEE)
					return TRUE;
			default:
				return FALSE;
		}
		i++;
		c = word[i];
	}
	return FALSE;
}
