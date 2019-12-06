/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 16:21:55 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 17:15:47 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	void	*cont;
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	cont = (void *)malloc(content_size);
	if (!list || !cont)
		return (NULL);
	cont = (!content) ? NULL : ft_memcpy(cont, content, content_size);
	list->content = cont;
	list->content_size = (!content) ? 0 : content_size;
	list->next = NULL;
	return (list);
}
