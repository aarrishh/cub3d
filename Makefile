# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 20:26:46 by arina             #+#    #+#              #
#    Updated: 2025/11/11 19:45:45 by mabaghda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror  #-g3 -fsanitize=address

MLX_DIR = ./minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lGL -lGLU

SRCS = \
	main.c get_next_line/get_next_line.c ft_split.c \
	get_next_line/get_next_line_utils.c functions.c \
	functions_for_trim.c parse.c game.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

get_next_line/%.o: get_next_line/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
