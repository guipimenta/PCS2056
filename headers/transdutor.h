#ifndef TRANSDUTOR_H
#define TRANSDUTOR_H
	#define BREAKLINE '\n'
	typedef char WORD[200];
	typedef int STATE;
	
	
	typedef struct {
		int id;
		WORD tvalue;	
	} TOKEN;
	
	#define TBEGIN 	0	
	#define TEND 	1
	#define TID 	2
	#define TIF		3
	#define TIN 	4
	#define TDE 	5
	#define TFE 	6
	#define TEL 	7
	#define TLE 	8
	#define TWH 	9
	#define TWE 	10
	#define TWR		11
	#define TWW 	13
	#define TCC 	14
	#define TNU 	15
	
	/*ESTADOS AUTOMATO */
	
	/* INITIAL */
	#define S0 0
	
	#define CREATE_TOKEN(NTOKEN, ID) (NTOKEN.id = ID)
	
	TOKEN tokenizer(WORD word);
#endif