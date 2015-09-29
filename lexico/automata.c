#include <stdio.h>
#include "../headers/automata.h"
#include "../headers/tokenizer.h"
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
	[S0]   			= {S0,  			{ {'#', SVAR, variable_first_char}, {DD, SINT, number_first_char},   {LL, SIDENT, identifier_first_char}, {'/', SCOMM1}, {'"', SSTR1, string_beginning}, {SB, SSYMB1, symbol_first_char}, {WS, S0}, {AN, SERROR, symbol_error} }},
	[SVAR]  		= {SVAR, 			{ {DD, SVAR, variable_loop}, {LL, SVAR, variable_loop},   {AN, S0, variable_end}  		  							}},
	[SIDENT]  	= {SIDENT, 		{ {LL, SIDENT, identifier_loop}, {DD, SIDENT, identifier_loop}, {AN, S0, identifier_end} 									}},
	[SINT]  		= {SINT, 			{ {DD, SINT, number_loop}, {'.', SFLOAT1, float_number},  {AN, S0, integer_end}  									}},
	[SFLOAT1]  	= {SFLOAT1,		{ {DD, SFLOAT2, float_first_char}, {AN, SERROR}			   										}},
	[SFLOAT2]  	= {SFLOAT2, 	{ {DD, SFLOAT2, float_loop}, {AN, S0, float_end}			   										}},
	[SCOMM1]  	=	{SCOMM1, 		{ {'/', SCOMM2}, {AN, S0}													}},
	[SCOMM2]  	=	{SCOMM2, 		{ {'\n', S0},  {AN, SCOMM2}													}},
	[SSTR1]  		=	{SSTR1, 		{ {'"', SSTR3},  {'\\', SSTR2}, {AN, SSTR1, string_loop}										}},
	[SSTR2]  		=	{SSTR2, 		{ {AN, SSTR1, string_escaped_char}															}},
	[SSTR3]			= {SSTR3,			{ {AN, S0, string_end}											}},
	[SSYMB1]  	=	{SSYMB1, 		{ {SB, SSYMB2, double_symbol}, {LL, S0, single_symbol_end}, {DD, S0, single_symbol_end}, {WS, S0, single_symbol_end}, {AN, S0, symbol_error}													}},
	[SSYMB2] 		=	{S0,  			{ {AN, S0, double_symbol_end}																}},
	[SERROR]	=	{SERROR, {{AN, S0}}}
};
