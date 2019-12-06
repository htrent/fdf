/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:35:52 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 19:03:17 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*list;
	t_list	*beg;
	t_list	*buf;

	buf = lst;
	list = (t_list *)malloc(sizeof(t_list));
	if (!list || !lst || !f)
		return (NULL);
	ft_lstadd(&list, (*f)(buf));
	list->next = NULL;
	beg = list;
	buf = buf->next;
	while (buf)
	{
		ft_lstadd_back(&list, (*f)(buf));
		buf = buf->next;
	}
	return (beg);
}
