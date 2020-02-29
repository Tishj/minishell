/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnadd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 02:21:08 by tbruinem       #+#    #+#                */
/*   Updated: 2020/02/20 22:07:03 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libext.h"

char	*ft_strnadd(char *str, char *add, size_t n)
{
	char	*new;

	new = ft_calloc(sizeof(char), (ft_strlen(str) + ft_strnlen(add, n) + 1));
	if (!new)
		return (NULL);
	ft_strcpy(new, str);
	ft_strncat(new, add, n);
	free(str);
	return (new);
}
