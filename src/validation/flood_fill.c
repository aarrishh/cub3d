/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:14:13 by arina             #+#    #+#             */
/*   Updated: 2026/01/27 15:56:56 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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


int	flood_fill_start(char **map, int y, int x, t_flag *flag)
{
	t_map	*m;
	char	c;

	m = flag->map;
	if (y < 0 || x < 0 || y >= m->height || x >= m->width)
	{
		flag->flag = -1;
		return(print_error("Map is not closed\n", NULL), -1);
	}
	c = map[y][x];
	if (c == '1' || c == 'F')
		return (0);
	if (c == '\0' || c == '2')
	{
		flag->flag = -1;
		return(print_error("Map is not closed\n", NULL), -1);
	}
	map[y][x] = 'F';
	flood_fill_start(map, y + 1, x, flag);
	flood_fill_start(map, y - 1, x, flag);
	flood_fill_start(map, y, x + 1, flag);
	flood_fill_start(map, y, x - 1, flag);
	if (flag->flag == -1)
		return (-1);
	return (0);
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


int flood_fill(t_map *map)
{
	int		px;
	int		py;
	char	**map_copy;
	t_flag	flag;

	get_player_pos(map, &px, &py);
	flag.map = map;
	flag.flag = 0;
	map_copy = copy_map_for_flood_fill(map->grid);
	if (flood_fill_start(map_copy, py, px, &flag) == -1)
	{
		free_matrix(map->grid);
		free_matrix(map_copy);
		return (-1);
	}
	for (int i = 0; map_copy[i]; i++)
		printf("%s\n", map_copy[i]);
	free_matrix(map_copy);
	// free_matrix(map->grid);
	return (0);
}
