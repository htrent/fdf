/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2019/12/24 18:52:28 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int get_light(int start, int end, float percentage)
{
	return ((1 - percentage) * start + percentage * end);
}

int get_color(t_point p0, t_point p1, int percent)
{
	int r;
	int g;
	int b;

	r = get_light((p0.color >> 16) & 0xFF, (p1.color >> 16) & 0xFF, percent);
	g = get_light((p0.color >> 8) & 0xFF, (p1.color >> 8) & 0xFF, percent);
	b = get_light(p0.color & 0xFF, p1.color & 0xFF, percent);
	return ((r << 16) + (g << 8) + b);
}

void	print_map(t_point **map, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			printf("%2d ", map[i][j].z);
			j++;
		}
		printf("\n");
		i++;
	}
}

t_point	**stack_to_map(t_stack *coord, int x, int y)
{
	t_stack *temp;
	t_point **map;
	int 	i;
	int 	j;

	temp = coord;
	if (!(map = (t_point **)malloc(sizeof(t_point *) * y)))
		return (NULL);
	i = 0;
	while (i < y)
		if (!(map[i++] = (t_point *)malloc(sizeof(t_point) * x)))
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return (NULL);
		}
	i = y - 1;
	while (i >= 0)
	{
		j = x - 1;
		while (j >= 0)
		{
			map[i][j].x = j;
			map[i][j].y = i;
			map[i][j].z = temp->z;
			map[i][j].color = temp->color;
			temp = temp->next;
			j--;
		}
		i--;
	}
	return (map);
}

void init_max_min_z(t_fdf *fdf)
{
	int i;
	int j;

	fdf->z_max.z = fdf->map[0][0].z;
	fdf->z_min.z = fdf->map[0][0].z;
	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (fdf->map[i][j].z > fdf->z_max.z)
				fdf->z_max = fdf->map[i][j];
			if (fdf->map[i][j].z < fdf->z_min.z)
				fdf->z_min = fdf->map[i][j];
			j++;
		}
		i++;
	}
}

int 	get_defcl(float percent)
{
	if (percent <= 0.3334)
		return (DEF_CLR);
	if (percent <= 0.6667)
		return (DEF_CLR);
	return (0xff0000);
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
}

void	init_map_color(t_fdf *fdf)
{
	float deltaz;
	int i;
	int j;

	i = 0;
	deltaz = fdf->z_max.z - fdf->z_min.z;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			fdf->map[i][j].color = get_defcl(fdf->map[i][j].z / deltaz);
			j++;
		}
		i++;
	}
	fdf->map[fdf->height / 2][fdf->width / 2].color = 0xff0000;
}

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
	p->x = (prev_x - prev_y) * cos(M_PI / 6);			//x = (prev_x - prev_y) * cos(M_PI/6);
	p->y = (prev_x + prev_y) * sin(M_PI / 6) - p->z;	//y = (prev_x + prev_y) * sin(M_PI_6) - z;
}

t_point		project(t_point p, t_fdf *fdf)
{
	p.x *= fdf->zoom;
	p.y *= fdf->zoom;
	p.z *= fdf->zoom / fdf->z_high;
	p.x -= (fdf->width * fdf->zoom) / 2;
	p.y -= (fdf->height * fdf->zoom) / 2;
	rotate_x(&p.y, &p.z, fdf->alpha);
	rotate_y(&p.x, &p.z, fdf->beta);
	rotate_z(&p.x, &p.y, fdf->gamma);
	if (fdf->projection == ISO)
		iso_projection(&p);
	p.x += (WIDTH - MENU_WIDTH) / 2 + fdf->offset_x + MENU_WIDTH;
	p.y += (HEIGHT + fdf->height * fdf->zoom) / 2 + fdf->offset_y;
	return (p);
}

t_fdf	*fdf_init(t_point **map, int x, int y)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	fdf->offset_x = 0;
	fdf->offset_y = 0;
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel), &(fdf->size_line), &(fdf->endian));
	ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
	fdf->map = map;
	fdf->width = x;
	fdf->height = y;
	init_max_min_z(fdf);
	fdf->alpha = 0;
	fdf->beta = 0;
	fdf->gamma = 0;
	fdf->projection = 0;
	fdf->z_high = 1;
	fdf->zoom = min(WIDTH / (2 * fdf->width), HEIGHT / (2 * fdf->height));
	init_map_color(fdf);
	return (fdf);
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

int		deal_key(int keycode, t_fdf *fdf)
{
	//printf("key: %d\n", keycode);
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_MINUS)
		fdf->zoom--;
	if (keycode == KEY_PLUS)
		fdf->zoom++;
	if (keycode == KEY_UP)
		fdf->offset_y -= 10/*fdf->zoom / 5 + 1*/;
	if (keycode == KEY_DOWN)
		fdf->offset_y += 10/*fdf->zoom / 5 + 1*/;
	if (keycode == KEY_LEFT)
		fdf->offset_x -= 10/*fdf->zoom / 5 + 1*/;
	if (keycode == KEY_RIGHT)
		fdf->offset_x += 10/*fdf->zoom / 5 + 1*/;
	if (keycode == KEY_6_PAD)
		fdf->beta += 0.05;
	if (keycode == KEY_4_PAD)
		fdf->beta -= 0.05;
	if (keycode == KEY_8_PAD)
		fdf->alpha += 0.05;
	if (keycode == KEY_2_PAD)
		fdf->alpha -= 0.05;
	if (keycode == KEY_1_PAD || keycode == KEY_3_PAD)
		fdf->gamma += 0.05;
	if (keycode == KEY_7_PAD || keycode == KEY_9_PAD)
		fdf->gamma -= 0.05;
	if (keycode == KEY_I || keycode == KEY_P)
	{
		fdf->projection = (keycode == KEY_I) ? ISO : PARALLEL;
		fdf->alpha = 0;
		fdf->beta = 0;
		fdf->gamma = 0;
		fdf->offset_x = 0;
		fdf->offset_y = 0;
		fdf->zoom = 30;
		fdf->z_high = 1;
	}
	if (keycode == KEY_MORE && fdf->z_high > 0.1)
		fdf->z_high -= 0.1;
	if (keycode == KEY_LESS && fdf->z_high <= 20)
		fdf->z_high += 0.1;
	draw_map(fdf);
	return (keycode);
}

int		exit_program(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_fdf	*fdf;
	int i;

	int		fd;
	t_stack *coord;
	char	*line;
	char	**split_line;
	char	**split_coord_color;
	int 	color;
	int 	y;
	int		x;
	t_point 	**map;

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

	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if ((split_line = ft_strsplit(line, ' ')))
		{
			x = 0;
			while (*split_line)
			{
				split_coord_color = ft_strsplit(*split_line, ',');
				if (!split_coord_color[1])
					color = DEF_CLR;
//						else
//					color = ft_atoi_base(split_coord_color[1], 16);						///WRITE_ATOI_BASE!!!!!!
				push(&coord, new_node(ft_atoi(split_coord_color[0]), color));
				split_line++;
				x++;
			}
		}
		free(line);
		y++;
	}

	if (!(map = stack_to_map(coord, x, y))) ///MAP_INITIALIZATION
	{
		write(1, "There are some problems with map...\n", 36);
		return (0);
	}

	//print_map(map, x, y);

	fdf = fdf_init(map, x, y);

	///______________________FOR ME:
	/// Check offset (for max_z and min_z)!!!!!!!!1
	/// Add rotation. Add parallel projection.
	/// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	draw_map(fdf);
	mlx_hook(fdf->win, 17, 0, exit_program, fdf);
	mlx_hook(fdf->win, 2, 0, deal_key, fdf);
	mlx_loop(fdf->mlx);



	i = 0;
	while (i < y)
		free(map[i++]);
	free(map);

	free(fdf->mlx);
	free(fdf->win);
	free(fdf->img);
	free(fdf);
	free_stack(coord);

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