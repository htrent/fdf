/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2019/12/26 18:46:41 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argc, char **argv)
{
	t_fdf	*fdf;
	int		fd;
	t_stack *coord;
	t_point p;
	t_point **map;

	if (argc != 2)
	{
		ft_puterr("Usage: ./fdf file_with_map\n");
		return (0);
	}

	if ((fd = open(argv[1], O_RDONLY)) <= 0)
	{
		ft_puterr("Wrong filename...\nGive me existed file\n._.\n");
		return (0);
	}
	p = read_to_stack(fd, &coord);
	if (!(map = stack_to_map(coord, p.x, p.y)))
	{
		write(1, "There are some problems with map...\n", 36);
		return (0);
	}
	free_stack(coord);
	//print_map(map, x, y);
	fdf = fdf_init(map, p.x, p.y);
	draw_map(fdf);
	mlx_hooks(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}




//x = (prev_x - prev_y) * cos(M_PI/6);
//y = (prev_x + prev_y) * sin(M_PI_6) - z;

//CHECKFORZOOM
//printf("ZOOM:\n%f\n%f\n",(((map[y - 1][x - 1].x + map[y - 1][x - 1].y) * sin(M_PI / 6) - map[y - 1][x - 1].z) - ((map[0][0].x + map[0][0].y) * sin(M_PI / 6) - map[0][0].z)) * fdf->zoom,
//	   (((map[y - 1][0].x - map[y - 1][0].y) * cos(M_PI / 6)) - ((map[0][x - 1].x - map[0][x - 1].y) * cos(M_PI / 6))) * fdf->zoom);
//if (fabs(((map[y - 1][x - 1].x + map[y - 1][x - 1].y) * sin(M_PI / 6) - map[y - 1][x - 1].z) - ((map[0][0].x + map[0][0].y) * sin(M_PI / 6) - map[0][0].z)) * fdf->zoom > HEIGHT && printf("CHANGED ZOOM Y\n"))
//	fdf->zoom = fabs(HEIGHT / (((map[0][0].x + map[0][0].y) * sin(M_PI / 6) - map[0][0].z) - ((map[y - 1][x - 1].x + map[y - 1][x - 1].y) * sin(M_PI / 6) - map[y - 1][x - 1].z)));
//if (fabs(((map[y - 1][0].x - map[y - 1][0].y) * cos(M_PI / 6)) - ((map[0][x - 1].x - map[0][x - 1].y) * cos(M_PI / 6))) * fdf->zoom > WIDTH && printf("CHANGED ZOOM X\n"))
//	fdf->zoom = fabs(WIDTH / (((map[y - 1][0].x - map[y - 1][0].y) * cos(M_PI / 6)) - ((map[0][x - 1].x - map[0][x - 1].y) * cos(M_PI / 6))));
//if (fabs(((fdf->z_max.x + fdf->z_max.y) * sin(M_PI / 6) - fdf->z_max.z) - ((fdf->z_min.x + fdf->z_min.y) * sin(M_PI / 6) - fdf->z_min.z)) * fdf->zoom > HEIGHT && printf("CHANGED ZOOM MAX\n"))
//	fdf->zoom = fabs(HEIGHT / fabs(((fdf->z_max.x + fdf->z_max.y) * sin(M_PI / 6) - fdf->z_max.z) - ((fdf->z_min.x + fdf->z_min.y) * sin(M_PI / 6) - fdf->z_min.z))) - 1;

//PLACE IN CENTER
//fdf->offset_y = HEIGHT / 2 - ((map[fdf->height / 2][fdf->width / 2].x + map[fdf->height / 2][fdf->width / 2].y) * sin(M_PI / 6)/* - map[fdf->height / 2][fdf->width / 2].z*/) * fdf->zoom;
//fdf->offset_x = WIDTH / 2 - (map[fdf->height / 2][fdf->width / 2].x - map[fdf->height / 2][fdf->width / 2].y) * cos(M_PI / 6) * fdf->zoom;
//printf("offsets: %d %d %f %f\n", fdf->offset_y, fdf->offset_x, ((map[fdf->height / 2][fdf->width / 2].x + map[fdf->height / 2][fdf->width / 2].y) * sin(M_PI / 6) - map[fdf->height / 2][fdf->width / 2].z) * fdf->zoom, (map[fdf->height / 2][fdf->width / 2].x - map[fdf->height / 2][fdf->width / 2].y) * cos(M_PI / 6) * fdf->zoom);




/*///CHECKFOROFFSET
if ((((map[0][0].x + map[0][0].y) * sin(M_PI / 6) - map[0][0].z) * fdf->zoom + fdf->offset_y < 0) && printf("OFFSET_Y1\n"))
	fdf->offset_y = HEIGHT - ((map[0][0].x + map[0][0].y) * sin(M_PI / 6) - map[0][0].z) * fdf->zoom;
if (((map[y - 1][x - 1].x + map[y - 1][x - 1].y) * sin(M_PI / 6) - map[y - 1][x - 1].z) * fdf->zoom + fdf->offset_y > HEIGHT && printf("OFFSET_Y2\n"))
	fdf->offset_y = HEIGHT - ((map[y - 1][x - 1].x + map[y - 1][x - 1].y) * sin(M_PI / 6) - map[y - 1][x - 1].z) * fdf->zoom;
if ((map[y - 1][0].x - map[y - 1][0].y) * cos(M_PI / 6) * fdf->zoom + fdf->offset_x < 0 && printf("OFFSET_X1\n"))
	fdf->offset_x = -1 * (map[y - 1][0].x - map[y - 1][0].y) * cos(M_PI / 6) * fdf->zoom;
if ((map[0][x - 1].x - map[0][x - 1].y) * cos(M_PI / 6) * fdf->zoom + fdf->offset_x > WIDTH && printf("OFFSET_X2\n"))
	fdf->offset_x = WIDTH + -1 * (map[0][x - 1].x - map[0][x - 1].y) * cos(M_PI / 6) * fdf->zoom;*/

/*
///###_______DRAW_NET_____
int corner = 50; // instead of 50 place left upper corner of net
int width = 10; //Here cell is square with 50 pixels width
int height = 10;
int square = 50; //Width of cell

///______END_OF_DRAW_____

///_______ISO_DRAW_NET_______

int offset_x = WIDTH / 2; // instead of 50 place left upper corner of net
int offset_y = HEIGHT / 2;
int x = 10; //Here cell is square with 50 pixels width
int y = 10;
int a = 50; //Width of cell
i = 0;
while (i <= y)
{
	put_line(fdf,
			offset_x + a * cos(M_PI/6) * i,
			offset_y + a * sin(M_PI/6) * i,
			offset_x + a * cos(M_PI/6) * i - x * a * cos(M_PI/6),
			offset_y + a * sin(M_PI/6) * i + x * a * sin(M_PI/6),
			DEF_CLR);
	i++;
}
put_line(fdf, WIDTH / 2, 0, WIDTH / 2, HEIGHT / 2, 0x00FF00);									//   AXIS
put_line(fdf, WIDTH / 2, HEIGHT / 2, 0, HEIGHT / 2 + (WIDTH / 2) * sin(M_PI/6), 0x00FF00);		//	 OF ISOMETRIC
put_line(fdf, WIDTH / 2, HEIGHT / 2, WIDTH, HEIGHT / 2 + (WIDTH / 2) * sin(M_PI/6), 0x00FF00);	//	 PROJECTION
i = 0;
while (i <= x)
{
	put_line(fdf,
			offset_x - a * cos(M_PI/6) * i,
			offset_y + a * sin(M_PI/6) * i,
			offset_x - a * cos(M_PI/6) * i + y * a * cos(M_PI/6),
			offset_y + a * sin(M_PI/6) * i + y * a * sin(M_PI/6),
			DEF_CLR);
	i++;
}
///______END_OF_ISO_DRAW_____

mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
//while (i < HEIGHT * WIDTH)
//{
//	image[i] = (i % WIDTH < MENU_WIDTH) ? MENU_BACKGROUND : BACKGROUND;
//	i++;
//}
*/