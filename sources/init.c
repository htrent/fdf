/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2019/12/26 16:47:10 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


t_fdf	*fdf_init(t_point **map, int x, int y)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel), &(fdf->size_line), &(fdf->endian));
	ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
	fdf->map = map;
	fdf->width = x;
	fdf->height = y;
	init_max_min_z(fdf);
	fdf->alpha = 0;
	fdf->beta = 0;
	fdf->gamma = 0;
	fdf->projection = 0;
	fdf->z_high = 1;
	fdf->zoom = min(WIDTH / (2 * fdf->width), HEIGHT / (2 * fdf->height));
	init_map_color(fdf);
	fdf->mouse_status = NOTPRESSED;
	fdf->mouse_pos.x = WIDTH / 2;
	fdf->mouse_pos.y = HEIGHT / 2;
	return (fdf);
}
