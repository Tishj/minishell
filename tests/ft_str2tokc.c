/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str2tokc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/02 15:06:34 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/06 17:06:05 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_str2tokc(char **input, char c)
{
	static char	**buff;
	char		**ret;
	size_t		i;

	i = 0;
	if (input || !buff)
		buff = input;
	if (buff == NULL)
		return (NULL);
	while (buff && buff[i] && (*buff[i] != c || !*buff[i]))
		i++;
	ret = buff;
	if (buff && buff[i] && *buff[i] == c)
	{
		free(buff[i]);
		buff[i] = NULL;
		buff = &buff[i + 1];
	}
	else
		buff = NULL;
	return (ret);
}
