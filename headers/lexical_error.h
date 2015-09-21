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
#define LEX_ERROR_FEND_CODE				106
#define LEX_ERROR_ELSE_CODE				107
#define LEX_ERROR_LEND_CODE				108
#define LEX_ERROR_WHILE_CODE			109
#define LEX_ERROR_WEND_CODE				110
#define LEX_ERROR_READ_CODE				111
#define LEX_ERROR_WRITE_CODE			112
#define LEX_ERROR_COMMENT_CODE			113
#define LEX_ERROR_UNKOWN_CODE 			-100

/*ERROR MSG*/
#define LEX_ERROR_IDENTIFICATION_MESSAGE 	"Invalid char on Identificator!"
#define LEX_ERROR_BEGIN_MESSAGE 			"Invalid delimiter: expected begin"
#define LEX_ERROR_END_MESSAGE 				"Invalid delimiter: expected end"
#define LEX_ERROR_IF_MESSAGE                "Invalid command: expected if"
#define LEX_ERROR_NUMBER_MESSAGE			"Invalid number format!"
#define LEX_ERROR_DECLARE_MESSAGE			"Invalid declare: expected declare"
#define LEX_ERROR_FEND_MESSAGE				"Invalid command: expected fend"
#define LEX_ERROR_ELSE_MESSAGE				"Invalid command: expected else"
#define LEX_ERROR_LEND_MESSAGE				"Invalud command: expected lend"
#define LEX_ERROR_WHILE_MESSAGE				"Invalid command: expected while"
#define LEX_ERROR_WEND_MESSAGE				"Invalid command: expected wend"
#define LEX_ERROR_READ_MESSAGE				"Invalid system command: expected @read"
#define LEX_ERROR_WRITE_MESSAGE				"Invalid system command: expected write"
#define LEX_ERROR_COMMENT_MESSAGE			"Invalid comment: expected comment"
#define LEX_UNKOWN_MESSAGE 					"Unkown parsing error ocurred!"

/*Initializes an error*/
#define CREATE_ERROR(NERROR, ERR_ID, ERR_MSG) ({NERROR.ID = ERR_ID; strcpy(NERROR.MSG, ERR_MSG);})

void throw_lexical_error(int err);
ERROR lexical_error_message(int error_num);
#endif