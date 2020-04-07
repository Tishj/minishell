/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_str2print.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 01:59:48 by tbruinem       #+#    #+#                */
/*   Updated: 2020/04/02 13:04:58 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libext.h"

void	ft_str2print(char **str)
{
	size_t	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		ft_strprint(str[i]);
		i++;
	}
}
