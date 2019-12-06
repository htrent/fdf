/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:28:30 by htrent            #+#    #+#             */
/*   Updated: 2019/09/06 21:01:32 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	char const *buf1;
	char const *buf2;

	if (!s1 || !s2)
		return (0);
	buf1 = s1;
	buf2 = s2;
	while (*buf1 || *buf2)
	{
		if (*buf1 != *buf2)
			return (0);
		buf1++;
		buf2++;
	}
	if (*buf1 == '\0' && *buf2 == '\0')
		return (1);
	return (0);
}
