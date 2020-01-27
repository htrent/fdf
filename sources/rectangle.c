/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 19:49:58 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_rectangles(t_fdf *fdf)
{
	if ((fdf->mouse_pos.x < MENU_WIDTH && fdf->mouse_pos.y < MENU_HEIGHT &&
		fdf->menu == NOT_PERMANENT) || fdf->menu == PERMANENT)
	{
		if (fdf->menu_tr == TRANSPARENT)
			put_transparent_rectangle(fdf, new_point(0, HEIGHT_OF_HEADER + 10,
					MENU_BACKGROUND), MENU_WIDTH, MENU_HEIGHT);
		if (fdf->menu_tr == NOT_TRANSPARENT)
			put_rectangle(fdf, new_point(0, HEIGHT_OF_HEADER + 10,
					MENU_BACKGROUND), MENU_WIDTH, MENU_HEIGHT);
	}
	put_rectangle(fdf, new_point(5, 5, HEADER_COLOR),
			(ft_strlen(fdf->map_name) + 6) * 10, HEIGHT_OF_HEADER);
}

void	put_rectangle(t_fdf *fdf, t_point p, int width, int height)
{
	t_point draw;

	draw = p;
	while (draw.y < height)
	{
		draw.x = p.x;
		while (draw.x < width)
		{
			put_pixel(fdf, draw, p.color);
			draw.x++;
		}
		draw.y++;
	}
}

void	put_transparent_rectangle(t_fdf *fdf, t_point p, int width, int height)
{
	t_point draw;

	draw = p;
	while (draw.y < height)
	{
		draw.x = p.x;
		while (draw.x < width)
		{
			if ((draw.x % 2) && (draw.y % 2))
				put_pixel(fdf, draw, p.color);
			draw.x++;
		}
		draw.y++;
	}
}
