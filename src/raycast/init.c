/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:49:36 by mabaghda          #+#    #+#             */
/*   Updated: 2026/01/27 16:58:31 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_game_rest(t_game *game)

{
	game->config.colors.floor_int = 0;
	game->config.colors.ceiling_int = 0;
	game->config.map.grid = NULL;
	game->config.map.width = 0;
	game->config.map.height = 0;
	game->config.player.x = 0.0;
	game->config.player.y = 0.0;
	game->config.player.dir_x = 0.0;
	game->config.player.dir_y = 0.0;
	game->config.player.plane_x = 0.0;
	game->config.player.plane_y = 0.0;
	game->config.hyusisharav = NULL;
	game->config.map_before_split = NULL;
	game->config.splited_hyusisharav = NULL;
	game->config.splited_map = NULL;
}

void	init_all(t_game *game)
{
	int	i;

	game->mlx = NULL;
	game->window = NULL;
	game->img.img = NULL;
	game->img.address = NULL;
	game->img.bits_per_pixel = 0;
	game->img.line_length = 0;
	game->img.endian = 0;
	game->config.textures.no = NULL;
	game->config.textures.so = NULL;
	game->config.textures.we = NULL;
	game->config.textures.ea = NULL;
	i = 0;
	while (i < 3)
	{
		game->config.colors.floor[i] = 0;
		game->config.colors.ceiling[i] = 0;
		i++;
	}
	init_game_rest(game);
}
