/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
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

static int	check(int n, int *count, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			ft_putchar_fd('2', fd);
			(*count)--;
			return (147483648);
		}
		return (n * -1);
	}
	return (n);
}

void		ft_putnbr_fd(int n, int fd)
{
	int count;
	int buf_count;
	int delta;

	count = count_of_digits(n);
	buf_count = count;
	n = check(n, &count, fd);
	while (count)
	{
		buf_count = count_of_digits(n);
		delta = count - buf_count;
		if (delta > 0)
		{
			while (delta--)
				ft_putchar_fd('0', fd);
			count = buf_count;
		}
		ft_putchar_fd((n / pow_10(count_of_digits(n) - 1) + '0'), fd);
		n = n % pow_10(count_of_digits(n) - 1);
		count--;
	}
}
