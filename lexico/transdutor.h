#ifndef transdutor
	#define BREAKLINE '\n'
	typedef char WORD[200];
	typedef int STATE;
	
	
	typedef struct {
		int id;
		WORD tvalue;	
	} TOKEN;
	
	struct {
		int TBEGIN;
		int TEND;
		
	} TOKENS_ID = {
		.TBEGIN = 0,
		.TEND 	= 1
	};
	
	/*ESTADOS AUTOMATO */
	
	/* INITIAL */
	#define S0 0
	
	/* BEGIN */
	#define SB0 1
	
	#define CREATE_TOKEN(NTOKEN, ID) (NTOKEN.id = ID)
	
	TOKEN tokenizer(WORD word);
#endif