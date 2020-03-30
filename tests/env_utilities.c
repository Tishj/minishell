/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utilities.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/30 16:22:27 by tbruinem       #+#    #+#                */
/*   Updated: 2020/03/30 16:34:46 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_envvar(char **env, char *varname)
{
	size_t	i;
	size_t	namelen;

	i = 0;
	namelen = ft_strlen(varname);
	while (env[i])
	{
		if (ft_strncmp(env[i], varname, namelen) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

/*
**	varname: an environment variable name
**
**	returns:
**	the value portion of the environment variable requested (STACK) || NULL
*/
char	*get_envvar_value(char **env, char *varname)
{
	size_t	i;
	size_t	namelen;
	char	*envvar;

	namelen = ft_strlen(varname);
	envvar = get_envvar(env, varname);
	if (envvar)
		return (env[i] + namelen + 1);
	return (NULL);
}
