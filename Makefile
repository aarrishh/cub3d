# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 20:26:46 by arina             #+#    #+#              #
#    Updated: 2025/12/18 19:37:44 by mabaghda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lGL -lGLU

OBJ_DIR = objects
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

SRCS = main.c get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	ft_split.c functions.c functions_for_trim.c \
	parse.c game.c raycast.c map_operations.c \
	flood_fill.c check_functions.c mini_functions.c \
	textures.c


YELLOW = \033[0;33m
DEEP_PINK   := \033[1;38;2;255;20;147m
RESET = \033[0m
GREEN  := \033[1;38;2;80;200;120m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME) -lm
	@echo "$(DEEP_PINK)Cube3d compilation completed!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)Compiling $<...$(RESET)"

clean:
	@echo "cleaning objects..."
	@$(RM) -r $(OBJ_DIR)
	@echo "$(YELLOW)Objects cleaning completed!$(RESET)"

fclean: clean
	@echo "cleaning executable..."
	@$(RM) $(NAME)
	@echo "$(YELLOW)Executable cleaning completed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
