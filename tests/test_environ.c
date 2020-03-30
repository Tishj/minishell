/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_environ.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/17 19:39:04 by tbruinem       #+#    #+#                */
/*   Updated: 2020/03/30 17:07:55 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ptr(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		printf("env[%ld] = %p\n", i, &env[i]);
		i++;
	}
}

int		main(void)
{
	char	**env;
	char	*pwd;

	env = ft_str2dup(environ);
	print_ptr(env);
//	ft_str2print(env);
	printf("BEFORE---------------------------------------------------------------------------------------------------------------------------------------------<\n\n\n");
	printf("\n\n\n");
	pwd = get_envvar(env, "LS_COLORS");
	printf("length: %ld\n", ft_strlen(pwd));
	return (0);
	printf("Retrieved PWD: ptr: %p | var: %s\n\n\n", pwd, pwd);
	free(pwd);
//	return (0);
	pwd = ft_strprefix(ft_strdup("testerino_test_test"), "PWD=");
	printf("%p | %s\n", pwd, pwd);
//	print_ptr(env);
	printf("AFTER----------------------------------------------------------------------------------------------------------------------------------------------<\n\n\n");
//	ft_str2print(env);
	return (0);
}
