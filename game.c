/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 20:54:28 by mabaghda          #+#    #+#             */
/*   Updated: 2025/11/27 15:47:30 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_handler(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	return (0);
}

int	close_window(t_game *game)
{
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
}

void	draw_wall_line(t_game *game, int x, int start, int end)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y >= start && y <= end)
			put_pixels(&game->img, x, y, 0xFFFFFF);
		else if (y < start)
			put_pixels(&game->img, x, y, 0x7F00FF);
		else
			put_pixels(&game->img, x, y, 0x00FF00);
		y++;
	}
}

void	put_pixels(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->address + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// void	put_img_with_pixels(t_game *game)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < HEIGHT / 2)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			put_pixels(&game->img, x, y, 0x7F00FF);
// 			// stex piti lini mapi meji guyny
// 			x++;
// 		}
// 		y++;
// 	}
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			put_pixels(&game->img, x, y, 0x00FF00);
// 			// stex piti lini mapi meji guyny
// 			x++;
// 		}
// 		y++;
// 	}
// 	// mlx_put_image_to_window(game->mlx, game->window, game->img.img, 0, 0);
// }

void	pordznakan(t_game *game)
{
	game->config.map.grid = (char *[]){"1111111", "1000001", "100N001",
		"1000001", "1111111", NULL};
	game->config.map.width = 7;
	game->config.map.height = 5;
}

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

void	raycasting(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		draw_wall_line(game, x, HEIGHT / 4, 3 * HEIGHT / 4);
		x++;
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
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.address = mlx_get_data_addr(game->img.img,
			&game->img.bits_per_pixel, &game->img.line_length,
			&game->img.endian);
	mlx_hook(game->window, 17, 1L << 0, close_window, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_loop(game->mlx);
}
