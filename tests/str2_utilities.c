/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str2_utilities.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/02 12:35:07 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/06 17:05:54 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//unused
long long	ft_str2ncmpstr(const char **str2, char *str)
{
	long long	i;
	size_t		cmplen;

	cmplen = ft_strlen(str);
	i = 0;
	while (str2[i])
	{
		if (ft_strncmp((char *)str2[i], str, cmplen) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/*
**	str2: a string array to search in
**	str: string to look for
**
**	returns:
**	the index of str2 that matches str || -1
*/

long long	ft_str2cmpstr(const char **str2, char *str)
{
	long long	i;

	i = 0;
	while (str2[i])
	{
		if (ft_strcmp((char *)str2[i], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}
