/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strprefix.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 02:21:08 by tbruinem       #+#    #+#                */
/*   Updated: 2020/02/20 22:06:58 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libext.h"

char	*ft_strprefix(char *str, char *prefix)
{
	char	*new;

	new = ft_calloc(sizeof(char), (ft_strlen(str) + ft_strlen(prefix) + 1));
	if (!new)
		return (NULL);
	ft_strcpy(new, prefix);
	ft_strcat(new, str);
	free(str);
	return (new);
}
