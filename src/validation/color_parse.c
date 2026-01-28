/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:50:41 by arimanuk          #+#    #+#             */
/*   Updated: 2026/01/28 17:09:55 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	assign_color(int *dest, char *value)
{
	int	v;

	v = color_value(value);
	if (v == -1)
		return (-1);
	*dest = v;
	return (0);
}

int	assign_color_values(t_config *data, char *id, char **rgb)
{
	if (ft_strcmp(id, "F") == 0)
	{
		if (assign_color(&data->colors.floor[0], rgb[0]) == -1
			|| assign_color(&data->colors.floor[1], rgb[1]) == -1
			|| assign_color(&data->colors.floor[2], rgb[2]) == -1)
			return (-1);
	}
	else if (ft_strcmp(id, "C") == 0)
	{
		if (assign_color(&data->colors.ceiling[0], rgb[0]) == -1
			|| assign_color(&data->colors.ceiling[1], rgb[1]) == -1
			|| assign_color(&data->colors.ceiling[2], rgb[2]) == -1)
			return (-1);
	}
	else
		ft_putstr_fd("Unknown color identifier\n", 2);
	return (0);
}

char	**split_color_line(char *line)
{
	char	**split;

	split = ft_split(line, ' ', 2);
	if (!split || !split[1])
		ft_putstr_fd("Invalid color line\n", 2);
	return (split);
}

char	**split_rgb_values(char **split)
{
	char	**rgb;
	int		i;

	rgb = ft_split(split[1], ',', MAX_SPLIT_CNT);
	if ((comma_count(split[1])) == -1)
		return (free_matrix(rgb), NULL);
	if (!rgb)
		return (ft_putstr_fd("Invalid RGB format\n", 2), NULL);
	i = 0;
	while (rgb[i])
	{
		rgb[i] = ft_strtrim(rgb[i], "\n\t\v\r\f ");
		if (check_valid_chars(rgb[i]) == -1)
		{
			free_matrix(rgb);
			return (ft_putstr_fd("Invalid RGB format\n", 2), NULL);
		}
		i++;
	}
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		free_matrix(rgb);
		return (ft_putstr_fd("Invalid RGB format\n", 2), NULL);
	}
	return (rgb);
}

int	parse_color(t_config *data, char *line)
{
	char	**split;
	char	**rgb;

	split = split_color_line(line);
	rgb = split_rgb_values(split);
	if (rgb)
	{
		if (assign_color_values(data, split[0], rgb) == -1)
		{
			free_matrix(rgb);
			free_matrix(split);
			return (-1);
		}
		free_matrix(rgb);
		free_matrix(split);
		return (0);
	}
	else
	{
		free_matrix(rgb);
		free_matrix(split);
		return (-1);
	}
}
