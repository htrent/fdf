/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/28 12:57:59 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	test_color1(double percent)
{
	if (percent <= 0.5715)
		return (A_VIOLET);
	if (percent <= 0.6419)
		return (B_VIOLET);
	if (percent <= 0.7143)
		return (C_VIOLET);
	if (percent <= 0.7858)
		return (D_VIOLET);
	if (percent <= 0.8572)
		return (E_VIOLET);
	if (percent <= 0.9286)
		return (F_VIOLET);
	return (WHITE);
}

int			test_color(double percent)
{
	if (percent <= 0.0715)
		return (BLACK);
	if (percent <= 0.1429)
		return (F_BLUE);
	if (percent <= 0.2142)
		return (E_BLUE);
	if (percent <= 0.2858)
		return (D_BLUE);
	if (percent <= 0.3572)
		return (C_BLUE);
	if (percent <= 0.4286)
		return (B_BLUE);
	if (percent <= 0.5001)
		return (A_BLUE);
	return (test_color1(percent));
}

int			default_color(double percent)
{
	if (percent <= 0.3334)
		return (DEF_CLR);
	if (percent <= 0.6667)
		return (0x00ff00);
	return (0xff0000);
}

int			rainbow_color(double percent)
{
	if (percent <= 0.1429)
		return (VIOLET);
	if (percent <= 0.2858)
		return (BLUE);
	if (percent <= 0.4286)
		return (LIGHT_BLUE);
	if (percent <= 0.5715)
		return (GREEN);
	if (percent <= 0.7143)
		return (YELLOW);
	if (percent <= 0.8572)
		return (ORANGE);
	return (RED);
}

int			darkmode_color(double percent)
{
	if (percent <= 0.2501)
		return (DARK_TURQUOISE);
	if (percent <= 0.5001)
		return (PRIMARY_VIOLET);
	if (percent <= 0.7501)
		return (DARK_VIOLET);
	return (DARK_BLUE);
}
