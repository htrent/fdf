/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 17:59:25 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	t_fdf	*fdf;
	int		fd;
	t_stack	*coord;
	t_map	*map;

	if (argc != 2)
		error("Usage: ./fdf file_with_map\n");
	if ((fd = open(argv[1], O_RDONLY)) <= 0)
		error("Wrong filename...\nGive me existed file\n*_*\n");
	map = map_init();
	if (read_to_stack(fd, &coord, map) == -1)
		error("There are some problems with map...\n");
	fdf = fdf_init(map);
	stack_to_map(&coord, map);
	fdf->map_name = argv[1];
	draw_map(fdf);
	mlx_hooks(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
