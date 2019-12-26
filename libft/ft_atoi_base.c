/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:58:37 by htrent            #+#    #+#             */
/*   Updated: 2019/12/26 18:29:15 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int ft_pow(int a, int b)
{
	int i;
	int c;

	c = 1;
	i = 0;
	if (b == 0)
		return (1);
	while (i < b)
	{
		c *= a;
		i++;
	}
	return (c);

}

static int check_digit(char c, int str_base)
{
	int i;
	char *digits;
	char *digits_up;

	digits = "0123456789abcdef";
	digits_up = "0123456789ABCDEF";
	i = 0;
	while (i < str_base)
	{
		if (c == digits[i] || c == digits_up[i])
			return (1);
		i++;
	}
	return (0);
}

static int max_pos(const char *str, int str_base)
{
	int i;

	i = -1;
	while (check_digit(*str, str_base))
	{
		i++;
		str++;
	}
	return (i);
}

static int add_to_num(char c, int str_base, int pos)
{
	if (c >= 'a' && c <= 'f')
		return ((c - 87) * ft_pow(str_base, pos));
	else if (c >= 'A' && c <= 'F')
		return ((c - 55) * ft_pow(str_base, pos));
	else
		return ((c - 48) * ft_pow(str_base, pos));
}

int ft_atoi_base(const char *str, int str_base)
{
	int num;
	int sign;
	int pos;

	num = 0;
	sign = 1;
	if (*str == '-')
	{
		if (!check_digit(*(++str), str_base))
			return (0);
		sign = -1;
	}
	pos = max_pos(str, str_base);
	while (*str)
	{
		if (!check_digit(*str, str_base))
			return (num * sign);
		num += add_to_num(*(str++), str_base, pos--);
	}
	return (num * sign);
}
