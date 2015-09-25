#ifndef AUTOMATA_H
#define AUTOMATA_H
	#include "bool.h"

	#define TMAX 1000
	#define SMAX 1000
	#define WMAX 1000

	typedef enum states {
		S0,		//initial state
		SVAR,	//variable state
		SIDENT,	//identifier state
		SINT,	//number state 1
		SFLOAT1,	//number state 2
		SFLOAT2,
		SSU,	//
		SCOM,	//comment state
		SSTR1,	//string state 1
		SSTR2,	//string state 2
		SO1,	//operator state 1
		SO2		//operator state 2
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
