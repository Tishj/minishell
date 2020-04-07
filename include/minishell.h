/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 23:04:09 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/03 14:36:56 by tbruinem      ########   odam.nl         */
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

void		printmem(char *str);
char		*specialchar_sep(char *string, char *specialchars);
long long	ft_str2cmpstr(const char **str2, char *str);
long long	ft_str2ncmpstr(const char **str2, char *str);
char		**ft_str2tokc(char **input, char c);
char		*ft_strreplace(char *org, char *before, char *after);
char		*ft_strreplacec(char *org, char c, char *replace);
char		*get_cwd(void);

typedef void (*t_builtin)(int argc, char **argv, t_list *env);
void		ft_cd(int argc, char **argv, t_list *env);
void		ft_pwd(int argc, char **argv, t_list *env);
void		ft_env(int argc, char **argv, t_list *env);
void		ft_echo(int argc, char **argv, t_list *env);
void		ft_export(int argc, char **argv, t_list *env);
void		ft_unset(int argc, char **argv, t_list *env);
void		ft_exit(int argc, char **argv, t_list *env);

t_list		*set_envvar(t_list **env, char *varname, char *value);
void		unset_envvar(t_list **env, char *varname);
char		*get_envvar_value(t_list **env, char *varname);

long long	is_builtin(char *program);

int			ft_escaper(char *str, char *last);
char		**parsing(t_list *env, char *input);
char		*get_abs_path(t_list *env, char *program);

#endif
