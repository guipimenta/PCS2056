#include<stdio.h>
#include <string.h>
#include"transdutor.h"

int main() 
{
	WORD to_token = "begin";
	TOKEN t = tokenizer(to_token);
	printf(">> %d\n", t.id);
}

TOKEN tokenizer(WORD word)
{
	int  i 	= 0;
	char c 	= word[i];
	STATE current = S0;
	TOKEN tokenized;
	while(c != BREAKLINE)
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
			default:
				break;
		}
		i++;
		c = word[i];
	} 
}

