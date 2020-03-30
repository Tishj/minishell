/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnlookup.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/30 20:11:50 by tbruinem       #+#    #+#                */
/*   Updated: 2020/03/31 00:01:08 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libext.h"

t_list	*ft_lstnlookup(t_list *root, char *str)
{
	size_t	len;

	len = ft_strlen(str);
	while (root)
	{
		if (ft_strncmp((char *)root->item, str, len) == 0)
			return (root);
		root = root->next;
	}
	return (root);
}
