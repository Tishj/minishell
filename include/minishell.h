/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 23:04:09 by tbruinem       #+#    #+#                */
/*   Updated: 2020/03/30 14:29:15 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libext.h"

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>

extern char	**environ;
extern int	errno;

enum	e_builtin
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
};

typedef void (*t_builtin)(int argc, char **argv, char **env);
void		ft_cd(int argc, char **argv, char **env);
void		ft_pwd(int argc, char **argv, char **env);

int			ft_escaper(char *str, char *last);
char		**parsing(char *input);
char		*get_abs_path(char *program);
long long	is_builtin(char *program);

#endif
