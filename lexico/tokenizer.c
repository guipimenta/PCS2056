#include <stdio.h>
#include "../headers/tokenizer.h"
#include "../headers/bool.h"
#include "../headers/aux_char.h"
#include "../headers/automata.h"
#include <string.h>

extern TRANS_TABLE trans_table;


/*
* NEXT_STATE
*	PARAMS:
*		current: current state ID
*		c:		 char to search for transactions on TRANS_TABLE
*
* Will search on the TRANS_TABLE for the current state transitions
* 
* Triggering transitions means that we the current state has a VALID
* transition rule for the given char c. 
* If a vaid transition is triggeres, next_state will return the NEXT
* State ID
* 
* The macro DIGIT takes a char c and returns either is a DD or a LL
* (all defined in aux_char) so that special rules, like:
* 	#[a-zA-Z]+
* can be created without adding many transactions on TRANS_TABLE
*/

STATE next_state(STATE current, char c) 
{
	int i = 0;
	while(trans_table[current].transitions[i].trigger != AN)
	{
		if(trans_table[current].transitions[i].trigger == c ||
			trans_table[current].transitions[i].trigger == LETTER(c) )
		{
			return trans_table[current].transitions[i].next;
		}
		i++;
	}
	return S0;
}


/*
* PARAMETERS: a single WORD for lexical analysis
* RETURNS:	  a TOKEN of the parsed WORD or error token ISERR
* 
* TOKENIZE
* 
* Reads work char by char, and keep track of the current and next state
* when next_state returns  ISERR, an invalid WORD was found.
* When next is ISF, a final state was reached, so no more parsing, returns
* the valid token.
*/
TOKEN tokenize(WORD word)
{
	char c;
	int i = 0;
	STATE current = S0;
	STATE next;
	c = word[i]; 
	while(TRUE)
	{
		next = next_state(current, c);
		if (next == S0)
		{
			return create_token(current, word);
		}
		current = next;
		i++;
		c = word[i];
	}
	return create_token(current, word);
}

TOKEN create_token(int id, WORD tvalue)
{
	TOKEN t;
	t.id = id;
	strcpy(t.tvalue, tvalue);
	return t;
}

/* FOR TESTING ONLY*/
int main()
{
	WORD to_token;
	TOKEN t;
	while(1) {
		printf(">> ");
		fgets(to_token, sizeof(to_token), stdin);
		t = tokenize(to_token);
		printf("Token: %d\nWord: %s\n", t.id, t.tvalue);
	}
	return 0;
}