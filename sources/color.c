/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/28 13:06:21 by htrent           ###   ########.fr       */
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

int		get_defcl(int z, t_map *map, t_fdf *fdf)
{
	double percent;

	percent = z * 1.0 / (map->z_max - map->z_min);
	if (fdf->color == DEFAULT_COLOR || fdf->color % 5 == 0)
		return (default_color(percent));
	if (fdf->color == RAINBOW || fdf->color % 4 == 0)
		return (rainbow_color(percent));
	if (fdf->color == DARK_MODE || fdf->color % DARK_MODE == 0)
		return (darkmode_color(percent));
	if (fdf->color == TEST_COLOR || fdf->color % TEST_COLOR == 0)
		return (test_color(percent));
	return (default_color(percent));
}
