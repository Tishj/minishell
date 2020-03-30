/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_parsing.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/19 15:34:18 by tbruinem       #+#    #+#                */
/*   Updated: 2020/03/30 21:29:45 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlenr(char *str, char rstart, char rend)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] >= rstart && str[i] <= rend)
			len++;
		i++;
	}
	return (len);
}

char	*ft_strdupr(char *orig, char rstart, char rend)
{
	size_t	i;
	size_t	len;
	char	*new;

	len = ft_strlenr(orig, rstart, rend);
	i = 0;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (*orig)
	{
		if (*orig >= rstart && *orig <= rend)
		{
			new[i] = *orig;
			i++;
		}
		orig++;
	}
	new[i] = 0;
	return (new);
}

char	**ft_str2clean(char **orig)
{
	char	**new;
	size_t	len;
	size_t	i;

	if (!orig)
		return (NULL);
	len = ft_str2len(orig);
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (orig[i])
	{
		new[i] = ft_strdupr(orig[i], (char)0, (char)127);
		if (!new[i])
		{
			ft_str2del(new);
			return (orig);
		}
		i++;
	}
	ft_str2del(orig);
	new[i] = 0;
	return (new);
}

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

//obsolete, used to debug wordsplit.
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
	printf("tokenbuffer: %s\n", buff);
	if (*buff == '\0')
		return (NULL);
	ret = buff;
	buff += (ft_splitter(buff) + 1);
	*(buff - 1) = '\0';
	return ((buff - 1) - ret) ? ret : ft_wordsplit(NULL);
}

/*
**	Receive a string, that has been gotten with fdstrc through STDIN <- malloced.
**	Create a 2d string for the size of strclenb(input)
**	returns all the arguments (char **) needed to call an executable or builtin.
*/
char	**parsing(char *input)
{
	char	**args;
	char	*program;
	size_t	i;
	size_t	blocks;

	blocks = ft_strclenb(input, ' ');
	i = 0;
	args = ft_calloc(sizeof(char *), blocks + 1);
	program = ft_wordsplit(input);
	printf("program token: %s\n", program);
	program = get_abs_path(program);
	args[i] = program;
	if (!args[i])
	{
		printf("Yep, this is not good\n");
		return (NULL);
	}
	while (args[i])
	{
		i++;
		args[i] = ft_strdup(ft_wordsplit(NULL));
	}
	args[i] = 0;
	args = ft_str2clean(args);
	return (args);
}
