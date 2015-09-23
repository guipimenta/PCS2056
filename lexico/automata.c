#include <stdio.h>
#include <automata.h>
#include <aux_char.h>

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
	[IS0]  = {IS0,  {{'b', ISBB}, {'e', ISUE}, 
					{'#', ISIS},TEND}},
	[ISBB] = {ISBB, {{'e', ISBE}, TEND}},
	[ISBE] = {ISBE, {{'g', ISBG}, TEND}},
	[ISBG] = {ISBG, {{'i', ISBI}, TEND}},
	[ISBI] = {ISBI, {{'n', ISBN}, TEND}},
	[ISBN] = {ISBN, {{'\n', ISF}, TEND}},

	[ISEN] = {ISEN, {{'d', ISED}, TEND}},
	[ISED] = {ISED, {{'\n', ISF}, TEND}},

	[ISUE] = {ISUE, {{'n', ISEN}, TEND}},

	[ISIS] = {ISIS, {{LL, ISIS}, {'\n', ISF}, TEND}},
	[ISF]  = {ISF, {{'\r', ISF}, {'\n', ISF}, {'\t', ISF}, {' ', ISF}, {32, ISF}, {10, ISF}, TEND}}
};