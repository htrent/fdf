/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:44:59 by htrent            #+#    #+#             */
/*   Updated: 2019/09/17 16:44:59 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_list(t_gnl_list *list)
{
	t_gnl_list *begin;

	begin = list;
	if (list == NULL)
		return ;
	while (begin)
	{
		ft_putchar(begin->data);
		begin = begin->next;
	}
}
