#include <stdio.h>
#include <lexical_error.h>
#include <c_error.h>

#define MAX 100

ERROR lexical_error_message(int error_num)
{
	ERROR err;
	switch(error_num)
	{
		case LEX_ERROR_IDENTIFICATION_CODE:
			CREATE_ERROR(err, LEX_ERROR_IDENTIFICATION_CODE, LEX_ERROR_IDENTIFICATION_MESSAGE);
			return err;
			break;
		case LEX_ERROR_BEGIN_CODE:
			CREATE_ERROR(err, LEX_ERROR_IDENTIFICATION_CODE, LEX_ERROR_BEGIN_MESSAGE);
			return err;
			break;
		case LEX_ERROR_END_CODE:
			CREATE_ERROR(err, LEX_ERROR_END_CODE, LEX_ERROR_END_MESSAGE);
			return err;
			break;
		default:
			CREATE_ERROR(err, LEX_ERROR_UNKOWN_CODE, LEX_UNKOWN_MESSAGE);
			break;
	}	
}

void throw_lexical_error(int err_id)
{
	ERROR err;
	err = lexical_error_message(err_id);
	printf("[ERROR] \n\t ERROR_ID: %d \n\t %s \n\t", err.ID, err.MSG);
}