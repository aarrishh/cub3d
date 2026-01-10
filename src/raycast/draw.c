/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:47:41 by mabaghda          #+#    #+#             */
/*   Updated: 2026/01/10 19:57:20 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_ceiling_floor(t_game *game, int x, int draw_start, int draw_end)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		put_pixels(&game->img, x, y, game->config.colors.ceiling_int);
		y++;
	}
	y = draw_end + 1;
	while (y < HEIGHT)
	{
		put_pixels(&game->img, x, y, game->config.colors.floor_int);
		y++;
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
