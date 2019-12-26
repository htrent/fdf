/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2019/12/26 16:39:44 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		exit_program(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	mlx_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win, 17, 0, exit_program, fdf);
	mlx_hook(fdf->win, 2, 0, deal_key, fdf);
	mlx_hook(fdf->win, 4, 0, mouse_press, fdf);
	mlx_hook(fdf->win, 5, 0, mouse_release, fdf);
	mlx_hook(fdf->win, 6, 0, mouse_move, fdf);
}

int		deal_key(int keycode, t_fdf *fdf)
{
	//printf("key: %d\n", keycode);
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_MINUS)
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
	if (keycode == KEY_I || keycode == KEY_P)
	{
		fdf->projection = (keycode == KEY_I) ? ISO : PARALLEL;
		fdf->alpha = 0;
		fdf->beta = 0;
		fdf->gamma = 0;
		fdf->offset_x = 0;
		fdf->offset_y = 0;
		fdf->zoom = 30;
		fdf->z_high = 1;
	}
	if (keycode == KEY_MORE && fdf->z_high > 0.1)
		fdf->z_high -= 0.05;
	if (keycode == KEY_LESS && fdf->z_high <= 20)
		fdf->z_high += 0.1;
	draw_map(fdf);
	return (keycode);
}