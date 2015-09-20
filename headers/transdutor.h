#ifndef TRANSDUTOR_H
#define TRANSDUTOR_H
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
		int TID;
		int TIF;
		int TIN;
		int TDE;
		int TFE;
		
	} TOKENS_ID = {
		.TBEGIN = 0,
		.TEND 	= 1,
		.TID 	= 2,
		.TIF	= 3,
		.TIN 	= 4,
		.TDE 	= 5,
		.TFE	= 6
	};
	
	/*ESTADOS AUTOMATO */
	
	/* INITIAL */
	#define S0 0
	
	#define CREATE_TOKEN(NTOKEN, ID) (NTOKEN.id = ID)
	
	TOKEN tokenizer(WORD word);
#endif