/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 23:56:44 by tbruinem       #+#    #+#                */
/*   Updated: 2020/02/28 00:02:38 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *output, char *arg)
{
	if (!arg)
		return ;
	write(1, output, ft_strlen(output));
	if (!ft_strcmp(arg, "-n"))
		write(1, "\n", 1);
}
