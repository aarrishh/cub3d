/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:14:13 by arina             #+#    #+#             */
/*   Updated: 2025/12/02 21:36:21 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void get_player_pos(t_map *map, int *px, int *py)
{
	int	y;
	int	x;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S'
				|| map->grid[y][x] == 'E' || map->grid[y][x] == 'W')
			{
				*py = y;
				*px = x;
				return;
			}
			x++;
		}
		y++;
	}
}

void flood_fill_start(char **map, int y, int x, t_map *m)
{
	if (y < 0 || x < 0 || y >= m->height || x >= m->width)
		print_error("Map is not closed\n", map);
	char c = map[y][x];
	if (c == '1' || c == 'F') 
		return;
	if (c == '\0' || c == ' ')
		print_error("Map is not closed\n", map);
	map[y][x] = 'F';
	flood_fill_start(map, y + 1, x, m);
	flood_fill_start(map, y - 1, x, m);
	flood_fill_start(map, y, x + 1, m);
	flood_fill_start(map, y, x - 1, m);
}

void flood_fill(t_map *map)
{
	int	px;
	int	py;

	get_player_pos(map, &px, &py);
	flood_fill_start(map->grid, py, px, map);
}
