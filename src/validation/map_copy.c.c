/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:52:21 by arina             #+#    #+#             */
/*   Updated: 2026/01/28 13:03:56 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	copy_map_part_2(char *str, char *buffer, int width)
{
	int	i;
	int	rest;

	i = 0;
	while (str[i])
	{
		buffer[i] = str[i];
		i++;
	}
	rest = width - ft_strlen(str);
	while (rest)
	{
		buffer[i] = '2';
		i++;
		rest--;
	}
	buffer[i] = '\0';
}

int	height_map(char **map, t_map *map_s)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	map_s->height = i;
	return (i);
}

int	width_map(char **map, t_map *map_s)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	map_s->width = max;
	return (max);
}

void	second_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_white_space(map[i][j]))
				map[i][j] = '2';
			j++;
		}
		i++;
	}
}

char	**copy_map(char **str, t_map *map, int i)
{
	int		width;
	int		heigth;
	char	**buffer;

	buffer = NULL;
	width = width_map(str, map);
	heigth = height_map(str, map);
	buffer = (char **)malloc((heigth + 1) * sizeof(char *));
	if (!buffer)
		return (NULL);
	buffer[heigth] = NULL;
	while (heigth)
	{
		buffer[i] = (char *)malloc((width + 1) * sizeof(char));
		if (!buffer[i])
		{
			free_array(buffer);
			return (NULL);
		}
		copy_map_part_2(str[i], buffer[i], width);
		i++;
		heigth--;
	}
	second_check(buffer);
	return (buffer);
}
