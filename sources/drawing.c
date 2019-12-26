/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2019/12/26 18:22:38 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	put_pixel(t_fdf *fdf, t_point p, int color)
{
	int		i;

	//printf("x: %d, y: %d\n", p.x, p.y);
	if (p.x >= 0 && p.x < WIDTH && p.y >= 0 && p.y < HEIGHT)
	{
		i = (p.x * fdf->bits_per_pixel / 8) + (p.y * fdf->size_line);
		fdf->data_addr[i] = color;
		fdf->data_addr[++i] = color >> 8;
		fdf->data_addr[++i] = color >> 16;
	}
}

void	put_line(t_fdf *fdf, t_point p0, t_point p1)
{

	int A;
	int B;
	int sign;
	int signa;
	int signb;
	int f;
	float length;
	t_point p;

	A = p1.y - p0.y;
	B = p0.x - p1.x;
	sign = (abs(A) > abs(B)) ? 1 : -1;
	signa = (A < 0) ? -1 : 1;
	signb = (B < 0) ? -1 : 1;
	f = 0;
	put_pixel(fdf, p0, p0.color);
	p.x = p0.x;
	p.y = p0.y;
	length = sqrt(pow((p0.x - p1.x), 2) + pow((p0.y - p1.y), 2));
	while (p.x != p1.x || p.y != p1.y)
	{
		f += (sign == 1) ? B * signb : A * signa;
		if (f > 0)
		{
			f -= (sign == 1) ? A * signa : B * signb;
			if (sign == 1)
				p.x -= signb;
			else
				p.y += signa;
		}
		if (sign == 1)
			p.y += signa;
		else
			p.x -= signb;
		//printf("percent:%f r:%x g:%x b :%x color:%x\n", percent, r, g, b, color);
		put_pixel(fdf, p, get_color(p0, p1, sqrt(pow((p.x - p0.x), 2) + pow((p.y - p0.y), 2)) / length)); //percent = sqrt(pow((p.x - p0.x), 2) + pow((p.y - p0.y), 2)) / length
	}
}

void	draw_map(t_fdf *fdf)
{
	int i;
	int j;

	i = 0;
	ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (j < fdf->width - 1)
				put_line(fdf, project(fdf->map[i][j], fdf), project(fdf->map[i][j + 1], fdf));
			if (i < fdf->height - 1)
				put_line(fdf, project(fdf->map[i][j], fdf), project(fdf->map[i + 1][j], fdf));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}