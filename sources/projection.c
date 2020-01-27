/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 12:46:59 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(int *y, int *z, double alpha)
{
	int previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}


void	rotate_y(int *x, int *z, double beta)
{
	int previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}


void	rotate_z(int *x, int *y, double gamma)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

void	iso_projection(t_point *p)
{
	int prev_x;
	int prev_y;

	prev_x = p->x;
	prev_y = p->y;
	p->x = (prev_x - prev_y) * cos(M_PI / 6);
	p->y = (prev_x + prev_y) * sin(M_PI / 6) - p->z;
}

t_point		project(t_point p, t_fdf *fdf)
{
	p.x *= fdf->zoom;
	p.y *= fdf->zoom;
	p.z *= fdf->zoom / fdf->z_high;
	p.x -= (fdf->map->width * fdf->zoom) / 2;
	p.y -= (fdf->map->height * fdf->zoom) / 2;
	rotate_x(&p.y, &p.z, fdf->alpha);
	rotate_y(&p.x, &p.z, fdf->beta);
	rotate_z(&p.x, &p.y, fdf->gamma);
	if (fdf->projection == ISO)
		iso_projection(&p);
	p.x += (WIDTH - MENU_WIDTH) / 2 + fdf->offset_x + MENU_WIDTH;
	p.y += (HEIGHT + fdf->map->height * fdf->zoom) / 2 + fdf->offset_y;
	return (p);
}