/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:14:13 by arina             #+#    #+#             */
/*   Updated: 2025/12/14 18:15:18 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	get_player_pos(t_map *map, int *px, int *py)
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
				return ;
			}
			x++;
		}
		y++;
	}
}

void	flood_fill_start(char **map, int y, int x, t_map *m)
{
	char	c;

	if (y < 0 || x < 0 || y >= m->height || x >= m->width)
		print_error("Map is not closed\n", map);
	c = map[y][x];
	if (c == '1' || c == 'F')
		return ;
	if (c == '\0' || c == ' ')
		print_error("Map is not closed\n", map);
	map[y][x] = 'F';
	flood_fill_start(map, y + 1, x, m);
	flood_fill_start(map, y - 1, x, m);
	flood_fill_start(map, y, x + 1, m);
	flood_fill_start(map, y, x - 1, m);
}
char	**copy_map_for_flood_fill(char **map)
{
	char	**copy;
	int		i;

	if (!map)
		return (NULL);
	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	flood_fill(t_map *map)
{
	int		px;
	int		py;
	char	**map_copy;

	get_player_pos(map, &px, &py);
	map_copy = copy_map_for_flood_fill(map->grid);
	flood_fill_start(map_copy, py, px, map);
}
