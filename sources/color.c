/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 18:08:37 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_light(int start, int end, float percentage)
{
	return ((1 - percentage) * start + percentage * end);
}

int		get_color(t_point p0, t_point p1, float percent)
{
	int r;
	int g;
	int b;

	r = get_light((p0.color >> 16) & 0xFF, (p1.color >> 16) & 0xFF, percent);
	g = get_light((p0.color >> 8) & 0xFF, (p1.color >> 8) & 0xFF, percent);
	b = get_light(p0.color & 0xFF, p1.color & 0xFF, percent);
	return ((r << 16) + (g << 8) + b);
}

int		get_defcl(int z, t_map *map)
{
	double percent;

	percent = z * 1.0 / (map->z_max - map->z_min);
	if (percent <= 0.3334)
		return (DEF_CLR);
	if (percent <= 0.6667)
		return (0x00ff00);
	return (0xff0000);
}
