/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 11:31:17 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 16:20:02 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *s, size_t n)
{
	size_t	result;

	(ft_strlen(dst) >= n) ? (result = ft_strlen(s) + n) :
	(result = ft_strlen(dst) + ft_strlen(s));
	if (n > 0)
		n--;
	while (*(dst++))
		if (n > 0)
			n--;
	dst--;
	while (n-- != 0 && *s)
		*(dst++) = *(s++);
	*dst = '\0';
	return (result);
}
