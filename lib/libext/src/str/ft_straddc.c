/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_straddc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 02:21:08 by tbruinem       #+#    #+#                */
/*   Updated: 2020/02/20 22:07:44 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libext.h"

char	*ft_straddc(char *str, char c)
{
	char	*new;

	new = ft_calloc(sizeof(char), (ft_strlen(str) + 2));
	if (!new)
		return (NULL);
	ft_strcpy(new, str);
	ft_strcatc(new, c);
	free(str);
	return (new);
}
