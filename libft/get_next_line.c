/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:45:30 by htrent            #+#    #+#             */
/*   Updated: 2019/10/31 12:51:14 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_find_fd(t_list *head, const int fd)
{
	t_list *ptr;

	ptr = head;
	while (ptr)
	{
		if (ptr->content_size == (size_t)fd)
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

int		ft_free_node_fd(t_list **head, const int fd)
{
	t_list	*node;
	t_list	*prev;
	t_list	*to_del;

	prev = NULL;
	node = *head;
	while (node)
	{
		if (node->content_size == (size_t)fd)
		{
			to_del = node;
			if (!prev)
				*head = (*head)->next;
			else
				prev->next = node->next;
			free(to_del);
			return (1);
		}
		prev = node;
		node = node->next;
	}
	return (1);
}

int		ft_check_and_pull(t_list *node, char **line)
{
	char *newline;
	char *to_del;

	if (node)
	{
		newline = ft_strchr(node->content, '\n');
		if (newline)
		{
			*(newline++) = '\0';
			*line = ft_strdup(node->content);
			to_del = node->content;
			node->content = ft_strdup(newline);
			free(to_del);
			return (1);
		}
	}
	return (0);
}

void	ft_write_line(char *newline, char **line, t_list *node)
{
	char	*to_del;

	if (newline)
	{
		*(newline++) = '\0';
		*line = ft_strdup(node->content);
		to_del = node->content;
		node->content = ft_strdup(newline);
		free(to_del);
	}
	else
	{
		*line = ft_strdup(node->content);
		to_del = node->content;
		free(to_del);
		node->content = NULL;
	}
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*list;
	int				rt;
	char			buf[BUFF_SIZE + 1];
	char			*newline;
	t_list			*node;

	if (fd < 0 || read(fd, buf, 0) == -1 || !line)
		return (-1);
	newline = NULL;
	if (ft_check_and_pull(node = ft_find_fd(list, fd), line))
		return (1);
	while (!newline && (rt = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[rt] = '\0';
		if (!node)
			ft_lstadd(&list, node = ft_create_node(ft_strdup(buf), fd));
		else
			node->content = ft_strjoin(node->content, buf);
		newline = ft_strchr(node->content, '\n');
	}
	if ((!node || (rt == 0 && ft_strlen(node->content) == 0
	&& ft_free_node_fd(&list, fd))) && !(*line = NULL))
		return (0);
	ft_write_line(newline, line, node);
	return (1);
}
