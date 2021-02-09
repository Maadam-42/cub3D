# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maadam <maadam@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/15 19:32:01 by maadam            #+#    #+#              #
#    Updated: 2020/11/15 19:32:01 by maadam           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = cub3D

SRC = srcs/main.c srcs/args_files_check.c srcs/check_config_and_sort_sprites.c \
	srcs/errors_and_exit.c srcs/get_next_line.c srcs/get_next_line_utils.c \
	srcs/key_check.c srcs/make_map.c srcs/parsing_cub.c srcs/raycasting.c \
	srcs/screenshot.c srcs/sprites.c srcs/start_cub.c srcs/utils.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -framework OpenGL -framework Appkit

HEADER = cub3d.h

MLX = libmlx.dylib

MLX_DIR = minilibx_mms/

all: $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

$(MLX):
	make -C $(MLX_DIR)
	@cp $(MLX_DIR)$(MLX) ./

$(NAME): $(OBJ) $(MLX)
	gcc -o $(NAME) $(MLX) $(OBJ) $(MLX_FLAGS)
	@echo "$(NAME) is ready!"

clean:
	@rm -f *.bmp
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(MLX)
	@make -C $(MLX_DIR) clean

re: fclean all
