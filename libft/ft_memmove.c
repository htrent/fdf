/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 21:59:33 by htrent            #+#    #+#             */
/*   Updated: 2019/09/09 18:12:06 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_buf;
	char	*src_buf;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	dst_buf = (char *)dst;
	src_buf = (char *)src;
	i = 0;
	if (src_buf < dst_buf)
		while (len != 0)
		{
			*(dst_buf + len - 1) = *(src_buf + len - 1);
			len--;
		}
	else
		while (i < len)
		{
			*(dst_buf + i) = *(src_buf + i);
			i++;
		}
	return (dst);
}
