/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 10:49:50 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 16:20:02 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*s;
	size_t		len;
	const char	*buf;

	buf = s1;
	len = ft_strlen(s1);
	s = ft_strnew(len);
	if (s == NULL)
		return (NULL);
	while (len--)
		*(s++) = *(buf++);
	s -= ft_strlen(s1);
	return (s);
}
