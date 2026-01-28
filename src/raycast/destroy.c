/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:14:41 by mabaghda          #+#    #+#             */
/*   Updated: 2026/01/28 15:27:06 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	destroy_textures(t_game *game)
{
	if (!game->mlx)
		return ;
	if (game->north.img)
		mlx_destroy_image(game->mlx, game->north.img);
	if (game->south.img)
		mlx_destroy_image(game->mlx, game->south.img);
	if (game->west.img)
		mlx_destroy_image(game->mlx, game->west.img);
	if (game->east.img)
		mlx_destroy_image(game->mlx, game->east.img);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	game->north.img = NULL;
	game->south.img = NULL;
	game->west.img = NULL;
	game->east.img = NULL;
	game->img.img = NULL;
}

void	free_textures_cw_case(t_game *game)
{
	destroy_textures(game);
	if (game->config.textures.no)
		free(game->config.textures.no);
	if (game->config.textures.so)
		free(game->config.textures.so);
	if (game->config.textures.we)
		free(game->config.textures.we);
	if (game->config.textures.ea)
		free(game->config.textures.ea);
	game->config.textures.no = NULL;
	game->config.textures.so = NULL;
	game->config.textures.we = NULL;
	game->config.textures.ea = NULL;
}

int	close_window(t_game *game, int flag)
{
	int	i;

	free_textures_cw_case(game);
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
	if (flag == -1)
		exit(1);
	ft_putstr_fd("Congratulations!\n", 1);
	exit(0);
}
