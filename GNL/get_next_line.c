/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:51:08 by gcot              #+#    #+#             */
/*   Updated: 2023/02/23 16:51:35 by gcot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buf, char *file)
{
	int	re;

	re = read(fd, buf, BUFFER_SIZE);
	if (re <= 0)
	{
		free(buf);
		free(file);
		return (NULL);
	}
	buf[re] = '\0';
	file = ft_join(file, buf);
	while (ft_strchr(file, '\n') && re > 0)
	{
		re = read(fd, buf, BUFFER_SIZE);
		buf[re] = '\0';
		file = ft_join(file, buf);
	}
	free(buf);
	return (file);
}

char	*ft_write_line(char *file)
{
	int		i;
	int		y;
	char	*str;

	if (!file)
		return (NULL);
	i = 0;
	while (file[i] && file[i] != '\n')
		i++;
	if (file[i] == '\n')
		i++;
	str = malloc(sizeof(*str) * (i + 1));
	y = i;
	i = 0;
	while (i < y)
	{
		str[i] = file[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*file;
	char		*buf;
	char		*str;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!file)
	{
		file = malloc(sizeof(*file) * 1);
		file[0] = '\0';
		buf = malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
		file = ft_read(fd, buf, file);
	}
	if (ft_strchr(file, '\n'))
	{
		buf = malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
		file = ft_read(fd, buf, file);
	}
	if (!file)
		return (NULL);
	str = ft_write_line(file);
	file = ft_delete_line(str, file);
	return (str);
}
