/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:46:42 by htrent            #+#    #+#             */
/*   Updated: 2019/09/09 18:16:41 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const void	*buf;
	char		*dst_buf;

	dst_buf = dst;
	buf = src;
	while (n--)
	{
		*(unsigned char *)(dst_buf++) = *(unsigned char *)(buf++);
		if (*(unsigned char*)(dst_buf - 1) == (unsigned char)c)
			return (dst_buf);
	}
	return (NULL);
}
