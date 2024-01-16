/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:08:25 by gcot              #+#    #+#             */
/*   Updated: 2023/04/05 12:31:04 by gcot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx/mlx.h"
# include "GNL/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>

typedef struct s_point
{
	int	x;
	int	y;
	int	color;
}	t_point;

typedef struct s_controls
{
	int		x;
	int		y;
	int		cut;
	float	zoom;
}	t_controls;

typedef struct s_list
{
	int		**int_m;
	int		nb_l;
	int		nb_c;
	int		**color_m;
	t_point	p1;
	t_point	p2;
}	t_map;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		height;
	int		width;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			cur_img;
	t_map		m;
	t_controls	controls;
}	t_data;

void	set_map(t_map *map, char *argv);
void	set_controls(t_controls *controls);
void	free_map(t_map *map);
void	img_pix_put(t_img *img, int x, int y, int color);
void	draw_line(t_data *data);
void	put_line(int *map, int *color, char *line);
void	size_win(int width, int height, t_img *img);
int		close_win(t_data *data);
int		handle_keypress(int keysym, t_data *data);
int		degrade(t_point *p1, t_point *p2);
int		convert_base(char *line, int i, int end);

#endif
