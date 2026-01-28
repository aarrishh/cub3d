/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:54:03 by mabaghda          #+#    #+#             */
/*   Updated: 2026/01/28 15:07:38 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
				dir_plane_horizontal(config, p);
				dir_plane_vertical(config, p);
				config->map.grid[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

int	key_handler(int keycode, t_game *game)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.1;
	rot_speed = 0.05;
	if (keycode == KEY_ESC)
		close_window(game, 0);
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
