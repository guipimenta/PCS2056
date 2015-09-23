#ifndef AUTOMATA_H
#define AUTOMATA_H
	#define TMAX 1000
	#define SMAX 1000
	#define WMAX 1000
	typedef char WORD[WMAX];
	typedef int STATE;

	typedef struct {
		int trigger;
		STATE next;
	} TRANSITION;

	typedef struct {
		STATE id;
		TRANSITION transitions[TMAX];
	} AUTOMATA;

	typedef AUTOMATA TRANS_TABLE[SMAX];

	/*SPECIAL TRANSITION*/
	#define TEND {-1, ISERR}
	

	/*STATES*/
	/* INITIAL */
	#define IS0 0

	/*BEGIN TOKEN PARSER*/
	#define ISBB 1
	#define ISBE 2
	#define ISBG 3
	#define ISBI 4
	#define ISBN 5

	/*END TOKEN PARSER*/
	#define ISEN 11
	#define ISED 12

	/*#IDENTIFIER*/
	#define ISIS 13

	/*UNDEFINED STATE*/
	#define ISUE 200

	/*Error token*/
	#define ISERR -1
	#define ISF 999

#endif