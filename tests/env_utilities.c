/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utilities.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/30 16:22:27 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/06 17:06:09 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_envvar(t_list **env, char *varname)
{
	t_list *tmp;

	if (!env || !*env)
		return ;
	tmp = ft_lstnlookup(*env, varname);
	if (!tmp)
		return ;
	ft_lstdel(env, tmp, &free);
}

void	update_envvar(t_list *var, char *name, char *value)
{
	free(var->item);
	var->item = ft_strdup(name);
	var->item = ft_straddc(var->item, '=');
	var->item = ft_strsuffix(var->item, value);
	free(value);
}

/*
**	Find an existing envvar in the linked list (env)
**	or create the link if it doesnt exist
**
**	env: address of the head of the list
**	varname: name of the variable
**	value: heap allocated value to put in the var. || NULL
**
**	Only if value is != NULL:
**	- the value of the envvar will be made / updated
**	returns:
**	A pointer to the link.
*/

t_list	*set_envvar(t_list **env, char *varname, char *value)
{
	t_list	*tmp;

	if (!env)
		return (NULL);
	if (!*env && value)
	{
		ft_lstprefix(env, ft_lstnew(value));
		return (*env);
	}
	else if (!*env)
		return (NULL);
	tmp = ft_lstnlookup(*env, varname);
	if (!value)
		return (tmp);
	if (tmp)
		update_envvar(tmp, varname, value);
	else
	{
		ft_lstprefix(env, ft_lstnew(value));
		tmp = *env;
	}
	return (tmp);
}

char	*get_envvar_value(t_list **env, char *varname)
{
	t_list	*tmp;
	size_t	namelen;
	char	*value;

	value = NULL;
	if (!env || !*env)
		return (NULL);
	tmp = ft_lstnlookup(*env, varname);
	namelen = ft_strlen(varname);
	if (tmp)
		value = ((char *)tmp->item + namelen + 1);
	return (value);
}
