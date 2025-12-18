/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabaghda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:18:49 by arina             #+#    #+#             */
/*   Updated: 2025/12/18 15:55:13 by mabaghda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	parse_texture(t_config *data, char *line)
{
	int		i;
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
	// printf("%s\n", data->textures.ea);
	// printf("%s\n", data->textures.so);
	// printf("%s\n", data->textures.we);
	// printf("%s\n", data->textures.no);
    //free_matrix petqa anenq voncvor???
	return (0);
}

int	color_value(char *s)
{
	int	value;

	value = ft_atoi(s);
	if (value < 0 || value > 255)
	{
		write(2, "RGB value out of range (0-255)\n", 32);
		exit(1);
	}
	return (value);
}

int	parse_color(t_config *data, char *line)
{
	char	**split;
	char	**rgb;

	split = ft_split(line,  ' ', 2);
	if (split[1])
		rgb = ft_split(split[1], ',', MAX_SPLIT_CNT);
	else
		return (-1);
	free(split[1]);
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
	// free_matrix(split); ereviii
	// free_matrix(rgb); ereviii
	return (0);
}

void	change_flag_and_found_value(int *found, int *flag_plus_plus)
{
	(*found) = 2;
	(*flag_plus_plus)++;
}

int	is_map_line_second(char *str)
{
	int	i;

	i = 0;
	while (is_white_space(str[i]))
		i++;
	if (str[i] == '1' || str[i] == '0')
		return (1);
	return (0);
}

int	is_map_line(char *str, t_colflag *f)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == '0')
		{
			if (found == 2 || found == 3)
				found = 3;
			else
				found = 1;
		}
		else if (str[i] == 'N')
			change_flag_and_found_value(&found, &(*f).no_flag);
		else if (str[i] == 'W')
			change_flag_and_found_value(&found, &(*f).we_flag);
		else if (str[i] == 'E')
			change_flag_and_found_value(&found, &(*f).ea_flag);
		else if (str[i] == 'S')
			change_flag_and_found_value(&found, &(*f).so_flag);
		else if (!is_white_space(str[i]))
			return (-1);
		i++;
	}
	return (found);
}

int	parse_elements(t_config **data)
{
	int		i;
	char	**file;

	file = (*data)->splited_hyusisharav;
	i = -1;
	while (file[++i])
		file[i] = ft_strtrim(file[i], "\n\t\v\r\f ");
	i = 0;
	while (file[i])
	{
		if (!file[i][0] || !file[i])
		{
			i++;
			continue ;
		}
		if (ft_strncmp(file[i], "NO", 2) == 0 || ft_strncmp(file[i], "SO", 2) == 0 || ft_strncmp(file[i], "WE", 2) == 0 || ft_strncmp(file[i], "EA", 2) == 0)
		{
			if (parse_texture(*data, file[i]) == -1)
				return (-1);
		}
		else if (ft_strncmp(file[i], "F", 1) == 0 || ft_strncmp(file[i], "C", 1) == 0)
			parse_color(*data, file[i]);
		else
			print_error("Invalid line in configuration\n", file);
		i++;
	}
	check_textures((*data)->textures);
	return (0);
}
