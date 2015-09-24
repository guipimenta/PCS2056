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
		S0,
		SV1,
		SI1,
		SN1,
		SN2,
		SSU,
		SC1,
		SS1,
		SS2,
		SO1,
		SO2
	};

#endif