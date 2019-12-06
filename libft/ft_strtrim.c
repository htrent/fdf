/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 17:18:35 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 19:04:47 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char		*str;
	char		*ret;
	char		*buf;

	buf = (s) ? ft_strdup(s) : NULL;
	if (buf == NULL)
		return (NULL);
	while (*buf == ' ' || *buf == '\n' || *buf == '\t')
		buf++;
	s = buf;
	while (*buf)
		buf++;
	while (*buf == ' ' || *buf == '\n' || *buf == '\t' || *buf == '\0')
		buf--;
	*(++buf) = '\0';
	str = ft_strnew(ft_strlen(s));
	if (str == NULL)
		return (NULL);
	ret = str;
	while (*s)
		*(str++) = *(s++);
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\0')
		str--;
	*(++str) = '\0';
	return (ret);
}
