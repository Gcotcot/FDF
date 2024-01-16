/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 11:05:37 by gcot              #+#    #+#             */
/*   Updated: 2023/04/05 11:27:10 by gcot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if ((y >= 0 && x >= 0) && (y < 1000 && x < 1000))
	{
		i = img->bpp - 8;
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		while (i >= 0)
		{
			if (img->endian != 0)
				*pixel++ = (color >> i) & 0xFF;
			else
				*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
			i -= 8;
		}
	}
}

void	render_background(t_img *img, int color, int heigth, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < heigth)
		{
			img_pix_put(img, j, i, color);
			j++;
		}
		++i;
	}
}

int	render(t_data *data)
{
	if (data->win == NULL)
		return (1);
	render_background(&data->img, 0x000000, 1000, 1000);
	draw_line(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	return (0);
}

int	begin(t_data *data, char **argv)
{
	set_map(&data->m, argv[1]);
	set_controls(&data->controls);
	if (!data->m.int_m)
	{
		mlx_destroy_image(data->mlx, data->img.mlx_img);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	data->win = mlx_new_window(data->mlx, 1000, 1000, "FDF");
	if (data->win == NULL)
	{
		free(data->win);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.mlx = mlx_init();
	if (data.mlx == NULL)
		return (1);
	if (argc > 1)
	{
		if (begin(&data, argv))
			return (1);
		data.img.mlx_img = mlx_new_image(data.mlx, 1000, 1000);
		data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
				&data.img.line_len, &data.img.endian);
		mlx_loop_hook(data.mlx, &render, &data);
		mlx_hook(data.win, KeyPress, KeyPressMask, &handle_keypress, &data);
		mlx_hook(data.win, 2, 1, &handle_keypress, &data);
		mlx_hook(data.win, 17, 1, &close_win, &data);
		mlx_loop(data.mlx);
		mlx_destroy_image(data.mlx, data.img.mlx_img);
		mlx_destroy_display(data.mlx);
		if (data.m.int_m)
			free_map(&data.m);
	}
	free(data.mlx);
	return (0);
}
