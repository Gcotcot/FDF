/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:16:15 by gcot              #+#    #+#             */
/*   Updated: 2023/04/06 16:16:31 by gcot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_line(char *argv)
{
	char	*line;
	int		nb_line;
	int		fd;

	fd = open(argv, O_RDONLY);
	nb_line = 0;
	line = get_next_line(fd);
	while (line)
	{
		nb_line++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (nb_line);
}

int	count_col(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] && line[i] != '\n' && line[i] == ' ')
			i++;
		if (line[i] && line[i] != '\n' && line[i] != ' ')
		{
			count++;
			while (line[i] && line[i] != '\n' && line[i] != ' ')
				i++;
		}
	}
	return (count);
}

void	set_controls(t_controls *controls)
{
	controls->x = 0;
	controls->y = 0;
	controls->cut = 0;
	controls->zoom = 3;
}

void	set_map(t_map *map, char *argv)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	map->nb_l = count_line(argv);
	map->int_m = malloc(sizeof(*map->int_m) * map->nb_l);
	map->color_m = malloc(sizeof(*map->color_m) * map->nb_l);
	fd = open(argv, O_RDONLY);
	line = get_next_line(fd);
	map->nb_c = count_col(line);
	while (line)
	{
		map->int_m[i] = malloc(sizeof(**map->int_m) * map->nb_c);
		map->color_m[i] = malloc(sizeof(**map->color_m) * map->nb_c);
		put_line(map->int_m[i], map->color_m[i], line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	close(fd);
}

void	size_win(int width, int height, t_img *img)
{
	img->width = width;
	img->height = height;
}
