/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arina <arina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:18:49 by arina             #+#    #+#             */
/*   Updated: 2025/11/24 21:09:35 by arina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_texture(t_config *data, char *line)
{
	int i;
	char	**split;

	i = 0;
	
	line = ft_strtrim(line, "\n\t\v\r\f ");
	split = ft_split(line, ' ', MAX_SPLIT_CNT);
	free(line);
	if (!split || !split[0] || !split[1])
		print_error("Invalid texture line\n", split);
	while (split[i])
		i++;
	if (i > 2)
		return (-1);
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
	return (0);
}

int	color_value(char *s)
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

int	parse_color(t_config *data, char *line)
{
	char	**split;
	(void) data;
	char	**rgb;

	// if (!split || !split[0] || !split[1])
		// print_error("Invalid color line\n", split);
	split = ft_split(line,  ' ', 2);
	if (split[1])
		rgb = ft_split(split[1], ',', MAX_SPLIT_CNT);
	else
		return (-1);
	free(split[1]);
	// rgb = ft_split(split[1], ','); // split[1]
	int i = 0;
	while (rgb[i])
	{		
		rgb[i] = ft_strtrim(rgb[i], "\n\t\v\r\f ");
		i++;
	}
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
	// printf("fff_____%d\n", data->colors.floor[0]);
	// printf("fff_____%d\n", data->colors.floor[1]);
	// printf("fff_____%d\n", data->colors.floor[2]);
	// printf("ccc_____%d\n", data->colors.ceiling[0]);
	// printf("ccc_____%d\n", data->colors.ceiling[1]);
	// printf("ccc_____%d\n", data->colors.ceiling[2]);

	// // free_matrix(split); ereviii
	// // free_matrix(rgb); ereviii
	return (0);
}

int	is_map_line(char *str)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (is_white_space(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == '0')
			found = 1;
		else if (!is_white_space(str[i]))
			return (-1);
		i++;
	}
	return (found);
}


int	parse_elements(t_config *data, char **file)
{
	int	i;
	int flag;

	i = 0;
	flag = 0;
	while (file[i])
	{
		if (!file[i][0] || !file[i])
		{
			i++;
			continue ;
		}
		if (flag == 0 && file[i])
			file[i] = ft_strtrim(file[i], "\n\t\v\r\f ");
		// printf("%s\naaaa\n", file[i]);
		if (ft_strncmp(file[i], "NO", 2) == 0 || ft_strncmp(file[i], "SO", 2) == 0 || ft_strncmp(file[i], "WE", 2) == 0 || ft_strncmp(file[i], "EA", 2) == 0)
		{
			if (parse_texture(data, file[i]) == -1)
				return (-1);
		}
		else if (ft_strncmp(file[i], "F", 1) == 0 || ft_strncmp(file[i], "C", 1) == 0)
		{
			parse_color(data, file[i]);
			if (ft_strncmp(file[i], "C", 1) == 0)
				flag = 1;
		}
		else if (is_map_line(file[i]) == -1)
			return (-1);
		else if (is_map_line(file[i]) != -1)
			break ;
		else
			print_error("Invalid line in configuration\n", file);
		i++;
	}
	data->map.grid = &file[i];
	// printf("%s\n", data->textures.no);
	// printf("%s\n", data->textures.ea);
	// printf("%s\n", data->textures.so);
	// printf("%s\n\n", data->textures.we);
	// printf("%d,%d,%d\n", data->colors.floor[0], data->colors.floor[1], data->colors.floor[2]);
	// printf("%d,%d,%d\n\n", data->colors.ceiling[0], data->colors.ceiling[1], data->colors.ceiling[2]);

	// i = 0;
	// while (data->map.grid[i])
	// 	printf("%s\n", data->map.grid[i++]);
	return (0);
}


