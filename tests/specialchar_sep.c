/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specialchar_sep.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 10:29:34 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/06 17:05:57 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_unescapedchr(char *str, char c)
{
	size_t	i;
	char	last;
	size_t	len;

	len = 0;
	last = 0;
	i = 0;
	while (str[i])
	{
		if (last != '\\' && str[i] == c)
			len++;	
		last = str[i];
		i++;
	}
	return (len);
}

char	*gen_replacestr(char c)
{
	char	*replace;

	replace = malloc(sizeof(char) * (3 + 1));
	replace[0] = ' ';
	replace[1] = c;
	replace[2] = ' ';
	replace[3] = '\0';
	return (replace);
}

char	*specialchar_sep(char *string, char *specialchars)
{
	size_t	len;
	size_t	i;
	char	*replace;

	while (*specialchars)
	{
		len = count_unescapedchr(string, *specialchars);
		replace = gen_replacestr(*specialchars);
		string = ft_strreplacec(string, *specialchars, replace);
		i = 1;
		while (i < len)
		{
			string = ft_strreplacec(NULL, *specialchars, replace);
			i++;
		}
		free(replace);
		specialchars++;
	}
	return (string);
}
