/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:37:44 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 16:20:12 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const void	*buf;
	void		*begin;

	if (src == NULL && dst == NULL)
		return (NULL);
	begin = dst;
	buf = src;
	while (n--)
		*(unsigned char*)(dst++) = *(unsigned char *)(buf++);
	return (begin);
}
