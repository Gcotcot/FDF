/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:19:55 by gcot              #+#    #+#             */
/*   Updated: 2023/04/28 14:19:57 by gcot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	find_base(int c, char *base)
{
	int	i;

	i = 0;
	while (c != base[i])
		i++;
	return (i);
}

int	convert_base2(int i, char *line, int nb)
{
	if ('A' <= line[i] && line[i] <= 'F')
		nb = nb * 16 + find_base(line[i], "0123456789ABCDEF");
	else
		nb = nb * 16 + find_base(line[i], "0123456789abcdef");
	return (nb);
}

int	convert_base(char *line, int i, int end)
{
	int	nb;
	int	db;
	int	p;
	int	len;

	nb = 0;
	db = 0;
	p = 0;
	len = end - i;
	while (i < end)
	{
		nb = convert_base2(i, line, nb);
		i++;
		db++;
		if (db % 2 == 0 && len > 2)
		{
			p = p * 256 + nb * 256;
			nb = 0;
			len = len - 2;
		}
	}
	if (p > 0)
		return (p + nb);
	else
		return (nb);
}
