/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:42:49 by gcot              #+#    #+#             */
/*   Updated: 2023/04/28 14:42:59 by gcot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	put_line3(int *color, char *line, int i, int y)
{
	int	nb;

	if (line[i] == ',')
	{
		i = i + 3;
		nb = i;
		while (line[i] && line[i] != '\n' && line[i] != ' ')
			i++;
		color[y] = convert_base(line, nb, i);
	}
	else
		color[y] = 0xffffff;
	while (line[i] && line[i] != '\n' && line[i] != ' ')
		i++;
	return (i);
}

int	put_line2(char *line, int i, int *map, int y)
{
	int	nb;
	int	signe;

	nb = 0;
	signe = 1;
	if (line[i] == '-')
	{
		i++;
		signe = -1;
	}
	while (line[i] && line[i] != '\n' && line[i] != ' ' && line[i] != ',')
	{
		nb = nb * 10 + (line[i] - '0');
		i++;
	}
	map[y] = nb * signe;
	return (i);
}

void	put_line(int *map, int *color, char *line)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] && line[i] != '\n' && line[i] == ' ')
			i++;
		if (line[i] && line[i] != '\n' && line[i] != ' ')
		{
			i = put_line2(line, i, map, y);
			i = put_line3(color, line, i, y++);
		}
	}
}
