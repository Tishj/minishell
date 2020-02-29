/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtokp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/23 17:06:59 by tbruinem       #+#    #+#                */
/*   Updated: 2020/02/23 19:06:19 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libext.h"
#include "string.h"

char	*ft_strtokp(char *str, char *delimiter, char *buffer)
{
	char		*ret;
	size_t		i;

	i = 0;
	ret = NULL;
	if (str != NULL)
		buffer = str;
	if (buffer[i] == 0)
		return (NULL);
	while (buffer && buffer[i] && !ft_chrmatchs(buffer[i], delimiter))
		i++;
	if (buffer && ft_chrmatchs(buffer[i], delimiter))
	{
		buffer[i] = '\0';
		ret = buffer;
		buffer += i + 1;
	}
	else if (buffer && buffer[i] == '\0')
	{
		ret = buffer;
		buffer += i;
	}
	return (ret);
}
