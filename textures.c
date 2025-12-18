/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:36:15 by mabaghda          #+#    #+#             */
/*   Updated: 2025/12/18 13:44:17 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	load_texture(void *mlx, t_teximg *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		print_error("Texture load failed", NULL);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
}

t_teximg	*pick_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->rayDirX > 0)
			return (&game->west);
		return (&game->east);
	}
	else
	{
		if (ray->rayDirY > 0)
			return (&game->north);
		return (&game->south);
	}
}

void	calc_texture_x(t_game *game, t_ray *ray, t_teximg *tex)
{
	double	wallX;

	if (ray->side == 0)
		wallX = game->config.player.y + ray->perpWallDist * ray->rayDirY;
	else
		wallX = game->config.player.x + ray->perpWallDist * ray->rayDirX;
	wallX -= floor(wallX);
	ray->texX = (int)(wallX * tex->width);
	if (ray->side == 0 && ray->rayDirX > 0)
		ray->texX = tex->width - ray->texX - 1;
	if (ray->side == 1 && ray->rayDirY < 0)
		ray->texX = tex->width - ray->texX - 1;
}

void	draw_textured_wall(t_game *game, t_ray *ray, int x)
{
	t_teximg	*tex;
	double		step;
	double		texPos;
	int			y;
	int			texY;
	int			color;

	tex = pick_texture(game, ray);
	calc_texture_x(game, ray, tex);
	step = (double)tex->height / ray->lineHeight;
	texPos = (ray->drawStart - HEIGHT / 2 + ray->lineHeight / 2) * step;
	y = ray->drawStart;
	while (y <= ray->drawEnd)
	{
		texY = (int)texPos;
		if (texY < 0)
			texY = 0;
		if (texY >= tex->height)
			texY = tex->height - 1;
		texPos += step;
		color = *(int *)(tex->addr + texY * tex->line_len + ray->texX
				* (tex->bpp / 8));
		put_pixels(&game->img, x, y, color);
		y++;
	}
}
