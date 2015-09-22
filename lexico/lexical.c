#include <stdio.h>
#include <lexical.h>
#include <transdutor.h>
#include <parser.h>
#include <bool.h>
#include <string.h>

// int main(int argv, char **argc)
// {
// 	char c;
// 	lexical_analysis(argc[1]);
// 	return 0;
// }

int lexical_analysis(char *file_name)
{
	FILE *fp;
	char c;
	WORD word;
	int i, u;
	fp = fopen (file_name, "rt");  /* open the file for reading */
	if(fp == NULL)
	{
		return LEXICAL_ERROR_READFILE;
	}
	i = 0;
	while(!feof(fp))
	{
		c = getc(fp);
		word[i] = c;
		i++;
		if(i == 1 && (c == '\n' || c == '\0' || c == '\t'))
		{
			memset(word,0,sizeof(word));
				i=0;
		}
		else if((c == '\n' || c == '\0'))
		{
				word[++i] = '\0';
				TOKEN t = tokenizer(word);
				printf("Parsed: %s\n\t Token Id:%d\n", word, t.id);
				memset(word,0,sizeof(word));
				i=0;
			
		}
	}


	return 0;
}

