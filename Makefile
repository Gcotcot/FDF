# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gcot <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/12 15:00:07 by gcot              #+#    #+#              #
#    Updated: 2023/04/28 14:43:49 by gcot             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc

SRC = main.c set_map.c free.c drawing.c controls.c degrade.c convert_base.c put_line.c GNL/get_next_line.c GNL/get_next_line_utils.c

FLAGS = -Wall -Werror -Wextra

all :
	gcc $(FLAGS) $(SRC) minilibx/libmlx_Linux.a -lX11 -lXext -o $(NAME)

clean :
	rm -rf *.o

fclean : clean
	rm -rf $(NAME)

re : fclean all
