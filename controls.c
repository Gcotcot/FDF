/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:08:56 by gcot              #+#    #+#             */
/*   Updated: 2023/04/28 10:08:59 by gcot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move(float i, int axe, t_controls *c, t_map *m)
{
	if (axe == 'x')
		c->x += (int)i;
	else if (axe == 'y')
		c->y += (int)i;
	else if (axe == 'g' && (c->zoom + i > 1))
		c->zoom += i;
	else if (axe == 'c' && (c->cut + i >= 0) && c->cut + i < m->nb_l)
		c->cut += i;
}

void	reset_pos(t_controls *c)
{
	c->zoom = 3;
	c->cut = 0;
	c->y = 0;
	c->x = 0;
}

int	close_win(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	return (0);
}

void	handle_keypress2(int keysym, t_data *data)
{
	if (keysym == 65429)
		move(1, 'c', &data->controls, &data->m);
	else if (keysym == 65434)
		move(-1, 'c', &data->controls, &data->m);
	else if (keysym == 65438)
		reset_pos(&data->controls);
}

int	handle_keypress(int keysym, t_data *data)
{
	float	grad;
	float	zoom;

	grad = 4;
	zoom = 1;
	if (keysym == 65307)
		return (close_win(data));
	else if (keysym == 65361)
		move(grad, 'x', &data->controls, &data->m);
	else if (keysym == 65363)
		move(-grad, 'x', &data->controls, &data->m);
	else if (keysym == 65362)
		move(grad, 'y', &data->controls, &data->m);
	else if (keysym == 65364)
		move(-grad, 'y', &data->controls, &data->m);
	else if (keysym == 65451)
		move(zoom, 'g', &data->controls, &data->m);
	else if (keysym == 65453)
		move(-zoom, 'g', &data->controls, &data->m);
	else
		handle_keypress2(keysym, data);
	return (0);
}
