/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2019/12/24 18:54:15 by htrent           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
 * KEY DEFINES
 */

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
# define KEY_I 34
# define KEY_P 35
# define KEY_MORE 47
# define KEY_LESS 43

# define WIDTH 1400
# define HEIGHT 1000
# define MENU_WIDTH	0
# define BACKGROUND			0x222222
# define MENU_BACKGROUND	0x1E1E1E
# define DEF_CLR 0x0099EE//0xff7f50//0x0099EE//////0x6f00ff

# define ISO 0
# define PARALLEL 1

typedef struct		s_stack
{
	int				z;
	int				color;
	struct s_stack	*next;

}					t_stack;

typedef	struct	s_point
{
	int 		x;
	int 		y;
	int 		z;
	int 		color;
}				t_point;

typedef struct	s_fdf
{
	void		*mlx;
	void		*win;
	void		*img;
	char 		*data_addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			offset_x;
	int			offset_y;
	int			zoom;
	int 		projection;
	t_point		**map;
	t_point		z_max;
	t_point		z_min;
	float		alpha;
	float		beta;
	float		gamma;
	int 		width;
	int 		height;
	float 		z_high;
}				t_fdf;

void		ft_puterr(char *str);
int			min(int a, int b);
t_stack		*new_node(int z, int color);
void		push(t_stack **stack, t_stack *node);
void		free_stack(t_stack *stack);
void		print_stack(t_stack *stack);
void		put_pixel(t_fdf *fdf, t_point p, int color);
void		put_line(t_fdf *fdf, t_point p0, t_point p1);
int 		get_light(int start, int end, float percentage);
int 		get_color(t_point p0, t_point p1, int percent);
void		print_map(t_point **map, int x, int y);
t_point		**stack_to_map(t_stack *coord, int x, int y);
void 		init_max_min_z(t_fdf *fdf);
int 		get_defcl(float percent);
void		init_map_color(t_fdf *fdf);
void		rotate_x(int *y, int *z, double alpha);
void		rotate_y(int *x, int *z, double beta);
void		rotate_z(int *x, int *y, double gamma);
void		iso_projection(t_point *p);
t_point		project(t_point p, t_fdf *fdf);
t_fdf		*fdf_init(t_point **map, int x, int y);
void		draw_map(t_fdf *fdf);
int			deal_key(int keycode, t_fdf *fdf);
int			exit_program(void *param);

#endif
