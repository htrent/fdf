/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htrent <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:09:49 by htrent            #+#    #+#             */
/*   Updated: 2020/01/27 19:10:33 by htrent           ###   ########.fr       */
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
# define KEY_T 17
# define KEY_MORE 47
# define KEY_LESS 43

# define WIDTH 1400
# define HEIGHT 1000
# define HEIGHT_OF_HEADER 30
# define MENU_WIDTH	400
# define MENU_HEIGHT 300
# define BACKGROUND			0x222222
# define MENU_BACKGROUND	0x222222
# define HEADER_COLOR 0x808080
# define MENU_CLR 0x0099EE
# define DEF_CLR 0x0099EE//0xff7f50//0x0099EE//////0x6f00ff

# define RED 0xff000
# define ORANGE 0xff4f00
# define YELLOW 0xf7ff00
# define GREEN 0x0bda51
# define LIGHT_BLUE 0x1e90ff
# define BLUE 0x0099EE
# define VIOLET 0x4d0092

# define ISO 0
# define PARALLEL 1

# define NOTPRESSED 0
# define PRESSED_LEFT 1
# define PRESSED_RIGHT 2

# define MOUSE_LEFT_CLICK 1
# define MOUSE_RIGHT_CLICK 2
# define MOUSE_MID_CLICK 3
# define MOUSE_SCROLL_DOWN 4
# define MOUSE_SCROLL_UP 5

# define NOT_TRANSPARENT 0
# define TRANSPARENT 1
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

typedef struct	s_cmap
{
	int			z;
	int 		color;
}				t_cmap;

typedef struct	s_map
{
	t_cmap		*coords;
	int 		width;
	int 		height;
	int 		z_max;
	int 		z_min;
}				t_map;

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
	t_map		*map;
	float		alpha;
	float		beta;
	float		gamma;
	float 		z_high;
	int 		mouse_status;
	t_point		mouse_pos;
	t_point 	mouse_prevpos;
	char		*map_name;
	int         menu;
}				t_fdf;

void		ft_puterr(char *str);
int			min(int a, int b);
t_stack		*new_node(int z, int color);
void		push(t_stack **stack, t_stack *node);
t_stack  	*pop(t_stack **stack);
void		free_stack(t_stack *stack);
void		print_stack(t_stack *stack);
void		put_pixel(t_fdf *fdf, t_point p, int color);
void		put_line(t_fdf *fdf, t_point p0, t_point p1);
int 		get_light(int start, int end, float percentage);
int 		get_color(t_point p0, t_point p1, float percent);
void		stack_to_map(t_stack **coord, t_map *map);
int 		get_defcl(int z, t_map *map);
void		rotate_x(int *y, int *z, double alpha);
void		rotate_y(int *x, int *z, double beta);
void		rotate_z(int *x, int *y, double gamma);
void		iso_projection(t_point *p);
t_point		project(t_point p, t_fdf *fdf);
t_map		*map_init(void);
t_fdf		*fdf_init(t_map *map);
void		draw_map(t_fdf *fdf);
int			deal_key(int keycode, t_fdf *fdf);
int			exit_program(void *param);
int			mouse_press(int button, int x, int y, t_fdf *fdf);
int			mouse_release(int button, int x, int y, t_fdf *fdf);
int			mouse_move(int x, int y, t_fdf *fdf);
void		mlx_hooks(t_fdf *fdf);
int			read_to_stack(int fd, t_stack **coord, t_map *map);
void		put_rectangle(t_fdf *fdf, t_point p, int width, int height);
void		put_transparent_rectangle(t_fdf *fdf, t_point p, int width, int height);
t_point 	new_point_map(int x, int y, t_map *map);
t_point		new_point(int x, int y, int color);
void		show_program(t_fdf *fdf);
void		show_menu(t_fdf *fdf);
void		put_rectangles(t_fdf *fdf);
int			ft_isnumber(char *str, int base);
void		error(char *s);
void		rotation(int keycode, t_fdf *fdf);
void		change_proj(int keycode, t_fdf *fdf);
void		zoom_and_move(int keycode, t_fdf *fdf);
#endif
