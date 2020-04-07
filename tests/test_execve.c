/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_execve.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/22 19:39:52 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/06 17:05:24 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_straddchar(char *str, char c)
{
	char	*new;
	size_t	len;

	len = ft_strlen(str);
	new = ft_calloc(sizeof(char), (len + 2));
	if (!new)
		return (NULL);
	ft_strcpy(new, str);
	new[len] = c;
	new[len + 1] = 0;
	free(str);
	return (new);
}

/*
**	program: a token of wordsplit (treated as STACK)
**	path: the entire value portion of the envvar PATH
**
**	returns:
**	if BUILTIN ->	NULL
**	else ->			abs_path/program
**
**	BUILTIN - given 'program' is not an executable
*/
char		*get_file_path(char *program, char *path)
{
	char		*filepath;
	char		*token;
	int			result;
	struct stat	file;

	filepath = 0;
	token = ft_strctok(path, ':');
	while (token)
	{
		filepath = ft_strdup(token);
		filepath = ft_straddchar(filepath, '/');
		filepath = ft_strsuffix(filepath, program);
		result = stat(filepath, &file);
		if (result != -1)
			break ;
		token = ft_strctok(NULL, ':');
		free(filepath);
		filepath = NULL;
	}
	free(path);
	return (filepath);
}

/*
**	program: a token of wordsplit (treated as STACK)
**
**	returns:
**	if BUILTIN ->		strdup of program. (HEAP)
**	if EXECUTABLE ->	abs_path/program. (HEAP)
**	else ->				NULL
**
**	BUILTIN -			the given 'program' is not an executable
**	EXECUTABLE -		the given 'program' could be found in one of the directories in PATH
*/
char		*get_abs_path(t_list *env, char *program)
{
	char		*path;
	long long	builtin;

	builtin = is_builtin(program);
	if (builtin != -1)
		return (ft_strdup(program));
	path = (char *)set_envvar(&env, "PATH", NULL)->item;
	if (!path)
		return (NULL);
	path = ft_strdup(path);
	program = get_file_path(program, path);
	if (!program)
	{
		printf("No executable nor builtin by that name could be found.\n");
		return (NULL);
	}
	return (program);
}

void		fork_and_exec(char **args, t_list *env)
{
	char	**envp;

	envp = ft_lstconvstr2(env);
	if (fork() == 0)
	{
		printf("Trying to run a program\n");
		execve(args[0], args, envp);
	}
	ft_str2del(envp);
}

void		exec_builtin(char **args, int id, t_list *env)
{
	static const t_builtin builtins[] = {
	[ENV] = &ft_env,
	[PWD] = &ft_pwd,
	[ECHO] = &ft_echo,
	[EXPORT] = &ft_export,
	[UNSET] = &ft_unset,
	[EXIT] = &ft_exit,
	[CD] = &ft_cd};

//	printf("Executing builtin!\n");
	builtins[id](ft_str2len(args), args, env);
}

long long	is_builtin(char *program)
{
	static const char	*builtins[] = {
	[CD] = "cd",
	[ECHO] = "echo",
	[PWD] = "pwd",
	[EXPORT] = "export",
	[UNSET] = "unset",
	[ENV] = "env",
	[EXIT] = "exit",
	[7] = NULL,
	};

	return(ft_str2cmpstr(builtins, program));
}

void		run_program(char **args, t_list *env)
{
	long long	builtin;

	if (!args)
		return ;
	builtin = is_builtin(args[0]);
	if (builtin == -1)
		fork_and_exec(args, env);
	else
		exec_builtin(args, builtin, env);
	return ;
}

/*
**	Get the input with fdstrc
**	get a 2d string from it containing:
**	[0] = A program with it's absolute path prefixed to it.
**	[..] = all the program's arguments
*/

int			main(void)
{
	char	*input;
	char	**args;
	char	**tokens;
	t_list	*env;

	env = ft_str2convlst(environ);
	input = NULL;
	args = NULL;
	while (1)
	{
		ft_fdstrc(1, &input, '\n');
		input = specialchar_sep(input, ";|");
		tokens = parsing(env, input);
		args = ft_str2tokc(tokens, ';');
		while (args)
		{
			run_program(args, env);
			args = ft_str2tokc(NULL, ';');
		}
		free(input);
		input = NULL;
	}
	free(input);
	return (1);
}
