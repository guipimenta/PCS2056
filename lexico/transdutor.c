#include <stdio.h>
#include <string.h>
#include <transdutor.h>
#include <aux_char.h>
#include <lexical_error.h>
#include <parser.h>


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
						CREATE_TOKEN(tokenized, TBEGIN);
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
						CREATE_TOKEN(tokenized, TDE);
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
					current = SUE;
				}
				if(current == SUW)
				{
					if(parse_wend(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TWE);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_WEND_CODE);
					}
					return tokenized;
				}
				break;
			case 'n':
				if(current == SUE)
				{
					if(parse_end(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TEND);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_END_CODE);
					}
					return tokenized;
				}
			case 'l':
				if(current == S0)
				{
					if(parse_lend(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TLE);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_LEND_CODE);
					}
					return tokenized;
				}
				else if(current == SUE)
				{
					if(parse_else(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TEND);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_ELSE_CODE);
					}
					return tokenized;
				}
			case '#':
				if(current == S0)
				{
					if(parse_identifier(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TEND);
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
					if(parse_if(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TIF);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_IF_CODE);
					}
					return tokenized;
				}
				break;
			case 'f':
				if(current == S0)
				{
					if(parse_fend(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TIN);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_FEND_CODE);
					}
					return tokenized;
				}
				break;
			case 'w':
				if(current == S0)
				{
					current = SUW;	
				}
				else if(current == SUAT)
				{
					if(parse_write(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TWW);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_WRITE_CODE);
					}
					return tokenized;
				}
				break;
			case 'h':
				if(current == SUW)
				{
					if(parse_while(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TWH);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_WHILE_CODE);
					}
					return tokenized;
				}
				break;
			case '@':
				if(current == S0)
				{
					current = SUAT;
				}
				break;
			case 'r':
				if(current == SUAT)
				{
					if(parse_read(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TWH);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_READ_CODE);
					}
					return tokenized;
				}
			case '/':
				if(current == S0)
				{
					if(parse_comment(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TCC);
					}
					else 
					{
						throw_lexical_error(LEX_ERROR_COMMENT_CODE);
					}
					return tokenized;
				}
			case BREAKLINE:
				if(current == S0)
				{
					CREATE_TOKEN(tokenized, TNU);
					return tokenized;
				}
				break;
			default:
				if(isNumber(c) == TRUE)
				{
					if(parse_number(word) == TRUE)
					{
						CREATE_TOKEN(tokenized, TIN);
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

BOOL parse_fend(WORD word)
{
	int i = 0;
	unsigned char c	= word[i];
	STATE current = S0;
	while(TRUE)
	{
		switch(c)
		{
			case 'f':
				if(current == S0) 
				{
					current = SFF;
					break;
				}
				else 
				{
					return FALSE;
				}
				break;
			case 'e':
				if(current == SFF)
				{
					current = SFN;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'n':
				if(current == SFN)
				{
					current = SFE;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'd':
				if(current == SFE)
				{
					current = SFD;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case COMMAND_END:
				if(current == SFD)
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

BOOL parse_else(WORD word)
{
	int i = 0;
	unsigned char c	= word[i];
	STATE current = S0;
	while(TRUE)
	{
		switch(c)
		{
			case 'e':
				if(current == S0) 
				{
					current = SLE;
					break;
				}
				else if(current == SLS)
				{
					current = SLEE;
					break;
				}
				else 
				{
					return FALSE;
				}
				break;
			case 'l':
				if(current == SLE)
				{
					current = SLL;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 's':
				if(current == SLL)
				{
					current = SLS;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case COMMAND_END:
				if(current == SLEE)
					return TRUE;
			default:
				return FALSE;
		}
		i++;
		c = word[i];
	}
	return FALSE;
}

BOOL parse_lend(WORD word)
{
	int i = 0;
	unsigned char c	= word[i];
	STATE current = S0;
	while(TRUE)
	{
		switch(c)
		{
			case 'l':
				if(current == S0) 
				{
					current = SENL;
					break;
				}
				else 
				{
					return FALSE;
				}
				break;
			case 'e':
				if(current == SENL)
				{
					current = SENE;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'n':
				if(current == SENE)
				{
					current = SENN;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'd':
				if(current == SENN)
				{
					current = SEND;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case COMMAND_END:
				if(current == SEND)
					return TRUE;
			default:
				return FALSE;
		}
		i++;
		c = word[i];
	}
	return FALSE;	
}

BOOL parse_while(WORD word)
{
	int i = 0;
	unsigned char c	= word[i];
	STATE current = S0;
	while(TRUE)
	{
		switch(c)
		{
			case 'w':
				if(current == S0) 
				{
					current = SWW;
					break;
				}
				else 
				{
					return FALSE;
				}
				break;
			case 'h':
				if(current == SWW)
				{
					current = SWH;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'i':
				if(current == SWH)
				{
					current = SWI;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'l':
				if(current == SWI)
				{
					current = SWL;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'e':
				if(current == SWL)
				{
					current = SWE;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case COMMAND_END:
				if(current == SWE)
					return TRUE;
			default:
				return FALSE;
		}
		i++;
		c = word[i];
	}
	return FALSE;	
}

BOOL parse_wend(WORD word)
{
	int i = 0;
	unsigned char c	= word[i];
	STATE current = S0;
	while(TRUE)
	{
		switch(c)
		{
			case 'w':
				if(current == S0) 
				{
					current = SWEW;
					break;
				}
				else 
				{
					return FALSE;
				}
				break;
			case 'e':
				if(current == SWEW)
				{
					current = SWEE;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'n':
				if(current == SWEE)
				{
					current = SWEN;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'd':
				if(current == SWEN)
				{
					current = SWED;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case COMMAND_END:
				if(current == SWED)
					return TRUE;
			default:
				return FALSE;
		}
		i++;
		c = word[i];
	}
	return FALSE;
}

BOOL parse_read(WORD word)
{
	int i = 0;
	unsigned char c	= word[i];
	STATE current = S0;
	while(TRUE)
	{
		switch(c)
		{
			case '@':
				if(current == S0) 
				{
					current = SRAT;
					break;
				}
				else 
				{
					return FALSE;
				}
				break;
			case 'r':
				if(current == SRAT)
				{
					current = SRR;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'e':
				if(current == SRR)
				{
					current = SRE;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'a':
				if(current == SRE)
				{
					current = SRA;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'd':
				if(current == SRA)
				{
					current = SRD;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case COMMAND_END:
				if(current == SRD)
					return TRUE;
			default:
				return FALSE;
		}
		i++;
		c = word[i];
	}
	return FALSE;
}

BOOL parse_write(WORD word)
{
	int i = 0;
	unsigned char c	= word[i];
	STATE current = S0;
	while(TRUE)
	{
		switch(c)
		{
			case '@':
				if(current == S0) 
				{
					current = SWAT;
					break;
				}
				else 
				{
					return FALSE;
				}
				break;
			case 'w':
				if(current == SWAT)
				{
					current = SWRW;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'r':
				if(current == SWRW)
				{
					current = SWRR;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'i':
				if(current == SWRR)
				{
					current = SWRI;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 't':
				if(current == SWRI)
				{
					current = SWRT;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case 'e':
				if(current == SWRT)
				{
					current = SWRE;
					break;
				}
				else
				{
					return FALSE;
				}
				break;
			case COMMAND_END:
				if(current == SWRE)
					return TRUE;
			default:
				return FALSE;
		}
		i++;
		c = word[i];
	}
	return FALSE;
}

BOOL parse_comment(WORD word)
{
		int i = 0;
	unsigned char c	= word[i];
	STATE current = S0;
	while(TRUE)
	{
		switch(c)
		{
			case '/':
				if(current == S0) 
				{
					current = SCS1;
					break;
				}
				else if(current == SCS1)
				{
					current = SCS2;
				}
				break;
			case COMMAND_END:
				if(current == SCS2)
					return TRUE;
			default:
				return FALSE;
		}
		i++;
		c = word[i];
	}
	return FALSE;
}
