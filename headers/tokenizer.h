#ifndef TOKENIZER_H
#define TOKENIZER_H

#define WMAX	1000

typedef char 	WORD[WMAX];

/*
* Tokens contains a single identification number
* and it's value, string representation for a token
*	TOKEN ID  |   TOKEN VALUE
*	------------------------------------------------------
*     ISBN 	  |    begin
*	  ISED	  |	   end 
*	  ISIS	  |	   #<identifier> (any sequence of letters)
*	  ISERR   |	   <error state> (not part of language)
*/
typedef struct {
		int id;
		WORD tvalue;	
} TOKEN;

TOKEN create_token(int id, WORD tvalue);


#endif