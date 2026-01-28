/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:36:15 by mabaghda          #+#    #+#             */
/*   Updated: 2026/01/28 15:31:30 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_texture(t_game *game, void *mlx, t_teximg *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		ft_putstr_fd("Texture load failed\n", 2);
		close_window(game, -1);
	}
	if (tex->img != NULL)
		tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
				&tex->endian);
}

t_teximg	*pick_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&game->west);
		return (&game->east);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&game->north);
		return (&game->south);
	}
}

void	calc_texture_x(t_game *game, t_ray *ray, t_teximg *tex)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->config.player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->config.player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	ray->texture_x = (int)(wall_x * tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->texture_x = tex->width - ray->texture_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->texture_x = tex->width - ray->texture_x - 1;
}

void	draw_textured_wall(t_game *game, t_ray *ray, t_teximg *tex, int x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	tex = pick_texture(game, ray);
	calc_texture_x(game, ray, tex);
	step = (double)tex->height / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		tex_pos += step;
		color = *(int *)(tex->addr + tex_y * tex->line_len + ray->texture_x
				* (tex->bpp / 8));
		put_pixels(&game->img, x, y, color);
		y++;
	}
}
