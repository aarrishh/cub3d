# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/30 20:26:46 by arina             #+#    #+#              #
#    Updated: 2026/01/28 17:04:43 by arimanuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lGL -lGLU

OBJ_DIR = objects
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

SRCS = src/main.c get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c src/raycast/game.c \
	src/raycast/raycast.c src/raycast/textures.c src/raycast/draw.c \
	src/raycast/player.c src/raycast/init.c src/raycast/destroy.c \
	src/validation/color_2parse.c src/validation/color_parse.c \
	src/validation/file_check.c src/validation/flood_fill.c \
	src/validation/free_print.c src/validation/ft_split.c \
	src/validation/lib_functions.c src/validation/map_copy.c.c \
	src/validation/map_num2.c src/validation/map_wall_check.c \
	src/validation/mini_functions.c src/validation/texture_1parse.c \
	src/validation/texture_2parse.c src/validation/texture_3parse.c \
	src/validation/trim_functions.c src/validation/utils.c

YELLOW = \033[0;33m
DEEP_PINK   := \033[1;38;2;255;20;147m
RESET = \033[0m
GREEN  := \033[1;38;2;80;200;120m

all: $(NAME)

bonus:
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
