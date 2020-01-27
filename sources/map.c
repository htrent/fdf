/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 18:04:36 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	stack_to_map(t_stack **coord, t_map *map)
{
	t_stack *temp;
	int 	i;

	if (!(map->coords = (t_cmap *)malloc(sizeof(t_cmap) * map->width
			* map->height)))
		error("Some problems with mem.allocation in stack...\n");
	i = map->width * map->height - 1;
	while ((temp = pop(coord)) && i >= 0)
	{
		map->coords[i].z = temp->z;
		map->coords[i].color = temp->color;
		map->z_max = (temp->z > map->z_max) ? temp->z : map->z_max;
		map->z_min = (temp->z < map->z_min) ? temp->z : map->z_min;
		i--;
		free(temp);
	}
}

