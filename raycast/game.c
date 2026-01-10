/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:54:28 by mabaghda          #+#    #+#             */
/*   Updated: 2026/01/10 18:17:01 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	rotate_player(t_config *config, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = config->player.dir_x;
	old_plane_x = config->player.plane_x;
	config->player.dir_x = config->player.dir_x * cos(angle)
		- config->player.dir_y * sin(angle);
	config->player.dir_y = old_dir_x * sin(angle) + config->player.dir_y
		* cos(angle);
	config->player.plane_x = config->player.plane_x * cos(angle)
		- config->player.plane_y * sin(angle);
	config->player.plane_y = old_plane_x * sin(angle) + config->player.plane_y
		* cos(angle);
}

int	key_handler(int keycode, t_game *game)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.1;
	rot_speed = 0.05;
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		move_player(game, game->config.player.dir_x * move_speed,
			game->config.player.dir_y * move_speed);
	else if (keycode == KEY_S)
		move_player(game, -game->config.player.dir_x * move_speed,
			-game->config.player.dir_y * move_speed);
	else if (keycode == KEY_A)
		move_player(game, -game->config.player.plane_x * move_speed,
			-game->config.player.plane_y * move_speed);
	else if (keycode == KEY_D)
		move_player(game, game->config.player.plane_x * move_speed,
			game->config.player.plane_y * move_speed);
	else if (keycode == KEY_LEFT)
		rotate_player(&game->config, -rot_speed);
	else if (keycode == KEY_RIGHT)
		rotate_player(&game->config, rot_speed);
	return (0);
}

int	close_window(t_game *game)
{
	int	i;

	if (game->config.map.grid)
	{
		i = 0;
		while (game->config.map.grid[i])
		{
			free(game->config.map.grid[i]);
			i++;
		}
		free(game->config.map.grid);
		game->config.map.grid = NULL;
	}
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
}

void	move_player(t_game *game, double dx, double dy)
{
	double	nx;
	double	ny;

	nx = game->config.player.x + dx;
	ny = game->config.player.y + dy;
	if (game->config.map.grid[(int)ny][(int)nx] != '1')
	{
		game->config.player.x = nx;
		game->config.player.y = ny;
	}
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	put_pixels(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->address)
		return ;
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->address + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

void	set_dir_plane(t_config *config, char p)
{
	if (p == 'N')
	{
		config->player.dir_x = 0;
		config->player.dir_y = -1;
		config->player.plane_x = 0.66;
		config->player.plane_y = 0;
	}
	else if (p == 'S')
	{
		config->player.dir_x = 0;
		config->player.dir_y = 1;
		config->player.plane_x = -0.66;
		config->player.plane_y = 0;
	}
	else if (p == 'E')
	{
		config->player.dir_x = 1;
		config->player.dir_y = 0;
		config->player.plane_x = 0;
		config->player.plane_y = 0.66;
	}
	else if (p == 'W')
	{
		config->player.dir_x = -1;
		config->player.dir_y = 0;
		config->player.plane_x = 0;
		config->player.plane_y = -0.66;
	}
}

void	init_player(t_config *config)
{
	char	p;
	int		x;
	int		y;

	y = 0;
	while (config->map.grid[y])
	{
		x = 0;
		while (config->map.grid[y][x])
		{
			p = config->map.grid[y][x];
			if (p == 'N' || p == 'S' || p == 'E' || p == 'W')
			{
				config->player.x = x + 0.5;
				config->player.y = y + 0.5;
				set_dir_plane(config, p);
				config->map.grid[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

int	render(t_game *game)
{
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
	return (0);
}

void	start_game(t_game *game)
{
	init_player(&game->config);
	game->config.colors.floor_int = rgb_to_int(game->config.colors.floor[0],
			game->config.colors.floor[1], game->config.colors.floor[2]);
	game->config.colors.ceiling_int = rgb_to_int(game->config.colors.ceiling[0],
			game->config.colors.ceiling[1], game->config.colors.ceiling[2]);
	game->mlx = mlx_init();
	load_texture(game->mlx, &game->north, game->config.textures.no);
	load_texture(game->mlx, &game->south, game->config.textures.so);
	load_texture(game->mlx, &game->west, game->config.textures.we);
	load_texture(game->mlx, &game->east, game->config.textures.ea);
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.address = mlx_get_data_addr(game->img.img,
			&game->img.bits_per_pixel, &game->img.line_length,
			&game->img.endian);
	mlx_key_hook(game->window, key_handler, game);
	mlx_hook(game->window, 17, 1L << 0, close_window, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
}
