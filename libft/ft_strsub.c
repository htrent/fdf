/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:36:28 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 16:20:02 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *str;
	char *ret;

	if (!s)
		return (NULL);
	str = ft_strnew(len);
	ret = str;
	if (str == NULL)
		return (NULL);
	s = s + start;
	while (len--)
	{
		*(char *)str = *s;
		s++;
		str++;
	}
	return (ret);
}
