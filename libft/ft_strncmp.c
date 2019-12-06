/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 16:18:23 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 16:20:02 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const char *buf1;
	const char *buf2;

	buf1 = s1;
	buf2 = s2;
	while ((*buf1 || *buf2) && n--)
	{
		if (*buf1 != *buf2)
			return ((unsigned char)*buf1 - (unsigned char)*buf2);
		buf1++;
		buf2++;
	}
	return (0);
}
