/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_chdir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/18 14:06:07 by tbruinem       #+#    #+#                */
/*   Updated: 2020/03/18 14:52:30 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int		print_cwd(void)
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
			return (-1);
		res = getcwd(path, size + 1);
	}
	if (!res)
	{
		free(path);
		return (-1);
	}
	ft_strprint(path);
}

int		main(void)
{
	print_cwd();
	chdir("..");
	print_cwd();
	chdir("tests");
	print_cwd();
	chdir("/mnt/c/Users/Thijs/desktop/codam/");
	print_cwd();
	return (0);
}
