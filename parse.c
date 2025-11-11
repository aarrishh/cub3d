/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:18:49 by arina             #+#    #+#             */
/*   Updated: 2025/11/09 18:20:28 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_texture(t_config *data, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		print_error("Invalid texture line\n", split);
	if (ft_strcmp(split[0], "NO") == 0)
		data->textures.no = ft_strdup(split[1]);
	else if (ft_strcmp(split[0], "SO") == 0)
		data->textures.so = ft_strdup(split[1]);
	else if (ft_strcmp(split[0], "WE") == 0)
		data->textures.we = ft_strdup(split[1]);
	else if (ft_strcmp(split[0], "EA") == 0)
		data->textures.ea = ft_strdup(split[1]);
	else
		print_error("Unknown texture identifier\n", split);
    //free_matrix petqa anenq voncvor???
}

#include "cub3d.h"

static int	color_value(char *s)
{
	int	value;

	value = atoi(s);
	if (value < 0 || value > 255)
	{
		write(2, "Error\nInvalid RGB value\n", 25);
		exit(1);
	}
	return (value);
}

void	parse_color(t_config *data, char *line)
{
	char	**split;
	char	**rgb;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		print_error("Invalid color line\n", split);
	rgb = ft_split(split[1], ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
		print_error("Invalid RGB format\n", rgb);
	if (ft_strcmp(split[0], "F") == 0)
	{
		data->colors.floor[0] = color_value(rgb[0]);
		data->colors.floor[1] = color_value(rgb[1]);
		data->colors.floor[2] = color_value(rgb[2]);
	}
	else if (ft_strcmp(split[0], "C") == 0)
	{
		data->colors.ceiling[0] = color_value(rgb[0]);
		data->colors.ceiling[1] = color_value(rgb[1]);
		data->colors.ceiling[2] = color_value(rgb[2]);
	}
	// free_matrix(split); ereviii
	// free_matrix(rgb); ereviii
}

#include "cub3d.h"

int	is_map_line(char *str)
{
	int	i;

	i = 0;
	while (is_white_space(str[i]))
		i++;
	if (str[i] == '1' || str[i] == '0')
		return (1);
	return (0);
}

void	parse_elements(t_config *data, char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (!file[i][0])
		{
			i++;
			continue ;
		}
		if (ft_strncmp(file[i], "NO", 2) == 0 || ft_strncmp(file[i], "SO", 2) == 0
			|| ft_strncmp(file[i], "WE", 2) == 0 || ft_strncmp(file[i], "EA", 2) == 0)
			parse_texture(data, file[i]);
		else if (ft_strncmp(file[i], "F", 1) == 0 || ft_strncmp(file[i], "C", 1) == 0)
			parse_color(data, file[i]);
		else if (is_map_line(file[i]))
			break ;
		else
			print_error("Invalid line in configuration\n", file);
		i++;
	}
	data->map.grid = &file[i];
}


