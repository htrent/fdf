/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2019/12/26 18:22:24 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_puterr(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int		min(int a, int b)
{
	return ((a > b) ? b : a);
}

/*void	free_all(t_point **map, t_point point, t_fdf *fdf, t_stack *coord)
{
	int i;

	i = 0;
	while (i < point.y)
		free(map[i++]);
	free(map);
	free(fdf->mlx);
	free(fdf->win);
	free(fdf->img);
	free(fdf);
	free_stack(coord);
}*/