/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:21:58 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 16:20:02 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*str;
	size_t		len;
	size_t		i;
	const char	*buf;
	char		*ret;

	if (!s)
		return (NULL);
	buf = s;
	i = 0;
	len = ft_strlen(s);
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	ret = str;
	while (*buf)
	{
		*str = (*f)(i, *buf);
		str++;
		buf++;
		i++;
	}
	return (ret);
}
