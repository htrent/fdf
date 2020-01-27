/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 20:59:43 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_puterr(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int			min(int a, int b)
{
	return ((a > b) ? b : a);
}

t_point		new_point_map(int x, int y, t_map *map)
{
	t_point p;

	p.x = x;
	p.y = y;
	p.z = map->coords[y * map->width + x].z;
	p.color = (map->coords[y * map->width + x].color == -1) ?
			get_defcl(map->coords[y * map->width + x].z, map) :
			map->coords[y * map->width + x].color;
	return (p);
}

t_point		new_point(int x, int y, int color)
{
	t_point p;

	p.x = x;
	p.y = y;
	p.color = color;
	return (p);
}

void		error(char *s)
{
	ft_puterr(s);
	exit(1);
}
