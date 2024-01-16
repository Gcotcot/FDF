/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:52:04 by gcot              #+#    #+#             */
/*   Updated: 2023/02/23 16:52:24 by gcot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr(char *s, int c)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_join(char *file, char *src)
{
	int		i;
	int		y;
	char	*dest;

	i = ft_strlen(file);
	y = ft_strlen(src);
	dest = malloc(sizeof(*dest) * (i + y + 1));
	i = 0;
	while (file[i])
	{
		dest[i] = file[i];
		i++;
	}
	free(file);
	y = 0;
	while (src[y])
	{
		dest[i + y] = src[y];
		y++;
	}
	dest[i + y] = '\0';
	return (dest);
}

char	*ft_delete_line(char *str, char *file)
{
	char	*new;
	int		i;
	int		y;

	i = ft_strlen(str);
	new = malloc(sizeof(*new) * (ft_strlen(file) - i + 1));
	y = 0;
	while (file[i])
	{
		new[y] = file[i];
		i++;
		y++;
	}
	free(file);
	new[y] = '\0';
	return (new);
}
