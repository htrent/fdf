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

char	*ft_add_to_list(t_gnl_list **head, char *str, int fd)
{
	t_gnl_list	*list;
	int			i;
	t_gnl_list	*node;
	t_gnl_list	*begin;

	i = 0;
	list = *head;
	if (list == NULL)
		list = ft_create_elem_gnl(str[i++], fd);
	begin = list;
	while (list->next)
		list = list->next;
	while (str[i])
	{
		node = ft_create_elem_gnl(str[i++], fd);
		list->next = node;
		list = list->next;
	}
	*head = begin;
	free(str);
	str = ft_strnew(BUFF_SIZE);
	return (str);
}

void	ft_help(t_gnl_list **list, t_gnl_list *buf, char *str, int fd)
{
	t_gnl_list	*to_clear;
	t_gnl_list	*prev;

	prev = NULL;
	while (buf)
		if (buf->fd == fd)
		{
			if (prev != NULL)
				prev->next = buf->next;
			else
				(*list) = (*list)->next;
			to_clear = buf;
			*(str++) = buf->data;
			buf = buf->next;
			free(to_clear);
			if (*(str - 1) == '\n')
				break ;
		}
		else
		{
			prev = buf;
			buf = buf->next;
		}
	if (*(str - 1) == '\n')
		*(str - 1) = '\0';
}

char	*ft_list_to_str(t_gnl_list **list, int count, int i, int fd)
{
	char		*str;
	char		*beg;
	t_gnl_list	*buf;

	buf = *list;
	str = ft_strnew(count * BUFF_SIZE + i);
	beg = str;
	ft_help(list, buf, str, fd);
	return (beg);
}

int		ft_check_list(t_gnl_list *list, int fd)
{
	int			i;
	t_gnl_list	*buf;

	buf = list;
	i = 0;
	while (buf)
	{
		if (buf->fd == fd)
		{
			i++;
			if (buf->data == '\n')
				return (i);
		}
		buf = buf->next;
	}
	if (buf == NULL)
		return (i);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	char				*str;
	int					rt;
	int					i;
	static t_gnl_list	*list;
	int					count_of_calls;

	count_of_calls = 0;
	if (fd < 0 || !line)
		return (-1);
	if (list != NULL && (i = ft_check_list(list, fd)))
		return (*line = ft_list_to_str(&list, 0, i, fd)) ? 1 : 1;
	if ((str = ft_strnew(BUFF_SIZE)) == NULL)
		return (0);
	while ((i = ft_istrchr(str, '\n')) == -1 && (++count_of_calls))
		if ((rt = read(fd, str, BUFF_SIZE)) <= 0)
			break ;
		else
			str = ft_add_to_list(&list, str, fd);
	free(str);
	if (rt == -1)
		return (-1);
	*line = ft_list_to_str(&list, count_of_calls, i, fd);
	if (rt == 0 && i == -1 && ft_strlen(*line) == 0)
		return (0);
	return (1);
}
