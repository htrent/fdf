/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 11:29:04 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 16:20:02 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	const char	*buf2;
	char		*ret;
	char		*buf1;

	buf1 = s1;
	ret = buf1;
	buf2 = s2;
	while (*buf1)
		buf1++;
	while (n-- && *buf2)
	{
		*buf1 = *buf2;
		buf1++;
		buf2++;
	}
	*buf1 = '\0';
	return (ret);
}
