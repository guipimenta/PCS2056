#ifndef AUTOMATA_H
#define AUTOMATA_H
	#include "bool.h"

	#define TMAX 1000
	#define SMAX 1000
	#define WMAX 1000

	typedef enum states {
		S0,				//initial state
		SVAR,			//variable state
		SIDENT,		//identifier state
		SINT,			//integer state 1
		SFLOAT1,	//float state 1
		SFLOAT2,	//float state 2
		SCOMM1,		// comment state 1
		SCOMM2,		//comment state 2
		SSTR1,		//string state 1
		SSTR2,		//string state 2
		SSYMB1,		//symbol state 1
		SSYMB2		//symbol state 2
	} STATE;

	typedef struct {
		int trigger;
		STATE next;
		BOOL (*action)(STATE, STATE, char, char);
	} TRANSITION;

	typedef struct {
		STATE id;
		TRANSITION transitions[TMAX];
	} AUTOMATA;

	typedef AUTOMATA TRANS_TABLE[SMAX];

#endif
