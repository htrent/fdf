/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:28:30 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 18:32:04 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	char const	*buf1;
	char const	*buf2;
	size_t		i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	buf1 = s1;
	buf2 = s2;
	if (s1 == s2 || (s1 == NULL && s2 == NULL) || n == 0)
		return (1);
	while ((*buf1 || *buf2) && i < n)
	{
		if (*buf1 != *buf2)
			return (0);
		buf1++;
		buf2++;
		i++;
	}
	if (*buf1 == '\0' || *buf2 == '\0')
		return (0);
	return (1);
}
