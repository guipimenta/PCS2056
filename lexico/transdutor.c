#include <stdio.h>
#include <string.h>
#include <transdutor.h>
#include <aux_char.h>
#include <lexical_error.h>


int main() 
{
	WORD to_token = "#<>!abc";
	TOKEN t = tokenizer(to_token);
	printf(">> %d\n", t.id);
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
					CREATE_TOKEN(tokenized, TOKENS_ID.TBEGIN);
					return tokenized;
				}
				break;
			case 'e':
				if(current == S0)
				{
					CREATE_TOKEN(tokenized, TOKENS_ID.TEND);
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
					
					if(isLetter(c) == TRUE)
					{
						throw_lexical_error(LEX_ERROR_IDENTIFICATION_CODE);
						return tokenized;
					}
				break;
		}
		i++;
		c = word[i];
	} 
}

