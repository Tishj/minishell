/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strndup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 01:54:34 by tbruinem       #+#    #+#                */
/*   Updated: 2020/03/30 12:23:13 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libext.h"

char	*ft_strndup(char *str, size_t n)
{
	size_t	len;
	size_t	i;
	char	*new;

	i = 0;
	if (!str)
		return (NULL);
	len = ft_strnlen(str, n);
	new = ft_calloc(sizeof(char), (len + 1));
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = 0;
	return (new);
}
