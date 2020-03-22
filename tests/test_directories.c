/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_directories.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/17 17:40:37 by tbruinem       #+#    #+#                */
/*   Updated: 2020/03/17 17:53:21 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int		main(void)
{
	DIR				*directory;
	struct dirent	*subdir;

	directory = opendir("/");
	if (!directory)
	{
		printf("Directory doesn't exist.");
		return (1);
	}
	while (subdir = readdir(directory))
		printf("%s\n", subdir->d_name);
	closedir(directory);
	return (0);
}
