/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_istrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:41:25 by htrent            #+#    #+#             */
/*   Updated: 2019/09/17 16:54:21 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_istrchr(const char *str, int c)
{
	const char	*buf;
	int			i;

	buf = str;
	i = 0;
	while (buf[i])
	{
		if (buf[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (-1);
}
