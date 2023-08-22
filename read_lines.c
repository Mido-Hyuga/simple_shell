#include "main.h"

/**
* read_line - reads the input string.
* @i_eof: return value of getline function
* Return: input string
*/
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t buffsize = 0;

	*i_eof = getline(&input, &buffsize, stdin);

	return (input);
}
