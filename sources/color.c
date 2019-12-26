/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2019/12/26 19:07:49 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int get_light(int start, int end, float percentage)
{
	return ((1 - percentage) * start + percentage * end);
}

int get_color(t_point p0, t_point p1, float percent)
{
	int r;
	int g;
	int b;

	r = get_light((p0.color >> 16) & 0xFF, (p1.color >> 16) & 0xFF, percent);
	g = get_light((p0.color >> 8) & 0xFF, (p1.color >> 8) & 0xFF, percent);
	b = get_light(p0.color & 0xFF, p1.color & 0xFF, percent);
	return ((r << 16) + (g << 8) + b);
}

int 	get_defcl(float percent)
{
	if (percent <= 0.3334)
		return (DEF_CLR);
	if (percent <= 0.6667)
		return (0x00ff00);
	return (0xff0000);
}

/*	if (percent < 0.1428)
		return (0xff0000); //red
	if (percent < 0.2857)
		return (0xff4f00); //orange
	if (percent < 0.42857)
		return (0xf7ff00); //yellow
	if (percent < 0.57142)
		return (0x0bda51); //green
	if (percent < 0.7143)
		return (0x1e90ff); //light blue
	if (percent < 0.8571)
		return (DEF_CLR);  //blue
	return (0x4d0092);     //violet
 */