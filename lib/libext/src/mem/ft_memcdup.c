/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcdup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/24 16:51:30 by tbruinem       #+#    #+#                */
/*   Updated: 2020/02/27 10:45:50 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libext.h"

HEAP	*ft_memcdup(void *mem, size_t n, char c)
{
	size_t	i;
	HEAP	*new;
	char	*bytes;

	i = 0;
	if (!mem)
		return (NULL);
	n = ft_memclen(mem, n, c);
	bytes = (char *)mem;
	new = ft_calloc(sizeof(char), n);
	if (!new)
		return (NULL);
	while (i < n && bytes[i] != c)
	{
		*((char *)new + i) = bytes[i];
		i++;
	}
	return (new);
}
