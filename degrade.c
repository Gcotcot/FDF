/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   degrade.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:55:05 by gcot              #+#    #+#             */
/*   Updated: 2023/04/28 12:55:12 by gcot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	nb_pixel(int *pos, int nb)
{
	float	e;
	float	r;

	e = ((float)pos[3] - (float)pos[1]) / ((float)pos[2] - (float)pos[0]);
	r = e;
	if (e < 0)
		e = -e;
	while (pos[0] < pos[2] || pos[1] != pos[3])
	{
		if (0.5 < r || pos[0] == pos[2])
		{
			r--;
			if (pos[1] < pos[3])
				pos[1]++;
			else
				pos[1]--;
		}
		else
		{
			r = r + e;
			pos[0]++;
		}
		nb++;
	}
	return (nb);
}

int	*split_color(int p1, int p2)
{
	int	*color;

	color = malloc(sizeof(*color) * 6);
	color[2] = p1 % 256;
	p1 = (p1 - p1 % 256) / 256;
	color[1] = p1 % 256;
	p1 = (p1 - p1 % 256) / 256;
	color[0] = p1 % 256;
	color[5] = p2 % 256;
	p2 = (p2 - p2 % 256) / 256;
	color[4] = p2 % 256;
	p2 = (p2 - p2 % 256) / 256;
	color[3] = p2 % 256;
	return (color);
}

int	*set_pos(t_point *p1, t_point *p2)
{
	int	*pos;

	pos = malloc(sizeof(*pos) * 4);
	pos[0] = p1->x;
	pos[1] = p1->y;
	pos[2] = p2->x;
	pos[3] = p2->y;
	return (pos);
}

void	modify_color(int *color, int i, int dist)
{
	if (color[i] < color[i + 3])
		color[i] += (color[i + 3] - color[i]) / dist;
	else if (color[i] > color[i + 3])
		color[i] -= (color[i] - color[i + 3]) / dist;
	if (color[i] > 255)
		color[i] = 255;
}

int	degrade(t_point *p1, t_point *p2)
{
	int	dist;
	int	*color;
	int	*pos;
	int	i;

	if (p1->color == p2->color)
		return (p1->color);
	pos = set_pos(p1, p2);
	dist = nb_pixel(pos, 1);
	color = split_color(p1->color, p2->color);
	i = 0;
	while (i < 3)
	{
		modify_color(color, i, dist);
		i++;
	}
	p1->color = color[0] * 256 * 256 + color[1] * 256 + color[2];
	free(color);
	free(pos);
	return (p1->color);
}
