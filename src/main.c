/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 23:03:05 by tbruinem       #+#    #+#                */
/*   Updated: 2020/02/29 23:32:48 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

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
