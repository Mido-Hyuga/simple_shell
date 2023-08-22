#include "main.h"

/**
* copy_info - copies info to create
* a new env or alias
* @name: name (env or alias)
* @value: value (env or alias)
* Return: new env or alias.
*/
char *copy_info(char *name, char *value)
{
	char *new;
	int name_len, val_len, len;

	name_len = _strlen(name);
	val_len = _strlen(value);
	len = name_len + val_len + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
* set_env - sets an environment variable
* @name: name of the environment variable
* @value: value of the environment variable
* @listssh: lists structure (environ)
* Return: no return
*/
void set_env(char *name, char *value, lists_shell *listssh)
{
	int i, j;
	char *var_env, *name_env;

	for (i = 0; listssh->_environ[i]; i++)
	{
		var_env = _strdup(listssh->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(listssh->_environ[i]);
			listssh->_environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}
	j = sizeof(char *) * (i + 2);
	listssh->_environ = _reallocdp(listssh->_environ, i, j);
	listssh->_environ[i] = copy_info(name, value);
	listssh->_environ[i + 1] = NULL;
}

/**
* _setenv - compares env variables
* names with the name passed.
* @listssh: lists relevant (env name and env value)
* Return: 1 on success.
*/
int _setenv(lists_shell *listssh)
{

	if (listssh->args[1] == NULL || listssh->args[2] == NULL)
	{
		get_error(listssh, -1);
		return (1);
	}

	set_env(listssh->args[1], listssh->args[2], listssh);

	return (1);
}

/**
* _unsetenv - deletes a environment variable
* @listssh: lists relevant (env name)
* Return: 1 on success.
*/
int _unsetenv(lists_shell *listssh)
{
	char **rlloc_envr;
	char *var_env, *name_env;
	int i, j, k;

	if (listssh->args[1] == NULL)
	{
		get_error(listssh, -1);
		return (1);
	}
	k = -1;
	for (i = 0; listssh->_environ[i]; i++)
	{
		var_env = _strdup(listssh->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, listssh->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(listssh, -1);
		return (1);
	}
	rlloc_envr = malloc(sizeof(char *) * (i));
	for (i = j = 0; listssh->_environ[i]; i++)
	{
		if (i != k)
		{
			rlloc_envr[j] = listssh->_environ[i];
			j++;
		}
	}
	rlloc_envr[j] = NULL;
	free(listssh->_environ[k]);
	free(listssh->_environ);
	listssh->_environ = rlloc_envr;
	return (1);
}
