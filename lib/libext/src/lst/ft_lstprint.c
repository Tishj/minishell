/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstprint.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/17 00:52:45 by tbruinem       #+#    #+#                */
/*   Updated: 2020/03/30 23:50:39 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libext.h"

void	ft_lstprint(t_list *head, void (*p)(void *item))
{
	while (head)
	{
		p((head->item));
		head = head->next;
	}
}
