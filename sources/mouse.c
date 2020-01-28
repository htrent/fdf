/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/28 11:39:13 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			mouse_press(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == MOUSE_SCROLL_UP && fdf->zoom <= 200)
		fdf->zoom++;
	if (button == MOUSE_SCROLL_DOWN && fdf->zoom > 1)
		fdf->zoom--;
	if (button == MOUSE_LEFT_CLICK)
		fdf->mouse_status = PRESSED_LEFT;
	if (button == MOUSE_RIGHT_CLICK)
		fdf->mouse_status = PRESSED_RIGHT;
	draw_map(fdf);
	return (0);
}

int			mouse_release(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	(void)button;
	fdf->mouse_status = NOTPRESSED;
	return (0);
}

int			mouse_move(int x, int y, t_fdf *fdf)
{
	fdf->mouse_prevpos = fdf->mouse_pos;
	fdf->mouse_pos.x = x;
	fdf->mouse_pos.y = y;
	if (fdf->mouse_status == PRESSED_LEFT)
	{
		fdf->beta += (x - fdf->mouse_prevpos.x) * 0.002;
		fdf->alpha += (y - fdf->mouse_prevpos.y) * 0.002;
	}
	if (fdf->mouse_status == PRESSED_RIGHT)
	{
		fdf->offset_x += x - fdf->mouse_prevpos.x;
		fdf->offset_y += y - fdf->mouse_prevpos.y;
	}
	draw_map(fdf);
	return (0);
}
