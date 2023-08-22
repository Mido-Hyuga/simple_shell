#include "main.h"

/**
* check_env - checks if the typed variable is an env variable
* @h: head of linked list
* @in: input string
* @lists: lists structure
* Return: no return
*/
void check_env(r_var **h, char *in, lists_shell *lists)
{
	int a, row, c, lenval;
	char **_envr;

	_envr = lists->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (a = 1, c = 0; _envr[row][c]; c++)
		{
			if (_envr[row][c] == '=')
			{
				lenval = _strlen(_envr[row] + c + 1);
				add_rvar_node(h, a, _envr[row] + c + 1, lenval);
				return;
			}

			if (in[a] == _envr[row][c])
				a++;
			else
				break;
		}
	}

	for (a = 0; in[a]; a++)
		if (in[a] == ' ' || in[a] == '\t' || in[a] == ';' || in[a] == '\n')
			break;

	add_rvar_node(h, a, NULL, 0);
}

/**
* check_vars - check if the type of variable is $$ or $?
* @h: head of the linked list
* @in: input string
* @st: last status of the Shell
* @lists: lists structure
* Return: no return
*/
int check_vars(r_var **h, char *in, char *st, lists_shell *lists)
{
	int i, lenst, lpd;

	lenst = _strlen(st);
	lpd = _strlen(lists->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_rvar_node(h, 2, st, lenst), i++;
			else if (in[i + 1] == '$')
				add_rvar_node(h, 2, lists->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + i, lists);
		}
	}

	return (i);
}

/**
* replaced_input - replaces string into variables
* @head: head of the linked list
* @input: input string
* @new_input: new input string (replaced)
* @nlen: new length
* Return: new input
*/
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *index;
	int i, j, k;

	index = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (k = 0; k < index->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < index->len_val; k++)
				{
					new_input[i] = index->val[k];
					i++;
				}
				j += (index->len_var);
				i--;
			}
			index = index->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
* rep_var - calls functions to replace string into vars
* @input: input string
* @listssh: lists structure
* Return: new input
*/
char *rep_var(char *input, lists_shell *listssh)
{
	r_var *head, *index;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(listssh->status);
	head = NULL;

	olen = check_vars(&head, input, status, listssh);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	index = head;
	nlen = 0;

	while (index != NULL)
	{
		nlen += (index->len_val - index->len_var);
		index = index->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
