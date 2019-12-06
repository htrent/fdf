/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 13:51:40 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 19:10:37 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*hay;
	const char	*nee;
	const char	*buf;
	size_t		buf_len;

	nee = needle;
	hay = haystack;
	buf = nee;
	if (*nee == 0 || (haystack == needle) || (len == 0 && *needle == 0))
		return (char *)(haystack);
	if (*hay == 0 || len == 0)
		return (NULL);
	len++;
	while (*haystack && --len != 0)
	{
		buf_len = len;
		while (*hay && *nee && *hay == *nee && (hay++) && buf_len-- != 0)
			nee++;
		if (*nee == '\0')
			return ((char *)(hay - ft_strlen(needle)));
		nee = buf;
		haystack++;
		hay = haystack;
	}
	return (NULL);
}
