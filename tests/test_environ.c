/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_environ.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/17 19:39:04 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/06 17:05:39 by tbruinem      ########   odam.nl         */
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
	t_list	*env;
	t_list	*envvar;

	env = ft_str2convlst(environ);
	unset_envvar(&env, "PWD");
	ft_lstprint(env, &ft_strprint);
	return (0);
}
