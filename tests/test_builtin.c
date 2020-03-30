/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/28 11:09:49 by tbruinem       #+#    #+#                */
/*   Updated: 2020/03/30 15:05:00 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(int argc, char **argv, char **env)
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

void	ft_cd(int argc, char **argv, char **env)
{
	char	*path;

	printf("arg count: %d\n", argc);
	ft_str2print(argv);
	if (argc <= 1 || argc > 3)
		return ;
	path = argv[1];
	if (argc == 3)
	{
		//replace part of path;
		printf("Running CD with special property:\nFirst argument as needle.\nSecond argument as string to replace the needle\n");
	}
	if (chdir(path) == -1)
	perror(strerror(errno));
}
