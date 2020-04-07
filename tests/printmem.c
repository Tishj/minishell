/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printmem.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 10:50:16 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/03 11:03:46 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printmem(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		printf("str[%ld] = %c | %d | %p\n", i, str[i], (int)str[i], &str[i]);
		i++;
	}
	printf("str[%ld] = %c | %d | %p\n", i, str[i], (int)str[i], &str[i]);
}