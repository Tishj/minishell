/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 21:33:43 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/06 17:05:51 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(int argc, char **argv, t_list *env)
{
	size_t	i;
	size_t	tmp;

	if (argc == 1)
		return ;
	i = 1;
	while (argv[i])
	{
		tmp = ft_strclen(argv[i], '=');
		if (tmp != ft_strlen(argv[i]))
			ft_lstsuffix(&env, ft_lstnew(ft_strdup(argv[i])));
		i++;
	}
}

void	ft_exit(int argc, char **argv, t_list *env)
{
	exit(0);
}

void	ft_unset(int argc, char **argv, t_list *env)
{
	t_list	*envvar;
	size_t	i;

	if (argc == 1)
		return ;
	i = 1;
	while (argv[i])
	{
		envvar = set_envvar(&env, argv[i], NULL);
		if (envvar)
			ft_lstdel(&env, envvar, &free);
		i++;
	}
}

void	ft_echo(int argc, char **argv, t_list *env)
{
	size_t	i;

	i = 1;
	while (argc >= 2 && argv[i])
	{
		if (i != 1 || ft_strncmp(argv[1], "-n", 2) != 0)
		{
			write(1, argv[i], ft_strlen(argv[i]));
			if (i + 1 < argc)
				write(1, " ", 1);
		}
		i++;
	}
	if (argc == 1 || ft_strncmp(argv[1], "-n", 2) != 0)
		write(1, "\n", 1);
}

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
		path = ft_strdup(get_envvar_value(&env, "OLDPWD"));
	else if (argc == 3)
	{
		path = ft_strdup(get_envvar_value(&env, "PWD"));
		path = ft_strreplace(path, argv[1], argv[2]);
	}
	else
		path = ft_strdup(argv[1]);
	if (chdir(path) == -1)
	{
		free(path);
		return (perror(strerror(errno)));
	}
	set_envvar(&env, "OLDPWD", ft_strdup(get_envvar_value(&env, "PWD")));
	set_envvar(&env, "PWD", get_cwd());
	free(path);
}
