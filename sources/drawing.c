/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 19:21:35 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_fdf *fdf, t_point p, int color)
{
	int	i;

	if (p.x >= 0 && p.x < WIDTH && p.y >= 0 && p.y < HEIGHT)
	{
		i = (p.x * fdf->bits_per_pixel / 8) + (p.y * fdf->size_line);
		fdf->data_addr[i] = color;
		fdf->data_addr[++i] = color >> 8;
		fdf->data_addr[++i] = color >> 16;
		fdf->data_addr[++i] = 0;
	}
}

static void	action(t_point *p, int sign[3], int A, int B, int *f)
{
	*f += (sign[0] == 1) ? B * sign[2] : A * sign[1];
	if (*f > 0)
	{
		*f -= (sign[0] == 1) ? A * sign[1] : B * sign[2];
		if (sign[0] == 1)
			p->x -= sign[2];
		else
			p->y += sign[1];
	}
	if (sign[0] == 1)
		p->y += sign[1];
	else
		p->x -= sign[2];
}

void	put_line(t_fdf *fdf, t_point p0, t_point p1)
{
	int A;
	int B;
	int sign[3];
	int f;
	float length;
	t_point p;

	A = p1.y - p0.y;
	B = p0.x - p1.x;
	sign[0] = (abs(A) > abs(B)) ? 1 : -1;
	sign[1] = (A < 0) ? -1 : 1;
	sign[2] = (B < 0) ? -1 : 1;
	f = 0;
	put_pixel(fdf, p0, p0.color);
	p = p0;
	length = sqrt(pow((p0.x - p1.x), 2) + pow((p0.y - p1.y), 2));
	while (p.x != p1.x || p.y != p1.y)
	{
		action(&p, sign, A, B, &f);
		put_pixel(fdf, p, get_color(p0, p1, sqrt(pow((p.x - p0.x), 2)
		+ pow((p.y - p0.y), 2)) / length));
	}
}

void	draw_map(t_fdf *fdf)
{
	int x;
	int y;

	y = 0;
	ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
	while (y < fdf->map->height)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x != fdf->map->width - 1)
				put_line(fdf, project(new_point_map(x, y, fdf->map), fdf),
						project(new_point_map(x + 1, y, fdf->map), fdf));
			if (y != fdf->map->height - 1)
				put_line(fdf, project(new_point_map(x, y, fdf->map), fdf),
						project(new_point_map(x, y + 1, fdf->map), fdf));
			x++;
		}
		y++;
	}
	put_rectangles(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	show_text(fdf);
}