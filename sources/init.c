/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 19:05:13 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*map_init()
{
	t_map	*map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL); //add terminate
	map->width = 0;
	map->height = 0;
	map->coords = NULL;
	map->z_max = -2147483648;
	map->z_min = 2147483647;
	return (map);
}

t_fdf	*fdf_init(t_map *map)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel),
			&(fdf->size_line), &(fdf->endian));
	ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
	fdf->map = map;
	fdf->alpha = 0;
	fdf->beta = 0;
	fdf->gamma = 0;
	fdf->projection = ISO;
	fdf->z_high = 1;
	fdf->zoom = min(WIDTH / (2 * fdf->map->width), HEIGHT / (2 * fdf->map->height));
	fdf->mouse_status = NOTPRESSED;
	fdf->mouse_pos.x = WIDTH / 2;
	fdf->mouse_pos.y = HEIGHT / 2;
	fdf->menu_tr = NOT_TRANSPARENT;
	fdf->menu = NOT_PERMANENT;
	return (fdf);
}
