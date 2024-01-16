/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcot <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:52:30 by gcot              #+#    #+#             */
/*   Updated: 2023/02/23 16:54:49 by gcot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>

char	*get_next_line(int fd);
char	*ft_join(char *file, char *src);
char	*ft_delete_line(char *str, char *file);
int		ft_strlen(char *str);
int		ft_strchr(char *s, int c);

#endif
