#include "main.h"

/**
* cd_dot - changes to the parent directory
* @listssh: lists relevant (environ)
* Return: no return
*/
void cd_dot(lists_shell *listssh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, listssh);
	dir = listssh->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, listssh);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, listssh);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", listssh);
	}
	listssh->status = 0;
	free(cp_pwd);
}

/**
* cd_to - changes to a directory given
* by the user
* @listssh: lists relevant (directories)
* Return: no return
*/
void cd_to(lists_shell *listssh)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = listssh->args[1];
	if (chdir(dir) == -1)
	{
		get_error(listssh, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, listssh);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, listssh);

	free(cp_pwd);
	free(cp_dir);

	listssh->status = 0;

	chdir(dir);
}

/**
* cd_previous - changes to the previous directory
* @listssh: lists relevant (environ)
* Return: no return
*/
void cd_previous(lists_shell *listssh)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", listssh->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, listssh);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, listssh);
	else
		set_env("PWD", cp_oldpwd, listssh);

	p_pwd = _getenv("PWD", listssh->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	listssh->status = 0;

	chdir(p_pwd);
}

/**
* cd_to_home - changes to home directory
*
* @listssh: lists relevant (environ)
* Return: no return
*/
void cd_to_home(lists_shell *listssh)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", listssh->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, listssh);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(listssh, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, listssh);
	set_env("PWD", home, listssh);
	free(p_pwd);
	listssh->status = 0;
}
