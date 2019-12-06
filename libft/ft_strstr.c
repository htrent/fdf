/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 13:26:32 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 16:20:02 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char *hay;
	const char *nee;
	const char *buf;

	nee = needle;
	hay = haystack;
	buf = nee;
	while (*hay)
	{
		while (*hay == *nee && *hay && *nee)
		{
			hay++;
			nee++;
		}
		if (*nee == '\0')
			return ((char *)(hay - ft_strlen(needle)));
		else
			nee = buf;
		haystack++;
		hay = haystack;
	}
	if (*hay == 0 && *nee == 0)
		return (char*)(hay);
	return (NULL);
}
