/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_fdstrc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/22 22:47:39 by tbruinem       #+#    #+#                */
/*   Updated: 2020/02/27 11:42:14 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libext.h"

int				ft_fdstrc(int fd, char **line, char c)
{
	char	*str;
	int		ret;
	size_t	i;

	i = 0;
	if (!line || read(fd, (void *)0, 0) == -1)
		return (-1);
	str = NULL;
	while (str == NULL || (ret > 0 && str[i - 1] != c))
	{
		if (i % BUFFER_SIZE == 0)
		{
			str = ft_straddn(str, BUFFER_SIZE + 1);
			if (!str)
				return (-1);
		}
		ret = ft_fdchar(fd, &str[i]);
		i++;
	}
	str[i - 1] = '\0';
	*line = (ret > -1) ? ft_memdup(str, i + 1) : NULL;
	free(str);
	return ((ret > 0) ? 1 : ret);
}
