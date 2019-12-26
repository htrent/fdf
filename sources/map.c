/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2019/12/26 19:04:57 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_map_color(t_fdf *fdf)
{
	float deltaz;
	int i;
	int j;

	i = 0;
	deltaz = fdf->z_max.z - fdf->z_min.z;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			fdf->map[i][j].color = (fdf->z_min.z < 0) ? get_defcl((fdf->z_max.z + fdf->map[i][j].z) / deltaz) : get_defcl(fdf->map[i][j].z / deltaz);
			j++;
		}
		i++;
	}
}

t_point	**stack_to_map(t_stack *coord, int x, int y)
{
	t_stack *temp;
	t_point **map;
	int 	i;
	int 	j;

	temp = coord;
	if (!(map = (t_point **)malloc(sizeof(t_point *) * y)))
		return (NULL);
	i = 0;
	while (i < y)
		if (!(map[i++] = (t_point *)malloc(sizeof(t_point) * x)))
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return (NULL);
		}
	i = y - 1;
	while (i >= 0)
	{
		j = x - 1;
		while (j >= 0)
		{
			map[i][j].x = j;
			map[i][j].y = i;
			map[i][j].z = temp->z;
			map[i][j].color = temp->color;
			temp = temp->next;
			j--;
		}
		i--;
	}

	return (map);
}

void	print_map(t_point **map, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			printf("%2d ", map[i][j].z);
			j++;
		}
		printf("\n");
		i++;
	}
}

void init_max_min_z(t_fdf *fdf)
{
	int i;
	int j;

	fdf->z_max.z = fdf->map[0][0].z;
	fdf->z_min.z = fdf->map[0][0].z;
	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (fdf->map[i][j].z > fdf->z_max.z)
				fdf->z_max = fdf->map[i][j];
			if (fdf->map[i][j].z < fdf->z_min.z)
				fdf->z_min = fdf->map[i][j];
			j++;
		}
		i++;
	}
}