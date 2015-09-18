#ifndef LEXICAL_ERROR_H
#define LEXICAL_ERROR_H
#include <c_error.h>
#include <stdio.h>
#include <string.h>


/*ERROR CODE*/
#define LEX_ERROR_IDENTIFICATION_CODE 100
#define LEX_ERROR_UNKOWN_CODE -100

/*ERROR MSG*/
#define LEX_ERROR_IDENTIFICATION_MESSAGE "Invalid char on Identificator!"
#define LEX_UNKOWN_MESSAGE "Unkown parsing error ocurred!"

/*Initializes an error*/
#define CREATE_ERROR(NERROR, ERR_ID, ERR_MSG) ({NERROR.ID = ERR_ID; strcpy(NERROR.MSG, LEX_ERROR_IDENTIFICATION_MESSAGE);})

void throw_lexical_error(int err);
ERROR lexical_error_message(int error_num);
#endif