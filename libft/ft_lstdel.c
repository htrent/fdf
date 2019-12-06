/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <htrent@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:16:25 by htrent            #+#    #+#             */
/*   Updated: 2019/09/08 17:28:23 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;

	list = *alst;
	while (*alst)
	{
		(*alst) = (*alst)->next;
		(*del)(list->content, list->content_size);
		free(list);
		list = (*alst);
	}
	*alst = NULL;
}
