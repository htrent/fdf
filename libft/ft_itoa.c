/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 18:59:41 by htrent            #+#    #+#             */
/*   Updated: 2019/09/09 17:42:01 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_of_digits(int n)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static int	check(char *str, int *n)
{
	if (!str)
		return (3);
	if (*n < 0)
	{
		if (*n == -2147483648)
		{
			*n = 147483648;
			return (2);
		}
		*n *= -1;
		return (1);
	}
	return (0);
}

static char	*ft_strrev(char *s)
{
	char	*s_rev;

	if (s == NULL)
		return (NULL);
	s_rev = ft_strnew(ft_strlen(s));
	s_rev += ft_strlen(s);
	while (*s)
	{
		s_rev--;
		*s_rev = *s;
		s++;
	}
	return (s_rev);
}

static char	*ft_istrnew(size_t size, int n)
{
	char	*new;
	size_t	i;

	i = 0;
	new = (char *)malloc(size + 1);
	if (n == 0)
	{
		*new = '0';
		return (new);
	}
	if (new == NULL)
		return (NULL);
	while (i < size + 1)
		new[i++] = '\0';
	return (new);
}

char		*ft_itoa(int n)
{
	int		count;
	char	*str;
	char	*buf;
	int		state;

	count = count_of_digits(n);
	str = (n < 0) ? ft_istrnew(count + 1, n) : ft_istrnew(count, n);
	if (n == 0)
		return (str);
	buf = str;
	if ((state = check(str, &n)) == 3)
		return (NULL);
	while (n)
	{
		*(str++) = n % 10 + '0';
		n = n / 10;
	}
	if (state)
	{
		if (state == 2)
			*(str++) = '2';
		*str = '-';
	}
	return (ft_strrev(buf));
}
