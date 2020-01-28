/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/28 13:14:19 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			exit_program(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void		mlx_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win, 17, 0, exit_program, fdf);
	mlx_hook(fdf->win, 2, 0, deal_key, fdf);
	mlx_hook(fdf->win, 4, 0, mouse_press, fdf);
	mlx_hook(fdf->win, 5, 0, mouse_release, fdf);
	mlx_hook(fdf->win, 6, 0, mouse_move, fdf);
}

void		deal_color(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_R)
		fdf->color = RAINBOW;
	if (keycode == KEY_D)
		fdf->color = DEFAULT_COLOR;
	if (keycode == KEY_E)
		fdf->color = DARK_MODE;
	if (keycode == KEY_F)
		fdf->color = TEST_COLOR;
	if (keycode == KEY_W && fdf->color < MAX_INT)
		fdf->color++;
}

static void	deal_key2(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_MORE && fdf->z_high > 0.1)
		fdf->z_high -= 0.05;
	if (keycode == KEY_LESS && fdf->z_high <= 20)
		fdf->z_high += 0.1;
	if (keycode == KEY_T)
		fdf->menu_tr = (fdf->menu_tr == TRANSPARENT) ?
				NOT_TRANSPARENT : TRANSPARENT;
	if (keycode == KEY_M)
		fdf->menu = (fdf->menu == PERMANENT) ? NOT_PERMANENT : PERMANENT;
	if (keycode == KEY_R || keycode == KEY_D || keycode == KEY_F ||
		keycode == KEY_E || keycode == KEY_W)
		deal_color(keycode, fdf);
	draw_map(fdf);
}

int			deal_key(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_MINUS || keycode == KEY_PLUS || keycode == KEY_UP ||
		keycode == KEY_DOWN || keycode == KEY_LEFT || keycode == KEY_RIGHT ||
		keycode == KEY_PLUS_NUM || keycode == KEY_MINUS_NUM)
		zoom_and_move(keycode, fdf);
	if (keycode == KEY_6_PAD || keycode == KEY_4_PAD || keycode == KEY_8_PAD ||
		keycode == KEY_2_PAD || keycode == KEY_1_PAD || keycode == KEY_3_PAD ||
		keycode == KEY_7_PAD || keycode == KEY_9_PAD)
		rotation(keycode, fdf);
	if (keycode == KEY_I || keycode == KEY_P)
		change_proj(keycode, fdf);
	deal_key2(keycode, fdf);
	return (keycode);
}
