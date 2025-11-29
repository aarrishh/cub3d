/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:54:28 by mabaghda          #+#    #+#             */
/*   Updated: 2025/11/29 19:57:37 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_config *config, double angle)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = config->dir_x;
	oldPlaneX = config->plane_x;
	config->dir_x = config->dir_x * cos(angle) - config->dir_y * sin(angle);
	config->dir_y = oldDirX * sin(angle) + config->dir_y * cos(angle);
	config->plane_x = config->plane_x * cos(angle) - config->plane_y
		* sin(angle);
	config->plane_y = oldPlaneX * sin(angle) + config->plane_y * cos(angle);
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
		move_player(game, game->config.dir_x * move_speed, game->config.dir_y
			* move_speed);
	else if (keycode == KEY_S)
		move_player(game, -game->config.dir_x * move_speed, -game->config.dir_y
			* move_speed);
	else if (keycode == KEY_A)
		move_player(game, -game->config.plane_x * move_speed,
			-game->config.plane_y * move_speed);
	else if (keycode == KEY_D)
		move_player(game, game->config.plane_x * move_speed,
			game->config.plane_y * move_speed);
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

	nx = game->config.player_x + dx;
	ny = game->config.player_y + dy;
	if (game->config.map.grid[(int)ny][(int)nx] != '1')
	{
		game->config.player_x = nx;
		game->config.player_y = ny;
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

// temporary
#include <string.h>

char	**dup_map_rows(const char *rows[], int count)
{
	char	**map;

	map = malloc((count + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	for (int i = 0; i < count; ++i)
	{
		map[i] = strdup(rows[i]);
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return (NULL);
		}
	}
	map[count] = NULL;
	return (map);
}

void	pordznakan(t_game *game)
{
	const char	*rows[] = {"1111111", "1000001", "100E001", "1000001",
			"1111111"};

	game->config.map.grid = dup_map_rows(rows, 5);
	game->config.map.width = 7;
	game->config.map.height = 5;
}
// temporary

void	set_dir_plane(t_config *config, char p)
{
	if (p == 'N')
	{
		config->dir_x = 0;
		config->dir_y = -1;
		config->plane_x = 0.66;
		config->plane_y = 0;
	}
	else if (p == 'S')
	{
		config->dir_x = 0;
		config->dir_y = 1;
		config->plane_x = -0.66;
		config->plane_y = 0;
	}
	else if (p == 'E')
	{
		config->dir_x = 1;
		config->dir_y = 0;
		config->plane_x = 0;
		config->plane_y = 0.66;
	}
	else if (p == 'W')
	{
		config->dir_x = -1;
		config->dir_y = 0;
		config->plane_x = 0;
		config->plane_y = -0.66;
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
				config->player_x = x + 0.5;
				config->player_y = y + 0.5;
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
	pordznakan(game);
	init_player(&game->config);
	game->config.colors.floor_int = rgb_to_int(game->config.colors.floor[0],
			game->config.colors.floor[1], game->config.colors.floor[2]);
	game->config.colors.ceiling_int = rgb_to_int(game->config.colors.ceiling[0],
			game->config.colors.ceiling[1], game->config.colors.ceiling[2]);
	game->mlx = mlx_init();
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
