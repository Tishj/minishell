/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_parse.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/18 14:53:40 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/06 17:04:09 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtokplus(char *input, char *delim)
{
	static char	*buffer;
	char		*ret;
	char		stop;

	stop = ' ';
	if (!buffer || input)
		buffer = input;
	if (*buffer == '\0')
		return (NULL);
	while (buffer && *buffer == ' ')
		buffer++;
	ret = buffer;
	while (buffer && *buffer && !ft_chrmatchc(*buffer, stop))
	{
		if (ft_chrmatchs(*buffer, delim) && stop == ' ')
		{
			ret = buffer + 1;
			stop = *buffer;
		}
		buffer++;
	}
	buffer++;
	*(buffer - 1) = '\0';
	return (ret);
}

char	ft_delim(char *token, char *arg_end)
{
	while (*token)
		token++;
	token++;
	while (token < arg_end && ft_chrmatchs(*token, " "))
		token++;
	if (ft_chrmatchs(*token, "\"\'"))
		return (*token);
	return (' ');
}

int		main(void)
{
	char	*arg_start;
	char	*arg_end;
	char	*token;

	while(1)
	{
		ft_fdstrc(1, &arg_start, '\n');
		arg_end = arg_start + ft_strlen(arg_start);
		token = ft_strtokplus(arg_start, "\"\'");
		while (token)
		{
			ft_strprint(token);
//			delim = ft_delim(token, arg_end);
			token = ft_strtokplus(NULL, "\"\'");
		}
		free(arg_start);
		arg_start = NULL;
	}
	free(arg_start);
	return (0);
}

/* 
**	Brace Expansion:			Expansion of expressions within braces.
**	Tilde Expansion:			Expansion of the ~ character.
**	Shell Parameter Expansion:	How Bash expands variables to their values.
**	Command Substitution:	  	Using the output of a command as an argument.
**	Arithmetic Expansion:	  	How to use arithmetic in shell expansions.
**	Process Substitution:		A way to write and read to and from a command.
**	Word Splitting:				How the results of expansion are split into separate arguments.
**	Filename Expansion:			A shorthand for specifying filenames matching patterns.
**	Quote Removal:				How and when quote characters are removed from words
*/
