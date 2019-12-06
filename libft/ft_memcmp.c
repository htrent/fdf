/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 22:31:49 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 16:20:02 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const void *buf1;
	const void *buf2;

	buf1 = s1;
	buf2 = s2;
	while (n--)
	{
		if (*(unsigned char *)buf1 != *(unsigned char *)buf2)
			return (*(unsigned char*)buf1 - *(unsigned char*)buf2);
		buf1++;
		buf2++;
	}
	return (0);
}
