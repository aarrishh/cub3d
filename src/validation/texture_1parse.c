/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_1parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arimanuk <arimanuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:46:12 by arimanuk          #+#    #+#             */
/*   Updated: 2026/01/28 17:06:59 by arimanuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	trim_lines(t_config *data)
{
	int	i;

	i = 0;
	while (data->splited_hyusisharav[i])
	{
		data->splited_hyusisharav[i] = ft_strtrim(
				data->splited_hyusisharav[i], "\n\t\v\r\f ");
		i++;
	}
}

static int	parse_texture_or_color_line(t_config *data, char *line)
{
	if (!line || !line[0])
		return (0);
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
	{
		if (parse_texture(data, line) == -1)
			return (free_textures(&data), -1);
	}
	else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
	{
		if (parse_color(data, line) == -1)
			return (free_textures(&data), -1);
	}
	else
	{
		ft_putstr_fd("Invalid line in configuration\n", 2);
		return (free_textures(&data), -1);
	}
	return (0);
}

int	parse_elements(t_config **data)
{
	int	i;

	trim_lines(*data);
	i = 0;
	while ((*data)->splited_hyusisharav[i])
	{
		if (parse_texture_or_color_line(*data,
				(*data)->splited_hyusisharav[i]) == -1)
			return (-1);
		i++;
	}
	if (check_textures((*data)->textures) == -1)
		return (free_textures(data), -1);
	return (0);
}

static void	assign_texture(char **dest, char *src)
{
	if (*dest)
		free(*dest);
	*dest = ft_strdup(src);
}

int	parse_texture(t_config *data, char *line)
{
	int		i;
	char	**split;

	i = 0;
	line = ft_strtrim_helper(line, "\n\t\v\r\f ");
	split = ft_split(line, ' ', MAX_SPLIT_CNT);
	free(line);
	if (!split || !split[0] || !split[1])
		return (ft_putstr_fd("Invalid texture line\n", 2), -1);
	while (split[i])
		i++;
	if (i > 2)
		return (free_matrix(split), -1);
	if (ft_strcmp(split[0], "NO") == 0)
		assign_texture(&data->textures.no, split[1]);
	else if (ft_strcmp(split[0], "SO") == 0)
		assign_texture(&data->textures.so, split[1]);
	else if (ft_strcmp(split[0], "WE") == 0)
		assign_texture(&data->textures.we, split[1]);
	else if (ft_strcmp(split[0], "EA") == 0)
		assign_texture(&data->textures.ea, split[1]);
	else
		return (free_matrix(split), -1);
	return (free_matrix(split), 0);
}
