/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 23:04:09 by tbruinem       #+#    #+#                */
/*   Updated: 2020/03/31 00:42:02 by tbruinem      ########   odam.nl         */
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

char		*ft_strreplace(char *org, char *before, char *after);

typedef void (*t_builtin)(int argc, char **argv, t_list *env);
void		ft_cd(int argc, char **argv, t_list *env);
void		ft_pwd(int argc, char **argv, t_list *env);
void		ft_env(int argc, char **argv, t_list *env);

char		*get_envvar(char **env, char *varname);
char		*get_envvar_value(char **env, char *varname);
long long	is_builtin(char *program);

int			ft_escaper(char *str, char *last);
char		**parsing(char *input);
char		*get_abs_path(char *program);

#endif
