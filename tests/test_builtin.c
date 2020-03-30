/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/28 11:09:49 by tbruinem       #+#    #+#                */
/*   Updated: 2020/03/31 00:44:21 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(int argc, char **argv, t_list *env)
{
	if (argc != 1 || !argv)
		return ;
	ft_lstprint(env, ft_strprint);
}

void	ft_pwd(int argc, char **argv, t_list *env)
{
	char	*path;
	char	*res;
	size_t	size;

	size = 20;
	path = malloc(sizeof(char) * (size + 1));
	res = getcwd(path, size + 1);
	while (!res && errno == ERANGE)
	{
		size += 20;
		free(path);
		path = malloc(sizeof(char) * (size + 1));
		if (!path)
			return ;
		res = getcwd(path, size + 1);
	}
	if (res)
		ft_strprint(path);
	free(path);
}

void	ft_cd(int argc, char **argv, t_list *env)
{
	char	*path;
	char	*pwd;
	char	*oldpwd;

	if (argc <= 1 || argc > 3)
		return ;
	if (argc == 2 && ft_strcmp(argv[1], "-") == 0)
		path = ft_strdup(get_envvar_value(environ, "OLDPWD"));
	else if (argc == 3)
	{
		path = ft_strdup(get_envvar_value(environ, "PWD"));
		path = ft_strreplace(path, argv[1], argv[2]);
		ft_strprint(path);
		printf("Running CD with special property:\nFirst argument as needle.\nSecond argument as string to replace the needle\n");
	}
	else
		path = ft_strdup(argv[1]);
	if (chdir(path) == -1)
		return (perror(strerror(errno)));
	//TODO: update PWD and OLDPWD
}
