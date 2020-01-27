/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 19:59:30 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotation(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_6_PAD)
		fdf->beta += 0.05;
	if (keycode == KEY_4_PAD)
		fdf->beta -= 0.05;
	if (keycode == KEY_8_PAD)
		fdf->alpha += 0.05;
	if (keycode == KEY_2_PAD)
		fdf->alpha -= 0.05;
	if (keycode == KEY_1_PAD || keycode == KEY_3_PAD)
		fdf->gamma += 0.05;
	if (keycode == KEY_7_PAD || keycode == KEY_9_PAD)
		fdf->gamma -= 0.05;
}

void	change_proj(int keycode, t_fdf *fdf)
{
	fdf->projection = (keycode == KEY_I) ? ISO : PARALLEL;
	fdf->alpha = 0;
	fdf->beta = 0;
	fdf->gamma = 0;
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	fdf->zoom = min(WIDTH / (2 * fdf->map->width),
			HEIGHT / (2 * fdf->map->height));
	fdf->z_high = 1;
}

void	zoom_and_move(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_MINUS && fdf->zoom > 1)
		fdf->zoom--;
	if (keycode == KEY_PLUS)
		fdf->zoom++;
	if (keycode == KEY_UP)
		fdf->offset_y -= fdf->zoom / 5 + 1;
	if (keycode == KEY_DOWN)
		fdf->offset_y += fdf->zoom / 5 + 1;
	if (keycode == KEY_LEFT)
		fdf->offset_x -= fdf->zoom / 5 + 1;
	if (keycode == KEY_RIGHT)
		fdf->offset_x += fdf->zoom / 5 + 1;
}
