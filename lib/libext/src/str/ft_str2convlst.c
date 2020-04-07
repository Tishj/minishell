/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str2convlst.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/30 17:22:13 by tbruinem       #+#    #+#                */
/*   Updated: 2020/04/02 13:31:45 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libext.h"

t_list	*ft_str2convlst(char **str2)
{
	t_list	*list;
	int		len;

	if (!str2)
		return (NULL);
	len = ft_str2len(str2) - 1;
	list = NULL;
	while (len >= 0)
	{
		ft_lstprefix(&list, ft_lstnew(ft_strdup(str2[len])));
		len--;
	}
	return (list);
}
