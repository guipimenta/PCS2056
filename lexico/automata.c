#include <stdio.h>
#include "../headers/automata.h"
#include "../headers/aux_char.h"

/*
* TRANSITIONS TABLE
*
* A table containg a simple structure:
* 	       identified by state id, contains transition struct
*		  that contains a id of the state and a list of possible
*         transitions.
*
* TRANSITION
*
* A tuple that contains a char that triggers the transition and
* the id of the next state.
*
* STATES
*
* They are integers that indexes the TRANSITION TABLE.
* Special States:
*	- ISF: Identifier State Final: after a VALID command, a '\n' will
*		   trigger a transition to the final state, so that we know
*			that the WORD parsed is VALID
*	- ISERR: if the char doesn't trigger any transition, the TEND
*			 transition will be triggered, and automata will go to
*			 a invalid state, called ISERR
*
* SPECIAL KEY CODES
*
* In case we need a special keycode (like, identifiers, that accept)
* any digit, we use aux_char library, that brings up LL and DD. This
* special codes, will allow our automata to track down digits and letters
* so that we can build-up identifiers and numbers
*/

TRANS_TABLE trans_table = {
/*	[<ROW NUMBER>] {<STATEID>, { {TRIGGER, NEXT_STATE}, ... }}*/
	[S0]   = {S0,  { {'#',  SV1}, {DD, SN1},   {LL, SI1}, {'/', SSU}, {'"', SS1}, {OP, SO1} }},
	[SV1]  = {SV1, { {DD,   SV1}, {LL, SV1},   {AN, S0}  		  							}},
	[SI1]  = {SI1, { {LL,   SI1}, {DD, SI1},   {AN, S0}  									}},
	[SN1]  = {SN1, { {DD,   SN1}, {'.', SN2},  {AN, S0}  									}},
	[SN2]  = {SN2, { {DD,   SN2}, {AN, S0}			   										}},
	[SSU]  = {SSU, { {'/',  SC1}, {AN, S0}													}},
	[SC1]  = {SC1, { {'\n', S0},  {AN, SC1}													}},
	[SS1]  = {SS1, { {'"',  S0},  {'\'', SS2}, {AN, S0}										}},
	[SS2]  = {SS2, { {AN,   SS1}															}},
	[SO1]  = {SO1, { {OP,   SO2}, {AN, S0}													}},
	[SO2]  = {S0,  { {AN, S0}																}}
};
