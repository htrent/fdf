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

void		show_text(t_fdf *fdf)
{
	if ((fdf->mouse_pos.x < MENU_WIDTH && fdf->mouse_pos.y < MENU_HEIGHT &&
		fdf->menu == NOT_PERMANENT) || fdf->menu == PERMANENT)
		show_menu(fdf);
	else
		show_hint(fdf);
	show_program(fdf);
}

void		show_hint(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx, fdf->win, 50, 80, 0x222222,
			"PLACE YOUR MOUSE");
	mlx_string_put(fdf->mlx, fdf->win, 100, 130, 0x222222,
			"HERE");
	mlx_string_put(fdf->mlx, fdf->win, 80, 180, 0x222222,
			"FOR MENU");
	mlx_string_put(fdf->mlx, fdf->win, 50, 230, 0x222222,
			"(or press M key)");
}

void		show_program(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx, fdf->win, 10, 5, DARK_VIOLET, "Map: ");
	mlx_string_put(fdf->mlx, fdf->win, 55, 5, DARK_BLUE, fdf->map_name);
}

static void	show_menu2(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx, fdf->win, 10, HEIGHT_OF_HEADER + 200, MENU_CLR,
			"Use NUM_PAD/left_click_mouse to rotate");
	mlx_string_put(fdf->mlx, fdf->win, 10, HEIGHT_OF_HEADER + 230, MENU_CLR,
			"\"E\" for Dark color scheme");
	mlx_string_put(fdf->mlx, fdf->win, 10, HEIGHT_OF_HEADER + 260, MENU_CLR,
			"\"D\" for Default color scheme");
	mlx_string_put(fdf->mlx, fdf->win, 10, HEIGHT_OF_HEADER + 290, MENU_CLR,
			"\"F\" for Test color scheme");
	mlx_string_put(fdf->mlx, fdf->win, 10, HEIGHT_OF_HEADER + 320, MENU_CLR,
			"\"R\" for Rainbow color scheme");
	mlx_string_put(fdf->mlx, fdf->win, 10, HEIGHT_OF_HEADER + 350, MENU_CLR,
			"\"W\" for random color scheme");
}

void		show_menu(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx, fdf->win, 10, HEIGHT_OF_HEADER + 20, MENU_CLR,
			"\"+\" or \"-\" to zoom");
	mlx_string_put(fdf->mlx, fdf->win, 10, HEIGHT_OF_HEADER + 50, MENU_CLR,
			"\"T\" to not/transparent menu");
	mlx_string_put(fdf->mlx, fdf->win, 10, HEIGHT_OF_HEADER + 80, MENU_CLR,
			"\"I\" for ISO projection ");
	mlx_string_put(fdf->mlx, fdf->win, 10, HEIGHT_OF_HEADER + 110, MENU_CLR,
			"\"P\" for PARALLEL projection");
	mlx_string_put(fdf->mlx, fdf->win, 10, HEIGHT_OF_HEADER + 140, MENU_CLR,
			"Use arrows/right_click_mouse to move");
	mlx_string_put(fdf->mlx, fdf->win, 10, HEIGHT_OF_HEADER + 170, MENU_CLR,
			"Use \">\" or \"<\" to change altitude");
	show_menu2(fdf);
}
