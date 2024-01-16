/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:14:20 by gcot              #+#    #+#             */
/*   Updated: 2023/04/07 16:14:36 by gcot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	join_point(t_point *p1, t_point *p2, t_img *img)
{
	float	e;
	float	r;

	e = ((float)p2->y - (float)p1->y) / ((float)p2->x - (float)p1->x);
	r = e;
	if (e < 0)
		e = -e;
	while (p1->x < p2->x || p1->y != p2->y)
	{
		img_pix_put(img, p1->x, p1->y, degrade(p1, p2));
		if (0.5 < r)
		{
			r--;
			if (p1->y <= p2->y)
				p1->y++;
			else
				p1->y--;
		}
		else
		{
			r = r + e;
			p1->x++;
		}
	}
}

void	draw_line2(t_data *d, int x, int y, int z)
{
	float	g;
	int		p;

	g = d->controls.zoom;
	p = 300 + d->controls.y;
	if (x < d->m.nb_c + y - 1)
	{
		d->m.p1.x = x * g + d->controls.x;
		d->m.p2.x = (x + 1) * g + d->controls.x;
		d->m.p1.y = (d->m.nb_c + y - z - d->m.int_m[y][z]) * g / 2 + p;
		d->m.p2.y = (d->m.nb_c + y - z - d->m.int_m[y][z + 1] - 1) * g / 2 + p;
		d->m.p1.color = d->m.color_m[y][z];
		d->m.p2.color = d->m.color_m[y][z + 1];
		join_point(&d->m.p1, &d->m.p2, &d->img);
	}
	if (y < d->m.nb_l - d->controls.cut - 1)
	{
		d->m.p1.x = x * g + d->controls.x;
		d->m.p2.x = (x + 1) * g + d->controls.x;
		d->m.p1.y = (d->m.nb_c + y - z - d->m.int_m[y][z]) * g / 2 + p;
		d->m.p2.y = (d->m.nb_c + y - z - d->m.int_m[y + 1][z] + 1) * g / 2 + p;
		d->m.p1.color = d->m.color_m[y][z];
		d->m.p2.color = d->m.color_m[y + 1][z];
		join_point(&d->m.p1, &d->m.p2, &d->img);
	}
}

void	draw_line(t_data *data)
{
	int	x;
	int	y;
	int	z;

	y = 0;
	while (y < data->m.nb_l - data->controls.cut)
	{
		x = y;
		z = 0;
		while (x < data->m.nb_c + y)
		{
			draw_line2(data, x, y, z);
			x++;
			z++;
		}
		y++;
	}
}
