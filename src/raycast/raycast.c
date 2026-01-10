/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:52:02 by mabaghda          #+#    #+#             */
/*   Updated: 2026/01/10 19:41:52 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_ray(t_game *game, int x, t_ray *ray)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = game->config.player.dir_x + game->config.player.plane_x
		* ray->camera_x;
	ray->ray_dir_y = game->config.player.dir_y + game->config.player.plane_y
		* ray->camera_x;
	ray->map_x = (int)game->config.player.x;
	ray->map_y = (int)game->config.player.y;
	ray->hit = 0;
	ray->side = 0;
	if (ray->ray_dir_x == 0.0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0.0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

void	calc_step_and_side(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->config.player.x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->config.player.x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->config.player.y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->config.player.y)
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_x < 0
			|| !game->config.map.grid[ray->map_y]
			|| !game->config.map.grid[ray->map_y][ray->map_x])
			break ;
		if (game->config.map.grid[ray->map_y][ray->map_x] == '1'
			|| game->config.map.grid[ray->map_y][ray->map_x] == '2')
			ray->hit = 1;
	}
}

void	calc_wall_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

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

void	raycasting(t_game *game)
{
	int			x;
	t_ray		ray;
	t_teximg	tex;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(game, x, &ray);
		calc_step_and_side(game, &ray);
		perform_dda(game, &ray);
		if (ray.hit == 1)
		{
			calc_wall_height(&ray);
			draw_ceiling_floor(game, x, ray.draw_start, ray.draw_end);
			draw_textured_wall(game, &ray, &tex, x);
		}
		x++;
	}
}
