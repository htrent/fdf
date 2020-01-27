/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 19:53:58 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	show_text(t_fdf *fdf)
{
	if ((fdf->mouse_pos.x < MENU_WIDTH && fdf->mouse_pos.y < MENU_HEIGHT &&
		fdf->menu == NOT_PERMANENT) || fdf->menu == PERMANENT)
		show_menu(fdf);
	else
		show_hint(fdf);
	show_program(fdf);
}

void	show_hint(t_fdf *fdf)
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

void	show_program(t_fdf *fdf)
{
	mlx_string_put(fdf->mlx, fdf->win, 10, 5, 0x00ff00, "Map: ");
	mlx_string_put(fdf->mlx, fdf->win, 55, 5, 0x4B0082, fdf->map_name);
}

void	show_menu(t_fdf *fdf)
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
	mlx_string_put(fdf->mlx, fdf->win, 10, HEIGHT_OF_HEADER + 200, MENU_CLR,
			"Use NUM_PAD/left_click_mouse to rotate");
}
