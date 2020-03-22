/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_execve.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/22 19:39:52 by tbruinem       #+#    #+#                */
/*   Updated: 2020/03/22 23:35:04 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_straddchar(char *str, char c)
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

long long	ft_str2cmpstr(char **str2, char *str)
{
	size_t	i;

	i = 0;
	while (str2[i])
	{
		if (ft_strcmp(str2[i], str) == 0)
			return ((long long)i);
		i++;
	}
	return (-1);
}

char	*get_envvar_value(char *varname)
{
	size_t	i;
	size_t	namelen;

	i = 0;
	namelen = ft_strlen(varname);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], varname, namelen) == 0)
			return (environ[i] + namelen + 1);
		i++;
	}
	return (NULL);
}

char	*get_file_path(char *program, char *path)
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
//		printf("program: %s\n", filepath);
		result = stat(filepath, &file);
		if (result != -1)
			return (filepath);
		token = ft_strctok(NULL, ':');
		free(filepath);
		filepath = NULL;
	}
	return (filepath);
}

char	*get_abs_path(char *program)
{
	char	*path;

	path = get_envvar_value("PATH");
	if (!path)
		return (NULL); //error
	path = ft_strdup(path);
	program = get_file_path(program, path);
	if (!program)
		printf("Could not find any executable by that name\n");
	free(path);
	return (program);
}

void	fork_and_exec(char **args)
{
//	ft_str2print(args);
	if (fork() == 0)
	{
		printf("Trying to run a program\n");
		execve(args[0], args, environ);
	}
}

void	run_program(char **args)
{
	size_t		builtin;
	static char	*builtins[] = {
	[CD] = "cd",
	[ECHO] = "echo",
	[PWD] = "pwd",
	[EXPORT] = "export",
	[UNSET] = "unset",
	[ENV] = "env",
	[EXIT] = "exit",
	};

	if (!args)
		return ; //error
//	builtin = ft_str2cmpstr(builtins, args[0]);
//	if (!builtin)
	fork_and_exec(args);
	return ;
}

int		main(void)
{
	char	*input;
	char	**args;

	input = NULL;
//	ft_str2print(environ);
	while (1)
	{
		ft_fdstrc(1, &input, '\n');
		args = parsing(input);
		run_program(args);
		free(input);
		input = NULL;
	}
	free(input);
	return (1);
}
