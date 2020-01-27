/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 18:17:05 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	more_free(char **str)
{
	int i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

static	void	push_to_stack(char **split_line, t_stack **coord, t_map *map)
{
	int x;
	char **scc;

	x = 0;
	while(split_line[x])
	{
		scc = ft_strsplit(split_line[x++], ',');
		if (!ft_isnumber(scc[0], 10))
			error("Some problems with map...\n");
		if (scc[1] && !ft_isnumber(scc[1], 16))
			error("Some problems with map...\n");
		push(coord, new_node(ft_atoi(scc[0]), (!scc[1]) ? -1 :
		ft_atoi_base(scc[1], 16)));
		more_free(scc);
	}
	if (map->height == 0)
		map->width = x;
	else if (map->height > 0 && map->width != x)
		error("Some problems with map...\n");
}

int		read_to_stack(int fd, t_stack **coord, t_map *map)
{
	char **split_line;
	char *line;
	int res;

	line = NULL;
	while ((res = get_next_line(fd, &line)) == 1)
	{
		if (!(split_line = ft_strsplit(line, ' ')))
			error("Error with ft_strsplit in read_to_stack...\n");
		push_to_stack(split_line, coord, map);
		more_free(split_line);
		ft_strdel(&line);
		map->height++;
	}
	ft_strdel(&line);
	if (!(*coord))
		error("Some problems with map...\n");
	return (res);
}

