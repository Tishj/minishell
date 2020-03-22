/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_parsing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/19 15:34:18 by tbruinem       #+#    #+#                */
/*   Updated: 2020/03/22 23:36:41 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Modified strprint, printing only the positive characters
**	Since we flipped a bunch of characters to negative
**	we have essentially removed them from the string
*/

char	**ft_str2addn(char **orig, size_t add)
{
	char	**new;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_str2len(orig);
	printf("len of orig: %ld\n", len);
	new = ft_calloc(sizeof(char *), (len + add + 1));
	while (i < len)
	{
		new[i] = orig[i];
		i++;
	}
	new[i] = 0;
	ft_str2del(orig);
	return (new);
}

void	ft_modstrprint(char *str)
{
	size_t	size;

	while (*str)
	{
		size = ft_strrlen(str, -128, -1);
		if (size)
			write(1, str, size);
		str += (size) ? size : 1;
	}
	write(1, "\n", 1);
}

/*
**	Flip the first " to negative
**	Loop until the first unescaped ", flip it to negative
**	Escape $,\n,`," when appropriate.
*/

int		ft_stringquote(char *str)
{
	char	last;
	int		i;

	i = 0;
	str[i - 1] *= -1;
	while (str[i] && (str[i] != '"' || last == '\\'))
	{
		if (last == '\\' && ft_chrmatchs(str[i], "abcef0ntvrx$\n\"`\\"))
			ft_escaper(str + i, &last);
		else
			last = str[i];
		i++;
	}
	if (str[i] == '"')
		str[i] *= -1;
	return (i);
}

/*
**	Flip the first ' to negative
**	Loop until the next ' and flip it to negative
**	Flipping escape characters to negative aswell.
*/

int		ft_literalquote(char *str)
{
	char	last;
	int		i;

	i = 0;
	last = 0;
	str[i - 1] *= -1;
	while (str[i] && str[i] != '\'')
	{
		if (last == '\\' && ft_chrmatchs(str[i], "abcef0ntvrx\\"))
			ft_escaper(str + i, &last);
		else
			last = str[i];
		i++;
	}
	if (str[i] == '\'')
		str[i] *= -1;
	return (i);
}

/*
**	Keep a pointer to the string in memory (buff)
**	i for iterator;
**	- Loop as long as a space is not found or the string ends
**
**	In between, check for escape characters and quotes:
**	- React accordingly.
**	- Flip escape character '\' to negative.
**
**	return buff and increase buff to (buff + i + 1)
**	similar to strtok
*/

int		ft_splitter(char *buff)
{
	size_t	i;
	char	last;

	i = 0;
	last = 0;
	while (buff[i] && buff[i] != ' ')
	{
		if (last == '\\' && buff[i] > 0)
			buff[i - 1] *= -1;
		if (buff[i] == '"' && last != '\\')
			i += ft_stringquote(buff + i + 1);
		else if (buff[i] == '\'' && last != '\\')
			i += ft_literalquote(buff + i + 1);
		i++;
		last = buff[i - 1];
	}
	return (i);
}

/*
**	Splitter setup, setting buff, preparing ret etc..
*/

char	*ft_wordsplit(char *str)
{
	static char	*buff;
	char		*ret;

	if (str)
		buff = str;
	if (*buff == '\0')
		return (NULL);
	ret = buff;
	buff += (ft_splitter(buff) + 1);
	*(buff - 1) = '\0';
	return ((buff - 1) - ret) ? ret : ft_wordsplit(NULL);
}

char	**parsing(char *input)
{
	char	**args;
	char	*program;
	size_t	i;

	i = 0;
	args = ft_calloc(sizeof(char *), (ft_strclenb(input, ' ') + 1));
	program = ft_wordsplit(input);
	program = get_abs_path(program);
	if (!program)
		return (NULL); //error
	args[i] = ft_strdup(program);
	while (args[i])
	{
		i++;
		args[i] = ft_wordsplit(NULL);
	}
	args[i] = 0;
	return (args);
}
