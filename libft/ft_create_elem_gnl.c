/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:45:30 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 17:48:52 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_gnl_list	*ft_create_elem_gnl(char data, int fd)
{
	t_gnl_list *list;

	list = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	list->next = NULL;
	list->data = data;
	list->fd = fd;
	return (list);
}
