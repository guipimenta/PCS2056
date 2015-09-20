#ifndef LEXICAL_ERROR_H
#define LEXICAL_ERROR_H
#include <c_error.h>
#include <stdio.h>
#include <string.h>


/*ERROR CODE*/
#define LEX_ERROR_IDENTIFICATION_CODE 	100
#define LEX_ERROR_BEGIN_CODE 			101
#define LEX_ERROR_END_CODE 				102
#define LEX_ERROR_IF_CODE 				103
#define LEX_ERROR_NUMBER_CODE 			104
#define LEX_ERROR_DECLARE_CODE 			105
#define LEX_ERROR_UNKOWN_CODE 			-100

/*ERROR MSG*/
#define LEX_ERROR_IDENTIFICATION_MESSAGE 	"Invalid char on Identificator!"
#define LEX_ERROR_BEGIN_MESSAGE 			"Invalid delimiter: expected begin"
#define LEX_ERROR_END_MESSAGE 				"Invalid delimiter: expected end"
#define LEX_ERROR_IF_MESSAGE                "Invalid command: expected if"
#define LEX_ERROR_NUMBER_MESSAGE			"Invalid number format!"
#define LEX_ERROR_DECLARE_MESSAGE			"Invalide declare: expected declare"
#define LEX_UNKOWN_MESSAGE 					"Unkown parsing error ocurred!"

/*Initializes an error*/
#define CREATE_ERROR(NERROR, ERR_ID, ERR_MSG) ({NERROR.ID = ERR_ID; strcpy(NERROR.MSG, ERR_MSG);})

void throw_lexical_error(int err);
ERROR lexical_error_message(int error_num);
#endif