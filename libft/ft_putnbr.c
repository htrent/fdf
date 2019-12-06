/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 19:26:30 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 16:20:02 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_of_digits(int n)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static int	pow_10(int i)
{
	int ret;

	ret = 1;
	while (i--)
		ret *= 10;
	return (ret);
}

static int	check(int n, int *count)
{
	if (n < 0)
	{
		ft_putchar('-');
		if (n == -2147483648)
		{
			ft_putchar('2');
			(*count)--;
			return (147483648);
		}
		return (n * -1);
	}
	return (n);
}

void		ft_putnbr(int n)
{
	int count;
	int buf_count;
	int delta;

	count = count_of_digits(n);
	buf_count = count;
	n = check(n, &count);
	while (count)
	{
		buf_count = count_of_digits(n);
		delta = count - buf_count;
		if (delta > 0)
		{
			while (delta--)
				ft_putchar('0');
			count = buf_count;
		}
		ft_putchar(n / pow_10(count_of_digits(n) - 1) + '0');
		n = n % pow_10(count_of_digits(n) - 1);
		count--;
	}
}
