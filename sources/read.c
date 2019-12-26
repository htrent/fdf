/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2019/12/26 16:38:22 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	read_to_stack(int fd, t_stack **coord)
{
	t_point point;
	char **split_line;
	char **split_coord_color;
	char *line;

	point.y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if ((split_line = ft_strsplit(line, ' ')))
		{
			point.x = 0;
			while (*split_line)
			{
				split_coord_color = ft_strsplit(*split_line, ',');
				if (!split_coord_color[1])
					point.color = DEF_CLR;
				else
					point.color = ft_atoi_base(split_coord_color[1], 16);
				push(coord, new_node(ft_atoi(split_coord_color[0]), point.color));
				split_line++;
				point.x++;
			}
		}
		free(line);
		point.y++;
	}
	return (point);
}

