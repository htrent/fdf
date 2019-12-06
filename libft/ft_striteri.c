/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:05:58 by htrent            #+#    #+#             */
/*   Updated: 2019/09/03 15:21:39 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	char			*ret;
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	ret = s;
	while (*s)
	{
		(*f)(i, s);
		s++;
		i++;
	}
	s = ret;
}
