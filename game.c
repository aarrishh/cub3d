/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:13:54 by mabaghda          #+#    #+#             */
/*   Updated: 2025/11/11 19:45:14 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_handler(int keycode, t_game *game)
{
	// grel
}
int	close_window(t_game *game)
{
	// grel
	return (0);
}

void	start_game(t_game *game)
{
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, game->config.map.width,
			game->config.map.height, "Cub3D");
	init_images(game);
	draw_map(game);
	mlx_key_hook(game->window, key_handler, game);
	mlx_hook(game->window, 17, 1L << 0, close_window, game);
	mlx_loop(game->mlx);
}