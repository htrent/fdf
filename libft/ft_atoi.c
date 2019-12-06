/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 16:20:02 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*trimmer(const char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\v' || *str == '\n'
	|| *str == '\r' || *str == '\f')
		str++;
	return (str);
}

static int			check(const char *str)
{
	if (*str == '-' && *(str + 1) >= '0' && *(str + 1) <= '9')
		return (-1);
	return (1);
}

int					ft_atoi(const char *str)
{
	const char	*buf;
	long int	res;
	int			ch;

	buf = trimmer(str);
	res = 0;
	ch = check(buf);
	if (*buf == '+' || *buf == '-')
		buf++;
	while (*buf >= '0' && *buf <= '9')
	{
		if (res * 10 + *buf - '0' < res)
		{
			if (ch == -1)
				return (0);
			else
				return (-1);
		}
		res = res * 10 + *buf - '0';
		buf++;
	}
	return (res * ch);
}
