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
		printf(">> %s", to_token);
		t = tokenizer(to_token);
		printf(">> %d\n", t.id);
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
					current = SI;
				}
				break;
			case BREAKLINE:
				if(current == SI)
				{
					CREATE_TOKEN(tokenized, TOKENS_ID.TID);
					return tokenized;
				}
				break;
			default:
				if(current == SI)
				{
					if(!isLetter(c) == FALSE)
					{
						throw_lexical_error(LEX_ERROR_IDENTIFICATION_CODE);
						return tokenized;
					}
				}
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
		printf(" >> %c\n", c);
		printf(" >> %d\n", c);
		switch(c)
		{
			case 'b':
				if(current == S0) {
					current = SBB;
					break;
				}
			case 'e':
				if(current == SBB) {
					current = SBE;
					break;
				}
			case 'g':
				if(current == SBE) {
					current = SBG;
					break;
				}
			case 'i':
				if(current == SBG) {
					current = SBI;
					break;
				}
			case 'n':
				if(current == SBI) {
					current = SBN;
					break;
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
		printf(" >> %c\n", c);
		printf(" >> %d\n", c);
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