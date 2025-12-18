/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:52:02 by mabaghda          #+#    #+#             */
/*   Updated: 2025/12/18 13:42:49 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	init_ray(t_game *game, int x, t_ray *ray)
{
	ray->cameraX = 2 * x / (double)WIDTH - 1;
	ray->rayDirX = game->config.player.dir_x + game->config.player.plane_x
		* ray->cameraX;
	ray->rayDirY = game->config.player.dir_y + game->config.player.plane_y
		* ray->cameraX;
	ray->mapX = (int)game->config.player.x;
	ray->mapY = (int)game->config.player.y;
	ray->hit = 0;
	ray->side = 0;
	if (ray->rayDirX == 0.0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1.0 / ray->rayDirX);
	if (ray->rayDirY == 0.0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1.0 / ray->rayDirY);
}

void	calc_step_and_side(t_game *game, t_ray *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->config.player.x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - game->config.player.x)
			* ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->config.player.y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - game->config.player.y)
			* ray->deltaDistY;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (ray->mapY < 0 || ray->mapX < 0 || !game->config.map.grid[ray->mapY]
			|| !game->config.map.grid[ray->mapY][ray->mapX])
			break ;
		if (game->config.map.grid[ray->mapY][ray->mapX] == '1'
			|| game->config.map.grid[ray->mapY][ray->mapX] == '2')
			ray->hit = 1;
	}
}

void	calc_wall_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpWallDist = ray->sideDistX - ray->deltaDistX;
	else
		ray->perpWallDist = ray->sideDistY - ray->deltaDistY;
	ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
}

void	draw_ceiling_floor(t_game *game, int x, int drawStart, int drawEnd)
{
	int	y;

	y = 0;
	while (y < drawStart)
	{
		put_pixels(&game->img, x, y, game->config.colors.ceiling_int);
		y++;
	}
	y = drawEnd + 1;
	while (y < HEIGHT)
	{
		put_pixels(&game->img, x, y, game->config.colors.floor_int);
		y++;
	}
}

void	raycasting(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(game, x, &ray);
		calc_step_and_side(game, &ray);
		perform_dda(game, &ray);
		if (ray.hit == 1)
		{
			calc_wall_height(&ray);
			draw_ceiling_floor(game, x, ray.drawStart, ray.drawEnd);
			draw_textured_wall(game, &ray, x);
		}
		x++;
	}
}
