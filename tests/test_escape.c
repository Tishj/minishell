/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_escape.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/20 14:47:55 by tbruinem       #+#    #+#                */
/*   Updated: 2020/03/30 21:39:32 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef int (*t_escapef)(char *str);

char	*ft_strchr(char *str, char c)
{
	while (*str && *str != c)
		str++;
	return ((*str == c) ? str : NULL);
}

char	*ft_strnump_base(char *str, int *val, char *base, int limit)
{
	int		ret;
	int		n;
	int		base_num;
	size_t	i;

	base_num = ft_strlen(base);
	ret = 0;
	i = 0;
	i += ft_strskipw(str);
	n = (str[i] == '-') ? -1 : 1;
	i = (str[i] == '-' || str[i] == '+') ? i + 1 : i;
	while (ft_chrmatchs(str[i], base) && (int)i < limit)
	{
		ret = (ret * base_num) + (ft_strchr(base, str[i]) - base);
		i++;
		*val = ret;
	}
	*val = (ret * n);
	return (ret) ? &str[i] : NULL;
}

int		ft_esc_hex(char *str)
{
	size_t	i;
	char	*end_upper;
	char	*end_lower;
	int		hex_upper;
	int		hex_lower;

	i = 1;
	str[0] = '\0';
	end_upper = ft_strnump_base(str + 1, &hex_upper, "0123456789ABCDEF", 2);
	end_lower = ft_strnump_base(str + 1, &hex_lower, "0123456789abcdef", 2);
	if (!end_lower && !end_upper)
		return (1);
	if (end_upper > end_lower)
	{
		end_lower = end_upper;
		hex_lower = hex_upper;
	}
	str[0] = (char)hex_lower;
	while (str + i < end_lower)
	{
		str[i] *= -1;
		i++;
	}
	return ((int)(end_lower - str));
}

int		ft_esc_oct(char *str)
{
	size_t	i;
	char	*end;
	int		oct;

	i = 1;
	str[0] = '\0';
	end = ft_strnump_base(str + 1, &oct, "01234567", 3);
	if (!end)
		return (1);
	str[0] = (char)oct;
	while (str + i < end)
	{
		str[i] *= -1;
		i++;
	}
	return ((int)(end - str));
}

int		ft_esc_single(char *str)
{
	static char	esc_char[] = {
	['a'] = '\a',
	['b'] = '\b',
	['c'] = '\x03',
	['e'] = '\x1B',
	['f'] = '\f',
	['n'] = '\n',
	['r'] = '\r',
	['t'] = '\t',
	['v'] = '\v',
	['\\'] = '\\',
	};

	*str = esc_char[*str];
	return (1);
}

int		ft_escaper(char *str, char *last)
{
	static const t_escapef handler[127] = {
	['a'] = &ft_esc_single,
	['b'] = &ft_esc_single,
	['c'] = &ft_esc_single,
	['e'] = &ft_esc_single,
	['f'] = &ft_esc_single,
	['n'] = &ft_esc_single,
	['r'] = &ft_esc_single,
	['t'] = &ft_esc_single,
	['v'] = &ft_esc_single,
	['\\'] = &ft_esc_single,
	['x'] = &ft_esc_hex,
	['0'] = &ft_esc_oct,
//	['u'] = &ft_esc_unismall,
//	['U'] = &ft_esc_unibig,
	};

	*(str - 1) *= -1;
	*last = 0;
	if (*str <= 0 || handler[*str] == 0)
		return (0);
	return ((handler[*str](str)));
}
