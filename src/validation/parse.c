/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 18:18:49 by arina             #+#    #+#             */
/*   Updated: 2026/01/27 21:59:24 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parse_texture(t_config *data, char *line)
{
	int		i;
	char	**split;

	i = 0;
	line = ft_strtrim_helper(line, "\n\t\v\r\f ");
	split = ft_split(line, ' ', MAX_SPLIT_CNT);
	free(line);
	if (!split || !split[0] || !split[1])
		return (print_error("Invalid texture line\n", NULL), -1);
	while (split[i])
		i++;
	if (i > 2)
		return (free_matrix(split), -1);
	(void)data;
	if (ft_strcmp(split[0], "NO") == 0)
		data->textures.no = ft_strdup(split[1]);
	else if (ft_strcmp(split[0], "SO") == 0)
		data->textures.so = ft_strdup(split[1]);
	else if (ft_strcmp(split[0], "WE") == 0)
		data->textures.we = ft_strdup(split[1]);
	else if (ft_strcmp(split[0], "EA") == 0)
		data->textures.ea = ft_strdup(split[1]);
	else
		print_error("Unknown texture identifier\n", NULL);
	return (free_matrix(split), 0);
}

int	color_value(char *s)
{
	int	value;

	value = ft_atoi(s);
	if (value < 0 || value > 255)
	{
		write(2, "RGB value out of range (0-255)\n", 32);
		return (-1);
	}
	return (value);
}

char	**split_color_line(char *line)
{
	char	**split;

	split = ft_split(line, ' ', 2);
	if (!split || !split[1])
		print_error("Invalid color line\n", split);
	return (split);
}

int	comma_count(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
	{
		print_error("Invalid RGB format\n", NULL);
		return (-1);
	}
	return (0);
}

char	**split_rgb_values(char **split)
{
	char	**rgb;
	int		i;

	rgb = ft_split(split[1], ',', MAX_SPLIT_CNT);
	if ((comma_count(split[1])) == -1)
	{
		free_matrix(rgb);
		return (NULL);
	}
	if (!rgb)
		return (print_error("Invalid RGB format\n", split), NULL);
	i = 0;
	while (rgb[i])
	{
		rgb[i] = ft_strtrim(rgb[i], "\n\t\v\r\f ");
		i++;
	}
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		free_matrix(rgb);
		return (print_error("Invalid RGB format\n", rgb), NULL);
	}
	return (rgb);
}

int	assign_color_values(t_config *data, char *id, char **rgb)
{
	if (ft_strcmp(id, "F") == 0)
	{
		if ((data->colors.floor[0] = color_value(rgb[0])) == -1)
			return (-1);
		if ((data->colors.floor[1] = color_value(rgb[1])) == -1)
			return (-1);
		if ((data->colors.floor[2] = color_value(rgb[2])) == -1)
			return (-1);
	}
	else if (ft_strcmp(id, "C") == 0)
	{
		if ((data->colors.ceiling[0] = color_value(rgb[0])) == -1)
			return (-1);
		if ((data->colors.ceiling[1] = color_value(rgb[1])) == -1)
			return (-1);
		if ((data->colors.ceiling[2] = color_value(rgb[2])) == -1)
			return (-1);
	}
	else
		print_error("Unknown color identifier\n", NULL);
	return (0);
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

void	free_textures(t_config **t)
{
	if (((*t)->textures.no))
		free((*t)->textures.no);
	if (((*t)->textures.so))
		free((*t)->textures.so);
	if (((*t)->textures.we))
		free((*t)->textures.we);
	if (((*t)->textures.ea))
		free((*t)->textures.ea);
	(*t)->textures.no = NULL;
	(*t)->textures.so = NULL;
	(*t)->textures.we = NULL;
	(*t)->textures.ea = NULL;
}

int	parse_elements(t_config **data)
{
	int	i;

	i = -1;
	while ((*data)->splited_hyusisharav[++i])
		(*data)->splited_hyusisharav[i] = ft_strtrim((*data)->splited_hyusisharav[i],
				"\n\t\v\r\f ");
	i = 0;
	while ((*data)->splited_hyusisharav[i])
	{
		if (!(*data)->splited_hyusisharav[i][0]
			|| !(*data)->splited_hyusisharav[i])
		{
			i++;
			continue ;
		}
		if (ft_strncmp((*data)->splited_hyusisharav[i], "NO", 2) == 0
			|| ft_strncmp((*data)->splited_hyusisharav[i], "SO", 2) == 0
			|| ft_strncmp((*data)->splited_hyusisharav[i], "WE", 2) == 0
			|| ft_strncmp((*data)->splited_hyusisharav[i], "EA", 2) == 0)
		{
			if (parse_texture(*data, (*data)->splited_hyusisharav[i]) == -1)
				return (-1);
		}
		else if (ft_strncmp((*data)->splited_hyusisharav[i], "F", 1) == 0
			|| ft_strncmp((*data)->splited_hyusisharav[i], "C", 1) == 0)
		{
			if (parse_color(*data, (*data)->splited_hyusisharav[i]) == -1)
				return (free_textures(data), -1);
		}
			else
			{
				print_error("Invalid line in configurationnn\n", NULL);
				return (free_textures(data), -1);
			}
		i++;
	}
	if (check_textures((*data)->textures) == -1)
		return (free_textures(data), -1);
	return (0);
}
