#ifndef AUTOMATA_H
#define AUTOMATA_H
	#define TMAX 1000
	#define SMAX 1000
	#define WMAX 1000
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
	
	enum {
		S0,		//initial state
		SV1,	//variable state
		SI1,	//identifier state
		SN1,	//number state 1
		SN2,	//number state 2
		SSU,	//
		SC1,	//comment state
		SS1,	//string state 1
		SS2,	//string state 2
		SO1,	//operator state 1
		SO2		//operator state 2
	};

#endif