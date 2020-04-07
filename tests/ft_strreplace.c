/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strreplace.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/28 11:20:27 by tbruinem      #+#    #+#                 */
/*   Updated: 2020/04/03 14:36:37 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libext.h"

char	*ft_strreplacec(char *org, char c, char *replace)
{
	char			*new;
	char			*check;
	static size_t	processed = 0;
	static char		*buff;

	if (org)
	{
		buff = org;
		processed = 0;
	}
	if (!buff || !replace)
		return (NULL);
	check = ft_strchr(buff + processed, c);
	if (!check)
		return (buff);
	processed += check - (buff + processed);
	if (*(check - 1) == '\\')
	{
		processed++;
		return (ft_strreplacec(NULL, c, replace));
	}
	new = malloc(sizeof(char) *
		(ft_strlen(buff) + ft_strlen(replace)));
	(void)ft_strncpy(new, buff, check - buff);
	(void)ft_strcat(new, replace);
	(void)ft_strcat(new, buff + processed + 1);
	processed += ft_strlen(replace);
	free(buff);
	buff = new;
	return (new);
}

/*
**	This function returns a heap allocated string and also frees 'org'
*/

char	*ft_strreplace(char *org, char *before, char *after)
{
	char			*new;
	char			*check;
	static size_t	processed = 0;
	static char		*buff;

	if (org)
	{
		buff = org;
		processed = 0;
	}
	if (!buff || (!before || !after))
		return (NULL);
	check = ft_strstr(buff + processed, before);
	if (!check)
		return (buff);
	processed += check - (buff + processed);
	if (*(check - 1) == '\\')
	{
		processed += ft_strlen(before);
		return (ft_strreplace(NULL, before, after));
	}
	new = malloc(sizeof(char) *
		((ft_strlen(buff) + ft_strlen(after) - ft_strlen(before)) + 1));
	(void)ft_strncpy(new, buff, check - buff);
	(void)ft_strcat(new, after);
	(void)ft_strcat(new, buff + processed + ft_strlen(before));
	processed += ft_strlen(after);
	free(buff);
	buff = new;
	return (new);
}
