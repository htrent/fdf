/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 13:22:37 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 16:20:02 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *buf;
	const char *beg;

	buf = s + ft_strlen(s);
	beg = s;
	while (buf != beg)
	{
		if ((unsigned char)*buf == (unsigned char)c)
			return (char *)(buf);
		buf--;
	}
	if ((unsigned char)*buf == (unsigned char)c)
		return ((char *)(buf));
	return (NULL);
}
