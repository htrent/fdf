/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2019/12/06 16:07:56 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

# define DEF_CLR 0xff7f50//0x0099EE//////0x6f00ff

# define KEY_ESC 53
# define KEY_1_UP 18
# define KEY_2_UP 19
# define KEY_3_UP 20
# define KEY_4_UP 21
# define KEY_5_UP 23
# define KEY_6_UP 22
# define KEY_7_UP 26
# define KEY_8_UP 28
# define KEY_9_UP 25
# define KEY_0_UP 29
# define KEY_1_PAD 83
# define KEY_2_PAD 84
# define KEY_3_PAD 85
# define KEY_4_PAD 86
# define KEY_5_PAD 87
# define KEY_6_PAD 88
# define KEY_7_PAD 89
# define KEY_8_PAD 91
# define KEY_9_PAD 92
# define KEY_0_PAD 82
# define KEY_SPACE 49
# define KEY_RIGHT 124
# define KEY_LEFT  123
# define KEY_UP    126
# define KEY_DOWN  125
# define KEY_MINUS 27
# define KEY_PLUS  24


# define WIDTH 1400
# define HEIGHT 1000
# define MENU_WIDTH		250
# define BACKGROUND			0x222222
# define MENU_BACKGROUND	0x1E1E1E

typedef struct	s_stack
{
	int				z;
	int				color;
	struct s_stack	*next;

}				t_stack;

typedef	struct	s_point
{
	int 			x;
	int 			y;
	int 			z;
	int 			color;
}				t_point;

typedef struct	s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char 	*data_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		offset_x;
	int		offset_y;
	int		zoom;
	t_point	**map;
	int z_max;
	int z_min;
	int x;
	int y;
}				t_fdf;



int		min(int a, int b)
{
	return ((a > b) ? b : a);
}

t_stack		*new_node(int z, int color)
{
	t_stack 	*node;
	if (!(node = (t_stack *)malloc(sizeof(t_stack))))
		return (NULL);
	node->z = z;
	node->color = color;
	node->next = NULL;
	return (node);
}

void	push(t_stack **stack, t_stack *node)
{
	if (!stack)
		return ;
	if (!*stack)
		*stack = node;
	else
	{
		node->next = *stack;
		*stack = node;
	}
}

void	free_stack(t_stack *stack)
{
	t_stack *to_del;

	while(stack)
	{
		to_del = stack;
		stack = stack->next;
		free(to_del);
	}
}

void	print_stack(t_stack *stack)
{
	if (!stack)
		return ;
	while (stack)
	{
		ft_putstr("z: ");
		ft_putnbr(stack->z);
		ft_putchar(' ');
		ft_putnbr(stack->color);
		ft_putchar('\n');
		stack = stack->next;
	}
}


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
	int z_max;
	int z_min;

	z_max = fdf->map[0][0].z;
	z_min = fdf->map[0][0].z;
	i = 0;
	while (i < fdf->y)
	{
		j = 0;
		while (j < fdf->x)
		{
			if (fdf->map[i][j].z > z_max)
				z_max = fdf->map[i][j].z;
			if (fdf->map[i][j].z < z_min)
				z_min = fdf->map[i][j].z;
			j++;
		}
		i++;
	}
	fdf->z_min = z_min;
	fdf->z_max = z_max;
}

int 	get_defcl(float percent)
{
	if (percent <= 0.3333)
		return (DEF_CLR);
	if (percent <= 0.6666)
		return (0x960018);
	return (0x960018);
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
	deltaz = fdf->z_max - fdf->z_min;
	while (i < fdf->y)
	{
		j = 0;
		while (j < fdf->x)
		{
			fdf->map[i][j].color = get_defcl(fdf->map[i][j].z / deltaz);
			j++;
		}
		i++;
	}
}

t_fdf	*fdf_init(t_point **map, int x, int y)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	fdf->offset_x = WIDTH / 2;
	fdf->offset_y = HEIGHT / 2;
	fdf->zoom = 40;
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel), &(fdf->size_line), &(fdf->endian));
	ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
	fdf->map = map;
	fdf->x = x;
	fdf->y = y;
	init_max_min_z(fdf);
	init_map_color(fdf);
	return (fdf);
}

t_point	iso_projection(t_point p, t_fdf *fdf)
{
	int prev_x;
	int prev_y;

	prev_x = p.x;
	prev_y = p.y;
	p.x = fdf->offset_x + ((prev_x - prev_y) * cos(M_PI / 6)) * fdf->zoom;			//x = (prev_x - prev_y) * cos(M_PI/6);
	p.y = fdf->offset_y + ((prev_x + prev_y) * sin(M_PI / 6) - p.z) * fdf->zoom;	//y = (prev_x + prev_y) * sin(M_PI_6) - z;
	p.color += 10 * p.z;
	return (p);
}

void	draw_map(t_fdf *fdf)
{
	int i;
	int j;

	ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
	i = 0;
	while (i < fdf->y)
	{
		j = 0;
		while (j < fdf->x)
		{
			if (j < fdf->x - 1)
				put_line(fdf, iso_projection(fdf->map[i][j], fdf), iso_projection(fdf->map[i][j + 1], fdf));
			if (i < fdf->y - 1)
				put_line(fdf, iso_projection(fdf->map[i][j], fdf), iso_projection(fdf->map[i + 1][j], fdf));
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
	if (keycode == KEY_UP || keycode == KEY_8_PAD)
		fdf->offset_y -= 5;
	if (keycode == KEY_DOWN || keycode == KEY_2_PAD)
		fdf->offset_y += 5;
	if (keycode == KEY_LEFT || keycode == KEY_4_PAD)
		fdf->offset_x -= 5;
	if (keycode == KEY_RIGHT || keycode == KEY_6_PAD)
		fdf->offset_x += 5;
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

	///#
	///#____READ_FROM_FILE____
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
		write(1, "I need a file:((((\n", 19);
		return (0);
	}

	if ((fd = open(argv[1], O_RDONLY)) <= 0)
	{
		write(1, "Please, give me existed file!!!\n", 32);
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
		//		else
		//			color = ft_atoi_base(split_coord_color[1], 16);							///WRITE_ATOI_BASE!!!!!!
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

	print_map(map, x, y);
	///#____END_READ_______
	///#

	fdf = fdf_init(map, x, y);

	///PLACE IN CENTER
	fdf->offset_y += HEIGHT / 2 - fabs(((map[y / 2][x / 2].x + map[y / 2][x / 2].y) * sin(M_PI / 6) - map[y / 2][x / 2].z) * fdf->zoom + fdf->offset_y);
	fdf->offset_x += WIDTH / 2 - fabs((map[y / 2][x / 2].x - map[y / 2][x / 2].y) * cos(M_PI / 6) * fdf->zoom + fdf->offset_x);

	///CHECKFORZOOM
	printf("ZOOM:\n%f\n%f\n",(((map[y - 1][x - 1].x + map[y - 1][x - 1].y) * sin(M_PI / 6) - map[y - 1][x - 1].z) - ((map[0][0].x + map[0][0].y) * sin(M_PI / 6) - map[0][0].z)) * fdf->zoom,
		   (((map[y - 1][0].x - map[y - 1][0].y) * cos(M_PI / 6)) - ((map[0][x - 1].x - map[0][x - 1].y) * cos(M_PI / 6))) * fdf->zoom);
	if ((((map[y - 1][x - 1].x + map[y - 1][x - 1].y) * sin(M_PI / 6) - map[y - 1][x - 1].z) - ((map[0][0].x + map[0][0].y) * sin(M_PI / 6) - map[0][0].z)) * fdf->zoom > HEIGHT)
		fdf->zoom = HEIGHT / (((map[0][0].x + map[0][0].y) * sin(M_PI / 6) - map[0][0].z) - ((map[y - 1][x - 1].x + map[y - 1][x - 1].y) * sin(M_PI / 6) - map[y - 1][x - 1].z));
	if ((((map[y - 1][0].x - map[y - 1][0].y) * cos(M_PI / 6)) - ((map[0][x - 1].x - map[0][x - 1].y) * cos(M_PI / 6))) * fdf->zoom > WIDTH)
		fdf->zoom = WIDTH / (((map[y - 1][0].x - map[y - 1][0].y) * cos(M_PI / 6)) - ((map[0][x - 1].x - map[0][x - 1].y) * cos(M_PI / 6)));

	///CHECKFOROFFSET
	if (((map[0][0].x + map[0][0].y) * sin(M_PI / 6) - map[0][0].z) * fdf->zoom + fdf->offset_y < 0 && printf("OFFSET_Y1\n"))
		fdf->offset_y = HEIGHT - ((map[0][0].x + map[0][0].y) * sin(M_PI / 6) - map[0][0].z) * fdf->zoom;
	if (((map[y - 1][x - 1].x + map[y - 1][x - 1].y) * sin(M_PI / 6) - map[y - 1][x - 1].z) * fdf->zoom + fdf->offset_y > HEIGHT && printf("OFFSET_Y2\n"))
		fdf->offset_y = HEIGHT - ((map[y - 1][x - 1].x + map[y - 1][x - 1].y) * sin(M_PI / 6) - map[y - 1][x - 1].z) * fdf->zoom;
	if ((map[y - 1][0].x - map[y - 1][0].y) * cos(M_PI / 6) * fdf->zoom + fdf->offset_x < 0 && printf("OFFSET_X1\n"))
		fdf->offset_x = -1 * (map[y - 1][0].x - map[y - 1][0].y) * cos(M_PI / 6) * fdf->zoom;
	if ((map[0][x - 1].x - map[0][x - 1].y) * cos(M_PI / 6) * fdf->zoom + fdf->offset_x > WIDTH && printf("OFFSET_X2\n"))
		fdf->offset_x = WIDTH + -1 * (map[0][x - 1].x - map[0][x - 1].y) * cos(M_PI / 6) * fdf->zoom;


	///______________________FOR ME:
	/// Check offset (for max_z and min_z)!!!!!!!!1
	/// Add rotation. Add parallel projection. 
	/// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



	///##
	///##____TRY_TO_DRAW____
	draw_map(fdf);

	///##____END_OF_TRY_____
	///##

	mlx_hook(fdf->win, 17, 0, exit_program, fdf);
	mlx_hook(fdf->win, 2, 0, deal_key, fdf);
	mlx_loop(fdf->mlx);

	free(fdf);
	i = 0;
	while (i < y)
		free(map[i++]);
	free(map);
	free_stack(coord);

	return (0);
}















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